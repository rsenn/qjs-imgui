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
  CALL,
  INVOKE,
  GETSET,
  INTERNAL,
};

struct ImGuiPointerClosure {
  int ref_count, magic;
  JSAtom prop;
  ImGuiPointerType type;
  union {
    JSValue obj;
    struct {
      JSValue funcObj;
      JSValue thisObj;
    };
    struct {
      JSValue get;
      JSValue set;
    };
  };
};

static void
js_imgui_pointer_finalizer(JSRuntime* rt, JSValue val) {
  ImGuiPointerClosure* ptr;

  if((ptr = static_cast<ImGuiPointerClosure*>(JS_GetOpaque(val, js_imgui_pointer_class_id)))) {

    if(--ptr->ref_count == 0) {
      JS_FreeAtomRT(rt, ptr->prop);
      JS_FreeValueRT(rt, ptr->obj);
      JS_FreeValueRT(rt, ptr->set);

      js_free_rt(rt, ptr);
    }
  }
  // JS_FreeValueRT(rt, val);
}

static JSValue
js_imgui_pointer_set(JSContext* ctx, ImGuiPointerClosure* ptr, JSValueConst value) {
  JSValue ret = JS_UNDEFINED;

  switch(ptr->type) {
    case CALL: ret = JS_Call(ctx, ptr->funcObj, ptr->thisObj, 1, &value); break;
    case INVOKE: ret = JS_Invoke(ctx, ptr->obj, ptr->prop, 1, &value); break;
    case PROPERTY: JS_SetProperty(ctx, ptr->obj, ptr->prop, JS_DupValue(ctx, value)); break;
    case GETSET: ret = JS_Call(ctx, ptr->set, JS_UNDEFINED, 1, &value); break;
    case INTERNAL: JS_FreeValue(ctx, ptr->obj), ptr->obj = JS_DupValue(ctx, value); break;
  }

  return ret;
}

static JSValue
js_imgui_pointer_get(JSContext* ctx, ImGuiPointerClosure* ptr) {
  JSValue ret = JS_UNDEFINED;

  switch(ptr->type) {
    case CALL: ret = JS_Call(ctx, ptr->funcObj, ptr->thisObj, 0, 0); break;
    case INVOKE: ret = JS_Invoke(ctx, ptr->obj, ptr->prop, 0, 0); break;
    case PROPERTY: ret = JS_GetProperty(ctx, ptr->obj, ptr->prop); break;
    case GETSET: ret = JS_Call(ctx, ptr->get, JS_UNDEFINED, 0, 0); break;
    case INTERNAL: ret = JS_DupValue(ctx, ptr->obj); break;
  }

  return ret;
}

static JSValue
js_imgui_pointer_func(JSContext* ctx, ImGuiPointerClosure* ptr, int argc, JSValueConst argv[]) {
  return (argc == 0 || JS_IsUndefined(argv[0])) ? js_imgui_pointer_get(ctx, ptr) : js_imgui_pointer_set(ctx, ptr, argv[0]);
}

static inline ImGuiPointerClosure*
imgui_pointer_dup(ImGuiPointerClosure* ptr) {
  ++ptr->ref_count;
  return ptr;
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

      ImGuiPointerType type(INTERNAL);

      if(JS_IsFunction(ctx, argv[0]))
        type = (argc > 1 && JS_IsFunction(ctx, argv[1])) ? GETSET : CALL;
      else if(argc > 1 && (JS_IsString(argv[1]) || JS_IsSymbol(argv[1])) && JS_IsObject(argv[0]))
        type = PROPERTY;
      else if(argc > 1 && (JS_IsString(argv[0]) || JS_IsSymbol(argv[0])) && JS_IsObject(argv[1]))
        type = INVOKE;
      else
        type = INTERNAL;

      ptr->ref_count = 1;
      ptr->magic = magic;
      ptr->obj = JS_DupValue(ctx, argv[type == INVOKE ? 1 : 0]);
      ptr->type = type;
      ptr->prop = JS_ValueToAtom(ctx, (type == INVOKE || type == PROPERTY) ? argv[type == INVOKE ? 0 : 1] : JS_UNDEFINED);
      ptr->set = type == GETSET || (type == CALL && argc > 1) ? JS_DupValue(ctx, argv[1]) : JS_UNDEFINED;

      ret = JS_NewObjectProtoClass(ctx, imgui_pointer_proto, js_imgui_pointer_class_id);

      JS_SetOpaque(ret, ptr);
      break;
    }
  }

  return ret;
}

static JSValue
js_imgui_pointer_valueof(JSContext* ctx, JSValueConst this_obj, int argc, JSValueConst argv[]) {
  ImGuiPointerClosure* ptr;
  JSValue ret = JS_UNDEFINED;

  if(!(ptr = static_cast<ImGuiPointerClosure*>(JS_GetOpaque2(ctx, this_obj, js_imgui_pointer_class_id))))
    return JS_EXCEPTION;

  return js_imgui_pointer_get(ctx, ptr);
}

static JSValue
js_imgui_pointer_call(JSContext* ctx, JSValueConst func_obj, JSValueConst this_val, int argc, JSValueConst argv[], int flags) {
  ImGuiPointerClosure* ptr;
  JSValue ret = JS_UNDEFINED;

  if(!(ptr = static_cast<ImGuiPointerClosure*>(JS_GetOpaque2(ctx, func_obj, js_imgui_pointer_class_id))))
    return JS_EXCEPTION;

  switch(ptr->magic) {
    case POINTER_CALL: ret = js_imgui_pointer_func(ctx, ptr, argc, argv); break;
    case POINTER_GET: ret = js_imgui_pointer_get(ctx, ptr); break;
    case POINTER_SET: ret = js_imgui_pointer_set(ctx, ptr, argc > 0 ? argv[0] : JS_UNDEFINED); break;
    default: ret = JS_ThrowInternalError(ctx, "%s: invalid magic %d", __func__, ptr->magic); break;
  }

  return ret;
}

static JSClassDef js_imgui_pointer_class = {
    .class_name = "ImGuiPointer",
    .finalizer = js_imgui_pointer_finalizer,
    .call = js_imgui_pointer_call
};

static const JSCFunctionListEntry js_imgui_pointer_funcs[] = {
    JS_CFUNC_DEF("valueOf", 0, js_imgui_pointer_valueof),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "ImGuiPointer", JS_PROP_CONFIGURABLE),
};

#endif // defined(QUICKJS_IMGUI_POINTER_HPP)
