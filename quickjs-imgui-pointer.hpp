
#ifndef QUICKJS_IMGUI_POINTER_HPP
#define QUICKJS_IMGUI_POINTER_HPP

typedef enum { PROPERTY = 0, CALL = 1, INVOKE = 2, GETSET = 3 } pointer_closure_type;

thread_local VISIBLE JSClassID js_imgui_pointer_class_id = 0;
thread_local JSValue imgui_pointer_proto = {JS_TAG_UNDEFINED}, imgui_pointer_ctor = {JS_TAG_UNDEFINED};

typedef struct imgui_pointer_closure {
  int ref_count, magic;
  JSContext* ctx;
  union {
    JSValue obj;
    JSValue fns[2];
  };
  JSAtom prop;
  pointer_closure_type type;
} ImGuiPointerClosure;

static void
js_imgui_pointer_finalize(void* opaque) {
  ImGuiPointerClosure* closure(static_cast<ImGuiPointerClosure*>(opaque));

  if(--closure->ref_count == 0) {
    JSContext* ctx = closure->ctx;
    JS_FreeValue(ctx, closure->obj);
    JS_FreeAtom(ctx, closure->prop);
    JS_FreeValue(ctx, closure->fns[1]);

    js_free(ctx, closure);
  }
}

static ImGuiPointerClosure*
js_imgui_pointer_dup(JSContext* ctx, ImGuiPointerClosure const* closure) {
  ImGuiPointerClosure* ret;

  if(!(ret = static_cast<ImGuiPointerClosure*>(js_malloc(ctx, sizeof(ImGuiPointerClosure)))))
    return nullptr;

  ret->ref_count = 1;
  ret->magic = closure->magic;
  ret->ctx = ctx;
  ret->fns[0] = JS_DupValue(ctx, closure->fns[0]);
  ret->fns[1] = JS_DupValue(ctx, closure->fns[1]);
  ret->prop = JS_DupAtom(ctx, closure->prop);
  ret->type = closure->type;
  return ret;
}

static void
js_imgui_pointer_finalizer(JSRuntime* rt, JSValue val) {
  ImGuiPointerClosure* closure = static_cast<ImGuiPointerClosure*>(JS_GetOpaque(val, js_imgui_pointer_class_id));
  if(closure) {
    js_free_rt(rt, closure);
  }
  JS_FreeValueRT(rt, val);
}

static JSValue
js_imgui_pointer_set(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv, int magic, void* opaque) {
  ImGuiPointerClosure* closure(static_cast<ImGuiPointerClosure*>(opaque));
  JSValue ret = JS_UNDEFINED;

  switch(closure->type) {
    case CALL: ret = JS_Call(ctx, closure->obj, JS_UNDEFINED, argc, argv); break;
    case INVOKE: ret = JS_Invoke(ctx, closure->obj, closure->prop, argc, argv); break;
    case PROPERTY: JS_SetProperty(ctx, closure->obj, closure->prop, JS_DupValue(ctx, argv[0])); break;
    case GETSET: ret = JS_Call(ctx, closure->fns[1], JS_UNDEFINED, argc, argv); break;
  }
  return ret;
}

static JSValue
js_imgui_pointer_get(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv, int magic, void* opaque) {
  ImGuiPointerClosure* closure(static_cast<ImGuiPointerClosure*>(opaque));
  JSValue ret = JS_UNDEFINED;

  switch(closure->type) {
    case CALL: ret = JS_Call(ctx, closure->obj, JS_UNDEFINED, 0, 0); break;
    case INVOKE: ret = JS_Invoke(ctx, closure->obj, closure->prop, 0, 0); break;
    case PROPERTY: ret = JS_GetProperty(ctx, closure->obj, closure->prop); break;
    case GETSET: ret = JS_Call(ctx, closure->fns[0], JS_UNDEFINED, 0, 0); break;
  }
  return ret;
}

static JSValue
js_imgui_pointer_func(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv, int magic, void* opaque) {
  ImGuiPointerClosure* closure(static_cast<ImGuiPointerClosure*>(opaque));
  JSValue ret = JS_UNDEFINED;

  return (argc == 0 || JS_IsUndefined(argv[0])) ? js_imgui_pointer_get(ctx, this_val, argc, argv, magic, opaque) : js_imgui_pointer_set(ctx, this_val, argc, argv, magic, opaque);
}

static JSValue
js_imgui_pointer(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  JSValue ret = JS_UNDEFINED;
  ImGuiPointerClosure* closure;

  if(!(closure = static_cast<ImGuiPointerClosure*>(js_malloc(ctx, sizeof(ImGuiPointerClosure)))))
    return JS_ThrowOutOfMemory(ctx);

  bool is_function = JS_IsFunction(ctx, argv[0]);

  closure->ref_count = 1;
  closure->magic = magic;
  closure->ctx = ctx;
  closure->obj = JS_DupValue(ctx, argv[0]);
  closure->type = is_function ? (argc >= 2 && !JS_IsUndefined(argv[1])) ? JS_IsFunction(ctx, argv[1]) ? GETSET : INVOKE : CALL : PROPERTY;
  closure->prop = JS_ValueToAtom(ctx, argc >= 2 ? argv[1] : JS_UNDEFINED);
  closure->fns[1] = closure->type == GETSET ? JS_DupValue(ctx, argv[1]) : JS_UNDEFINED;

  switch(magic) {
    case 0:
    case 1:
    case 2:
      ret = JS_NewObjectProtoClass(ctx, imgui_pointer_proto, js_imgui_pointer_class_id);

      JS_SetOpaque(ret, closure);

      break;
    case 3:
      ImGuiPointerClosure* closure2 = closure = js_imgui_pointer_dup(ctx, closure);
      closure->magic = 1;
      closure2->magic = 2;

      ret = JS_NewArray(ctx);

      JSValue getter = JS_NewObjectProtoClass(ctx, imgui_pointer_proto, js_imgui_pointer_class_id);
      JSValue setter = JS_NewObjectProtoClass(ctx, imgui_pointer_proto, js_imgui_pointer_class_id);
      JS_SetOpaque(getter, closure);
      JS_SetOpaque(setter, closure2);

      JS_SetPropertyUint32(ctx, ret, 0, getter);
      JS_SetPropertyUint32(ctx, ret, 0, setter);
      break;
  }

  return ret;
}

static JSValue
js_imgui_pointer_call(JSContext* ctx, JSValueConst func_obj, JSValueConst this_val, int argc, JSValueConst argv[], int flags) {
  ImGuiPointerClosure* closure;
  JSValue ret = JS_UNDEFINED;
  if(!(closure = static_cast<ImGuiPointerClosure*>(JS_GetOpaque2(ctx, func_obj, js_imgui_pointer_class_id))))
    return JS_EXCEPTION;

  switch(closure->magic) {
    case 0: ret = js_imgui_pointer_func(ctx, this_val, argc, argv, closure->magic, closure); break;
    case 1: ret = js_imgui_pointer_get(ctx, this_val, argc, argv, closure->magic, closure); break;
    case 2: ret = js_imgui_pointer_set(ctx, this_val, argc, argv, closure->magic, closure); break;
    default: ret = JS_ThrowInternalError(ctx, "%s: invalid magic %d", __func__, closure->magic); break;
  }
  return ret;
}

static JSClassDef js_imgui_pointer_class = {
    .class_name = "ImGuiPointer",
    .finalizer = js_imgui_pointer_finalizer,
    .call = js_imgui_pointer_call,
};

#endif // defined(QUICKJS_IMGUI_POINTER_HPP)
