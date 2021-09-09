#ifndef QUICKJS_IMGUI_IO_HPP
#define QUICKJS_IMGUI_IO_HPP

thread_local VISIBLE JSClassID js_imgui_io_class_id = 0;
thread_local JSValue imgui_io_proto = {JS_TAG_UNDEFINED}, imgui_io_ctor = {JS_TAG_UNDEFINED};

enum {
  IO_ADD_INPUT_CHARACTER,
  IO_ADD_INPUT_CHARACTERS,
  IO_CLEAR_INPUT_CHARACTERS,
  IO_ADD_FOCUS_EVENT,
};

static inline ImGuiIO*
js_imgui_io_data2(JSContext* ctx, JSValueConst value) {
  return static_cast<ImGuiIO*>(JS_GetOpaque2(ctx, value, js_imgui_io_class_id));
}

static JSValue
js_imgui_io_wrap(JSContext* ctx, ImGuiIO* io) {
  JSValue obj = JS_NewObjectProtoClass(ctx, imgui_io_proto, js_imgui_io_class_id);
  JS_SetOpaque(obj, io);
  return obj;
}

static JSValue
js_imgui_io_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  ImGuiIO* io;
  JSValue proto, obj = JS_UNDEFINED;

  /* if(!(io = static_cast<ImGuiIO*>(js_mallocz(ctx, sizeof(ImGuiIO)))))
     return JS_EXCEPTION;

   new (io)  ImGuiIO();*/
  io = new ImGuiIO();

  /* using new_target to get the prototype is necessary when the class is extended. */
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;
  obj = JS_NewObjectProtoClass(ctx, proto, js_imgui_io_class_id);
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
js_imgui_io_finalizer(JSRuntime* rt, JSValue val) {
  ImGuiIO* io = static_cast<ImGuiIO*>(JS_GetOpaque(val, js_imgui_io_class_id));
  if(io) {
    delete io;
  }
  JS_FreeValueRT(rt, val);
}

static JSValue
js_imgui_io_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  ImGuiIO* io;
  JSValue ret = JS_UNDEFINED;

  if(!(io = js_imgui_io_data2(ctx, this_val)))
    return ret;

  switch(magic) {
    case IO_ADD_INPUT_CHARACTER: {
      if(JS_IsString(argv[0])) {
        size_t len;
        const char* str = JS_ToCStringLen(ctx, &len, argv[0]);
        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(str);
        int codepoint;
        if((codepoint = unicode_from_utf8(ptr, len, &ptr)) != -1)
          io->AddInputCharacter(codepoint);
        JS_FreeCString(ctx, str);
      } else if(JS_IsNumber(argv[0])) {
        uint32_t n;
        JS_ToUint32(ctx, &n, argv[0]);
        io->AddInputCharacter(n);
      }
      break;
    }
    case IO_ADD_INPUT_CHARACTERS: {
      const char* str = JS_ToCString(ctx, argv[0]);
      io->AddInputCharactersUTF8(str);
      JS_FreeCString(ctx, str);
      break;
    }
    case IO_CLEAR_INPUT_CHARACTERS: {
      io->ClearInputCharacters();
      break;
    }
    case IO_ADD_FOCUS_EVENT: {
      bool focused = JS_ToBool(ctx, argv[0]);
      io->AddFocusEvent(focused);
      break;
    }
  }

  return ret;
}

static JSClassDef js_imgui_io_class = {
    .class_name = "ImGuiIO",
    .finalizer = js_imgui_io_finalizer,
};

static const JSCFunctionListEntry js_imgui_io_funcs[] = {
    JS_CFUNC_MAGIC_DEF("AddInputCharacter", 1, js_imgui_io_functions, IO_ADD_INPUT_CHARACTER),
    JS_CFUNC_MAGIC_DEF("AddInputCharacters", 1, js_imgui_io_functions, IO_ADD_INPUT_CHARACTERS),
    JS_CFUNC_MAGIC_DEF("ClearInputCharacters", 0, js_imgui_io_functions, IO_CLEAR_INPUT_CHARACTERS),
    JS_CFUNC_MAGIC_DEF("AddFocusEvent", 1, js_imgui_io_functions, IO_ADD_FOCUS_EVENT),
};

#endif // defined(QUICKJS_IMGUI_IO_HPP)
