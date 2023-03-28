#ifndef QUICKJS_IMGUI_POINTER_HPP
#define QUICKJS_IMGUI_POINTER_HPP

enum {
  POINTER_CALL,
  POINTER_GET,
  POINTER_SET,
  POINTER_GETSET,
};

thread_local VISIBLE JSClassID js_imgui_pointer_class_id = 0;
thread_local JSValue imgui_pointer_proto = {JS_TAG_UNDEFINED};

enum ImGuiPointerType {
  PROPERTY = 0,
  CALL = 1,
  INVOKE = 2,
  GETSET = 3,
};

struct ImGuiPointerClosure {
  int magic;
  union {
    JSValue obj;
    struct {
      JSValue get;
      JSValue set;
    };
  };
  JSAtom prop;
  ImGuiPointerType type;
};

static void
js_imgui_pointer_finalizer(JSRuntime* rt, JSValue val) {
  ImGuiPointerClosure* ptr;

  if((ptr = static_cast<ImGuiPointerClosure*>(JS_GetOpaque(val, js_imgui_pointer_class_id)))) {
    JS_FreeAtomRT(rt, ptr->prop);
    JS_FreeValueRT(rt, ptr->obj);
    JS_FreeValueRT(rt, ptr->set);

    js_free_rt(rt, ptr);
  }
  JS_FreeValueRT(rt, val);
}

static JSValue
js_imgui_pointer_set(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv, int magic, void* opaque) {
  ImGuiPointerClosure* ptr(static_cast<ImGuiPointerClosure*>(opaque));
  JSValue ret = JS_UNDEFINED;

  switch(ptr->type) {
    case CALL: ret = JS_Call(ctx, ptr->obj, JS_UNDEFINED, argc, argv); break;
    case INVOKE: ret = JS_Invoke(ctx, ptr->obj, ptr->prop, argc, argv); break;
    case PROPERTY: JS_SetProperty(ctx, ptr->obj, ptr->prop, JS_DupValue(ctx, argv[0])); break;
    case GETSET: ret = JS_Call(ctx, ptr->set, JS_UNDEFINED, argc, argv); break;
  }
  return ret;
}

static JSValue
js_imgui_pointer_get(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv, int magic, void* opaque) {
  ImGuiPointerClosure* ptr(static_cast<ImGuiPointerClosure*>(opaque));
  JSValue ret = JS_UNDEFINED;

  switch(ptr->type) {
    case CALL: ret = JS_Call(ctx, ptr->obj, JS_UNDEFINED, 0, 0); break;
    case INVOKE: ret = JS_Invoke(ctx, ptr->obj, ptr->prop, 0, 0); break;
    case PROPERTY: ret = JS_GetProperty(ctx, ptr->obj, ptr->prop); break;
    case GETSET: ret = JS_Call(ctx, ptr->get, JS_UNDEFINED, 0, 0); break;
  }
  return ret;
}

static JSValue
js_imgui_pointer_func(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv, int magic, void* opaque) {
  ImGuiPointerClosure* ptr(static_cast<ImGuiPointerClosure*>(opaque));
  JSValue ret = JS_UNDEFINED;

  return (argc == 0 || JS_IsUndefined(argv[0])) ? js_imgui_pointer_get(ctx, this_val, argc, argv, magic, opaque) : js_imgui_pointer_set(ctx, this_val, argc, argv, magic, opaque);
}

static JSValue
js_imgui_pointer(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  JSValue ret = JS_UNDEFINED;

  switch(magic) {
    case POINTER_GETSET:
      ret = JS_NewArray(ctx);

      JS_SetPropertyUint32(ctx, ret, 0, js_imgui_pointer(ctx, this_val, argc, argv, POINTER_GET));
      JS_SetPropertyUint32(ctx, ret, 1, js_imgui_pointer(ctx, this_val, argc, argv, POINTER_SET));
      break;

    default: {
      ImGuiPointerClosure* ptr;

      if(!(ptr = static_cast<ImGuiPointerClosure*>(js_malloc(ctx, sizeof(ImGuiPointerClosure)))))
        return JS_ThrowOutOfMemory(ctx);

      BOOL is_function = JS_IsFunction(ctx, argv[0]);

      ptr->magic = magic;
      ptr->obj = JS_DupValue(ctx, argv[0]);
      ptr->type = is_function ? (argc >= 2 && !JS_IsUndefined(argv[1])) ? JS_IsFunction(ctx, argv[1]) ? GETSET : INVOKE : CALL : PROPERTY;
      ptr->prop = JS_ValueToAtom(ctx, argc >= 2 && !JS_IsFunction(ctx, argv[1]) ? argv[1] : JS_UNDEFINED);
      ptr->set = ptr->type == GETSET ? JS_DupValue(ctx, argv[1]) : JS_UNDEFINED;

      ret = JS_NewObjectProtoClass(ctx, imgui_pointer_proto, js_imgui_pointer_class_id);

      JS_SetOpaque(ret, ptr);

      break;
    }
  }

  return ret;
}

static JSValue
js_imgui_pointer_call(JSContext* ctx, JSValueConst func_obj, JSValueConst this_val, int argc, JSValueConst argv[], int flags) {
  ImGuiPointerClosure* ptr;
  JSValue ret = JS_UNDEFINED;
  
  if(!(ptr = static_cast<ImGuiPointerClosure*>(JS_GetOpaque2(ctx, func_obj, js_imgui_pointer_class_id))))
    return JS_EXCEPTION;

  switch(ptr->magic) {
    case POINTER_CALL: ret = js_imgui_pointer_func(ctx, this_val, argc, argv, ptr->magic, ptr); break;
    case POINTER_GET: ret = js_imgui_pointer_get(ctx, this_val, argc, argv, ptr->magic, ptr); break;
    case POINTER_SET: ret = js_imgui_pointer_set(ctx, this_val, argc, argv, ptr->magic, ptr); break;
    default: ret = JS_ThrowInternalError(ctx, "%s: invalid magic %d", __func__, ptr->magic); break;
  }
  return ret;
}

static JSClassDef js_imgui_pointer_class = {
    .class_name = "ImGuiPointer",
    .finalizer = js_imgui_pointer_finalizer,
    .call = js_imgui_pointer_call,
};

static const JSCFunctionListEntry js_imgui_pointer_funcs[] = {
       JS_PROP_STRING_DEF("[Symbol.toStringTag]", "ImGuiPointer", JS_PROP_CONFIGURABLE),

};

#endif // defined(QUICKJS_IMGUI_POINTER_HPP)
