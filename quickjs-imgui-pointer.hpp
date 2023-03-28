
#ifndef QUICKJS_IMGUI_POINTER_HPP
#define QUICKJS_IMGUI_POINTER_HPP

typedef enum { PROPERTY = 0, CALL = 1, INVOKE = 2, GETSET = 3 } pointer_closure_type;

thread_local VISIBLE JSClassID js_imgui_pointer_class_id = 0;
thread_local JSValue imgui_pointer_proto = {JS_TAG_UNDEFINED}, imgui_pointer_ctor = {JS_TAG_UNDEFINED};

typedef struct imgui_pointer_closure {
  int ref_count;
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
  closure->ctx = ctx;
  closure->obj = JS_DupValue(ctx, argv[0]);
  closure->type = is_function ? (argc >= 2 && !JS_IsUndefined(argv[1])) ? JS_IsFunction(ctx, argv[1]) ? GETSET : INVOKE : CALL : PROPERTY;
  closure->prop = JS_ValueToAtom(ctx, argc >= 2 ? argv[1] : JS_UNDEFINED);
  closure->fns[1] = closure->type == GETSET ? JS_DupValue(ctx, argv[1]) : JS_UNDEFINED;

  switch(magic) {
    case 0: ret = JS_NewCClosure(ctx, js_imgui_pointer_func, 1, 0, closure, js_imgui_pointer_finalize); break;
    case 1: ret = JS_NewCClosure(ctx, js_imgui_pointer_get, 0, magic, closure, js_imgui_pointer_finalize); break;
    case 2: ret = JS_NewCClosure(ctx, js_imgui_pointer_set, 1, magic, closure, js_imgui_pointer_finalize); break;
    case 3:
      closure->ref_count = 2;
      ret = JS_NewArray(ctx);
      JS_SetPropertyUint32(ctx, ret, 0, JS_NewCClosure(ctx, js_imgui_pointer_get, 0, magic, closure, js_imgui_pointer_finalize));
      JS_SetPropertyUint32(ctx, ret, 1, JS_NewCClosure(ctx, js_imgui_pointer_set, 1, magic, closure, js_imgui_pointer_finalize));
      break;
  }

  return ret;
}

static JSValue
js_imgui_pointer_call(JSContext* ctx, JSValueConst func_obj, JSValueConst this_val, int argc, JSValueConst argv[], int flags) {
    ImGuiPointerClosure* closure;

    if(!(closure = static_cast<ImGuiPointerClosure*>(JS_GetOpaque2(ctx, func_obj, js_imgui_pointer_class_id))))
      return JS_EXCEPTION;

    return JS_UNDEFINED;
}
 
static JSClassDef js_imgui_pointer_class = {
    .class_name = "ImGuiPointer",
    .finalizer = js_imgui_pointer_finalizer,
    .call = js_imgui_pointer_call,
};


#endif // defined(QUICKJS_IMGUI_POINTER_HPP)
