#ifndef QUICKJS_IMGUI_INPUTTEXTCBD_HPP
#define QUICKJS_IMGUI_INPUTTEXTCBD_HPP

thread_local VISIBLE JSClassID js_imgui_inputtextcallbackdata_class_id = 0;
thread_local JSValue imgui_inputtextcallbackdata_proto = {JS_TAG_UNDEFINED}, imgui_inputtextcallbackdata_ctor = {JS_TAG_UNDEFINED};

enum {
  INPUTTEXTCBD_DELETE_CHARS,
  INPUTTEXTCBD_INSERT_CHARS,
  INPUTTEXTCBD_SELECT_ALL,
  INPUTTEXTCBD_CLEAR_SELECTION,
  INPUTTEXTCBD_HAS_SELECTION,
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

enum {
  INPUTTEXTCBD_EVENT_FLAG,
  INPUTTEXTCBD_FLAGS,
  INPUTTEXTCBD_EVENT_CHAR,
  INPUTTEXTCBD_EVENT_KEY,
  INPUTTEXTCBD_BUF,
  INPUTTEXTCBD_BUF_TEXT_LEN,
  INPUTTEXTCBD_BUF_SIZE,
  INPUTTEXTCBD_BUF_DIRTY,
  INPUTTEXTCBD_CURSOR_POS,
  INPUTTEXTCBD_SELECTION_START,
  INPUTTEXTCBD_SELECTION_END,
};

struct InputTextUserData {
  JSContext* ctx;
  JSValue fn, buf;
};

static JSValue
js_imgui_inputtextcallbackdata_get(JSContext* ctx, JSValueConst this_obj, int magic) {
  ImGuiInputTextCallbackData* itcd;
  JSValue ret = JS_UNDEFINED;
  InputTextUserData* user_data;

  if(!(itcd = static_cast<ImGuiInputTextCallbackData*>(JS_GetOpaque2(ctx, this_obj, js_imgui_inputtextcallbackdata_class_id))))
    return JS_EXCEPTION;

  user_data = static_cast<InputTextUserData*>(itcd->UserData);

  switch(magic) {
    case INPUTTEXTCBD_EVENT_FLAG: {
      ret = JS_NewInt32(ctx, itcd->EventFlag);
      break;
    }
    case INPUTTEXTCBD_FLAGS: {
      ret = JS_NewInt32(ctx, itcd->Flags);
      break;
    }
    case INPUTTEXTCBD_EVENT_CHAR: {
      ret = JS_NewUint32(ctx, itcd->EventChar);
      break;
    }
    case INPUTTEXTCBD_EVENT_KEY: {
      ret = JS_NewUint32(ctx, itcd->EventKey);
      break;
    }
    case INPUTTEXTCBD_BUF: {
      ret = JS_DupValue(ctx, user_data->buf);
      break;
    }
    case INPUTTEXTCBD_BUF_TEXT_LEN: {
      ret = JS_NewUint32(ctx, itcd->BufTextLen);
      break;
    }
    case INPUTTEXTCBD_BUF_SIZE: {
      ret = JS_NewUint32(ctx, itcd->BufSize);
      break;
    }
    case INPUTTEXTCBD_BUF_DIRTY: {
      ret = JS_NewBool(ctx, itcd->BufDirty);
      break;
    }
    case INPUTTEXTCBD_CURSOR_POS: {
      ret = JS_NewInt32(ctx, itcd->CursorPos);
      break;
    }
    case INPUTTEXTCBD_SELECTION_START: {
      ret = JS_NewInt32(ctx, itcd->SelectionStart);
      break;
    }
    case INPUTTEXTCBD_SELECTION_END: {
      ret = JS_NewInt32(ctx, itcd->SelectionEnd);
      break;
    }
  }
  return ret;
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

    case INPUTTEXTCBD_DELETE_CHARS: {
      int32_t pos, bytes_count;
      JS_ToInt32(ctx, &pos, argv[0]);
      JS_ToInt32(ctx, &bytes_count, argv[1]);
      itcd->DeleteChars(pos, bytes_count);
      break;
    }
    case INPUTTEXTCBD_INSERT_CHARS: {
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
    case INPUTTEXTCBD_SELECT_ALL: {
      itcd->SelectAll();
      break;
    }
    case INPUTTEXTCBD_CLEAR_SELECTION: {
      itcd->ClearSelection();
      break;
    }
    case INPUTTEXTCBD_HAS_SELECTION: {
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
    JS_CGETSET_MAGIC_DEF("EventFlag", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_EVENT_FLAG),
    JS_CGETSET_MAGIC_DEF("Flags", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_FLAGS),
    JS_CGETSET_MAGIC_DEF("EventChar", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_EVENT_CHAR),
    JS_CGETSET_MAGIC_DEF("EventKey", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_EVENT_KEY),
    JS_CGETSET_MAGIC_DEF("buf", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_BUF),
    JS_CGETSET_MAGIC_DEF("BufTextLen", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_BUF_TEXT_LEN),
    JS_CGETSET_MAGIC_DEF("BufSize", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_BUF_SIZE),
    JS_CGETSET_MAGIC_DEF("BufDirty", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_BUF_DIRTY),
    JS_CGETSET_MAGIC_DEF("CursorPos", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_CURSOR_POS),
    JS_CGETSET_MAGIC_DEF("SelectionStart", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_SELECTION_START),
    JS_CGETSET_MAGIC_DEF("SelectionEnd", js_imgui_inputtextcallbackdata_get, 0, INPUTTEXTCBD_SELECTION_END),
    JS_CFUNC_MAGIC_DEF("DeleteChars", 2, js_imgui_inputtextcallbackdata_functions, INPUTTEXTCBD_DELETE_CHARS),
    JS_CFUNC_MAGIC_DEF("InsertChars", 2, js_imgui_inputtextcallbackdata_functions, INPUTTEXTCBD_INSERT_CHARS),
    JS_CFUNC_MAGIC_DEF("SelectAll", 0, js_imgui_inputtextcallbackdata_functions, INPUTTEXTCBD_SELECT_ALL),
    JS_CFUNC_MAGIC_DEF("ClearSelection", 0, js_imgui_inputtextcallbackdata_functions, INPUTTEXTCBD_CLEAR_SELECTION),
    JS_CFUNC_MAGIC_DEF("HasSelection", 0, js_imgui_inputtextcallbackdata_functions, INPUTTEXTCBD_HAS_SELECTION),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "ImGuiInputTextCallbackData", JS_PROP_CONFIGURABLE),
};

#endif // defined(QUICKJS_IMGUI_INPUTTEXTCBD_HPP)
