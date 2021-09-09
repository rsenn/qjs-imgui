#ifndef QUICKJS_IMGUI_INPUTTEXTCALLBACKDATA_HPP
#define QUICKJS_IMGUI_INPUTTEXTCALLBACKDATA_HPP

thread_local VISIBLE JSClassID js_imgui_inputtextcallbackdata_class_id = 0;
thread_local JSValue imgui_inputtextcallbackdata_proto = {JS_TAG_UNDEFINED}, imgui_inputtextcallbackdata_ctor = {JS_TAG_UNDEFINED};

enum {
  INPUTTEXTCALLBACKDATA_DELETE_CHARS,
  INPUTTEXTCALLBACKDATA_INSERT_CHARS,
  INPUTTEXTCALLBACKDATA_SELECT_ALL,
  INPUTTEXTCALLBACKDATA_CLEAR_SELECTION,
  INPUTTEXTCALLBACKDATA_HAS_SELECTION,
};

static inline ImGuiInputTextCallbackData*
js_imgui_inputtextcallbackdata_data2(JSContext* ctx, JSValueConst value) {
  return static_cast<ImGuiInputTextCallbackData*>(JS_GetOpaque2(ctx, value, js_imgui_inputtextcallbackdata_class_id));
}

static JSValue
js_imgui_inputtextcallbackdata_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  JSValue proto, obj = JS_UNDEFINED;
  ImGuiInputTextCallbackData* itcd = new ImGuiInputTextCallbackData();
  /* using new_target to get the prototype is necessary when the class is extended. */
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;
  obj = JS_NewObjectProtoClass(ctx, proto, js_imgui_inputtextcallbackdata_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;
  JS_SetOpaque(obj, itcd);
  return obj;
fail:
  js_free(ctx, itcd);
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

static void
js_imgui_inputtextcallbackdata_finalizer(JSRuntime* rt, JSValue val) {
  ImGuiInputTextCallbackData* itcd = static_cast<ImGuiInputTextCallbackData*>(JS_GetOpaque(val, js_imgui_inputtextcallbackdata_class_id));
  if(itcd) {
    delete itcd;
  }
  JS_FreeValueRT(rt, val);
}

static JSValue
js_imgui_inputtextcallbackdata_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  ImGuiInputTextCallbackData* itcd;
  JSValue ret = JS_UNDEFINED;

  if(!(itcd = js_imgui_inputtextcallbackdata_data2(ctx, this_val)))
    return ret;

  switch(magic) {

    case INPUTTEXTCALLBACKDATA_DELETE_CHARS: {
      int32_t pos, bytes_count;
      JS_ToInt32(ctx, &pos, argv[0]);
      JS_ToInt32(ctx, &bytes_count, argv[1]);
      itcd->DeleteChars(pos, bytes_count);
      break;
    }
    case INPUTTEXTCALLBACKDATA_INSERT_CHARS: {
      int32_t pos;
      const char *text = JS_ToCString(ctx, argv[1]), *text_end = 0;
      if(argc >= 3)
        text_end = JS_ToCString(ctx, argv[2]);
      JS_ToInt32(ctx, &pos, argv[0]);
      itcd->InsertChars(pos, text, text_end);
      JS_FreeCString(ctx, text);
      if(text_end)
        JS_FreeCString(ctx, text_end);
      break;
    }
    case INPUTTEXTCALLBACKDATA_SELECT_ALL: {
      itcd->SelectAll();
      break;
    }
    case INPUTTEXTCALLBACKDATA_CLEAR_SELECTION: {
      itcd->ClearSelection();
      break;
    }
    case INPUTTEXTCALLBACKDATA_HAS_SELECTION: {
      ret = JS_NewBool(ctx, itcd->HasSelection());
      break;
    }
  }

  return ret;
}

static JSClassDef js_imgui_inputtextcallbackdata_class = {
    .class_name = "ImGuiInputTextCallbackData",
    .finalizer = js_imgui_inputtextcallbackdata_finalizer,
};

static const JSCFunctionListEntry js_imgui_inputtextcallbackdata_funcs[] = {
    JS_CFUNC_MAGIC_DEF("DeleteChars", 2, js_imgui_inputtextcallbackdata_functions, INPUTTEXTCALLBACKDATA_DELETE_CHARS),
    JS_CFUNC_MAGIC_DEF("InsertChars", 2, js_imgui_inputtextcallbackdata_functions, INPUTTEXTCALLBACKDATA_INSERT_CHARS),
    JS_CFUNC_MAGIC_DEF("SelectAll", 0, js_imgui_inputtextcallbackdata_functions, INPUTTEXTCALLBACKDATA_SELECT_ALL),
    JS_CFUNC_MAGIC_DEF("ClearSelection", 0, js_imgui_inputtextcallbackdata_functions, INPUTTEXTCALLBACKDATA_CLEAR_SELECTION),
    JS_CFUNC_MAGIC_DEF("HasSelection", 0, js_imgui_inputtextcallbackdata_functions, INPUTTEXTCALLBACKDATA_HAS_SELECTION),
};

#endif // defined(QUICKJS_IMGUI_INPUTTEXTCALLBACKDATA_HPP)
