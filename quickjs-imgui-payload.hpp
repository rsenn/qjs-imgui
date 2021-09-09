#ifndef QUICKJS_IMGUI_PAYLOAD_HPP
#define QUICKJS_IMGUI_PAYLOAD_HPP

thread_local VISIBLE JSClassID js_imgui_payload_class_id = 0;
thread_local JSValue imgui_payload_proto = {JS_TAG_UNDEFINED}, imgui_payload_ctor = {JS_TAG_UNDEFINED};

enum { 

};

static JSValue
js_imgui_payload_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  ImGuiPayload* io;
  JSValue proto, obj = JS_UNDEFINED;

  /* if(!(io = static_cast<ImGuiPayload*>(js_mallocz(ctx, sizeof(ImGuiPayload)))))
     return JS_EXCEPTION;

   new (io)  ImGuiPayload();*/
  io = new ImGuiPayload();

  /* using new_target to get the prototype is necessary when the class is extended. */
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;
  obj = JS_NewObjectProtoClass(ctx, proto, js_imgui_payload_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, io);

  return obj;
fail:
  js_free(ctx, io);
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

static void
js_imgui_payload_finalizer(JSRuntime* rt, JSValue val) {
  ImGuiPayload* io = static_cast<ImGuiPayload*>(JS_GetOpaque(val, js_imgui_payload_class_id));
  if(io) {
    delete io;
  }
  JS_FreeValueRT(rt, val);
}

static JSValue
js_imgui_payload_get(JSContext* ctx, JSValueConst this_val, int magic) {
  ImGuiPayload* io;
  JSValue ret = JS_UNDEFINED;

  if(!(io = static_cast<ImGuiPayload*>(JS_GetOpaque2(ctx, this_val, js_imgui_payload_class_id))))
    return ret;

  switch(magic) {}

  return ret;
}

static JSValue
js_imgui_payload_set(JSContext* ctx, JSValueConst this_val, JSValueConst value, int magic) {
  ImGuiPayload* io;
  JSValue ret = JS_UNDEFINED;

  if(!(io = static_cast<ImGuiPayload*>(JS_GetOpaque2(ctx, this_val, js_imgui_payload_class_id))))
    return ret;

  switch(magic) {}

  return ret;
}

static JSClassDef js_imgui_payload_class = {
    .class_name = "ImGuiPayload",
    .finalizer = js_imgui_payload_finalizer,
};

static const JSCFunctionListEntry js_imgui_payload_funcs[] = {
  

};

#endif // defined(QUICKJS_IMGUI_PAYLOAD_HPP)
