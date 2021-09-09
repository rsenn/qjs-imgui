#ifndef QUICKJS_IMGUI_PAYLOAD_HPP
#define QUICKJS_IMGUI_PAYLOAD_HPP

thread_local VISIBLE JSClassID js_imgui_payload_class_id = 0;
thread_local JSValue imgui_payload_proto = {JS_TAG_UNDEFINED}, imgui_payload_ctor = {JS_TAG_UNDEFINED};

enum {
  PAYLOAD_CLEAR,
  PAYLOAD_IS_DATA_TYPE,
  PAYLOAD_IS_PREVIEW,
  PAYLOAD_IS_DELIVERY,
};

static inline ImGuiPayload*
js_imgui_payload_data2(JSContext* ctx, JSValueConst value) {
  return static_cast<ImGuiPayload*>(JS_GetOpaque2(ctx, value, js_imgui_payload_class_id));
}

static JSValue
js_imgui_payload_wrap(JSContext* ctx, const ImGuiPayload& payload) {
  JSValue obj = JS_NewObjectProtoClass(ctx, imgui_payload_proto, js_imgui_payload_class_id);
  JS_SetOpaque(obj, new ImGuiPayload(payload));
  return obj;
}

static JSValue
js_imgui_payload_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  JSValue proto, obj = JS_UNDEFINED;
  ImGuiPayload* payload = new ImGuiPayload();
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;
  obj = JS_NewObjectProtoClass(ctx, proto, js_imgui_payload_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;
  JS_SetOpaque(obj, payload);
  return obj;
fail:
  js_free(ctx, payload);
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

static void
js_imgui_payload_finalizer(JSRuntime* rt, JSValue val) {
  ImGuiPayload* payload = static_cast<ImGuiPayload*>(JS_GetOpaque(val, js_imgui_payload_class_id));
  if(payload) {
    delete payload;
  }
  JS_FreeValueRT(rt, val);
}

static JSValue
js_imgui_payload_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  ImGuiPayload* payload;
  JSValue ret = JS_UNDEFINED;

  if(!(payload = js_imgui_payload_data2(ctx, this_val)))
    return ret;

  switch(magic) {
    case PAYLOAD_CLEAR: {
      payload->Clear();
      break;
    }
    case PAYLOAD_IS_DATA_TYPE: {
      const char* type = JS_ToCString(ctx, argv[0]);
      ret = JS_NewBool(ctx, payload->IsDataType(type));
      JS_FreeCString(ctx, type);
      break;
    }
    case PAYLOAD_IS_PREVIEW: {
      ret = JS_NewBool(ctx, payload->IsPreview());
      break;
    }
    case PAYLOAD_IS_DELIVERY: {
      ret = JS_NewBool(ctx, payload->IsDelivery());
      break;
    }
  }

  return ret;
}

static JSClassDef js_imgui_payload_class = {
    .class_name = "ImGuiPayload",
    .finalizer = js_imgui_payload_finalizer,
};

static const JSCFunctionListEntry js_imgui_payload_funcs[] = {
    JS_CFUNC_MAGIC_DEF("Clear", 0, js_imgui_payload_functions, PAYLOAD_CLEAR),
    JS_CFUNC_MAGIC_DEF("IsDataType", 1, js_imgui_payload_functions, PAYLOAD_IS_DATA_TYPE),
    JS_CFUNC_MAGIC_DEF("IsPreview", 0, js_imgui_payload_functions, PAYLOAD_IS_PREVIEW),
    JS_CFUNC_MAGIC_DEF("IsDelivery", 0, js_imgui_payload_functions, PAYLOAD_IS_DELIVERY),
};

#endif // defined(QUICKJS_IMGUI_PAYLOAD_HPP)
