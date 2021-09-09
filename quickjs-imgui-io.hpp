#ifndef QUICKJS_IMGUI_IO_HPP
#define QUICKJS_IMGUI_IO_HPP

thread_local VISIBLE JSClassID js_imgui_io_class_id = 0;
thread_local JSValue imgui_io_proto = {JS_TAG_UNDEFINED}, imgui_io_ctor = {JS_TAG_UNDEFINED};

enum {
  IMGUIIO_CONFIG_FLAGS,
  IMGUIIO_BACKEND_FLAGS,
  IMGUIIO_DISPLAY_SIZE,
  IMGUIIO_DELTA_TIME,
  IMGUIIO_INI_SAVING_RATE,
  IMGUIIO_INI_FILENAME,
  IMGUIIO_LOG_FILENAME,
  IMGUIIO_MOUSE_DOUBLE_CLICK_TIME,
  IMGUIIO_MOUSE_DOUBLE_CLICK_MAX_DIST,
  IMGUIIO_MOUSE_DRAG_THRESHOLD,
  IMGUIIO_KEY_MAP,
  IMGUIIO_KEY_REPEAT_DELAY,
  IMGUIIO_KEY_REPEAT_RATE,
  IMGUIIO_USER_DATA,
  IMGUIIO_FONTS,
  IMGUIIO_FONT_GLOBAL_SCALE,
  IMGUIIO_FONT_ALLOW_USER_SCALING,
  IMGUIIO_FONT_DEFAULT,
  IMGUIIO_DISPLAY_FRAMEBUFFER_SCALE,
  IMGUIIO_MOUSE_DRAW_CURSOR,
  IMGUIIO_CONFIG_MACOSX_BEHAVIORS,
  IMGUIIO_CONFIG_INPUT_TEXT_CURSOR_BLINK,
  IMGUIIO_CONFIG_WINDOWS_RESIZE_FROM_EDGES,
  IMGUIIO_CONFIG_WINDOWS_MOVE_FROM_TITLE_BAR_ONLY,
  IMGUIIO_BACKEND_PLATFORM_NAME,
  IMGUIIO_BACKEND_RENDERER_NAME,
  IMGUIIO_BACKEND_PLATFORM_USER_DATA,
  IMGUIIO_BACKEND_RENDERER_USER_DATA,
  IMGUIIO_BACKEND_LANGUAGE_USER_DATA,
  IMGUIIO_GET_CLIPBOARD_TEXT_FN,
  IMGUIIO_SET_CLIPBOARD_TEXT_FN,
  IMGUIIO_CLIPBOARD_USER_DATA,
  IMGUIIO_IME_SET_INPUT_SCREEN_POS_FN,
  IMGUIIO_IME_WINDOW_HANDLE,
  IMGUIIO_RENDER_DRAW_LISTS_FN,
  IMGUIIO_MOUSE_POS,
  IMGUIIO_MOUSE_DOWN,
  IMGUIIO_MOUSE_WHEEL,
  IMGUIIO_MOUSE_WHEEL_H,
  IMGUIIO_KEY_CTRL,
  IMGUIIO_KEY_SHIFT,
  IMGUIIO_KEY_ALT,
  IMGUIIO_KEY_SUPER,
  IMGUIIO_KEYS_DOWN,
  IMGUIIO_NAV_INPUTS,
  IMGUIIO_WANT_CAPTURE_MOUSE,
  IMGUIIO_WANT_CAPTURE_KEYBOARD,
  IMGUIIO_WANT_TEXT_INPUT,
  IMGUIIO_WANT_SET_MOUSE_POS,
  IMGUIIO_WANT_SAVE_INI_SETTINGS,
  IMGUIIO_NAV_ACTIVE,
  IMGUIIO_NAV_VISIBLE,
  IMGUIIO_FRAMERATE,
  IMGUIIO_METRICS_RENDER_VERTICES,
  IMGUIIO_METRICS_RENDER_INDICES,
  IMGUIIO_METRICS_RENDER_WINDOWS,
  IMGUIIO_METRICS_ACTIVE_WINDOWS,
  IMGUIIO_METRICS_ACTIVE_ALLOCATIONS,
  IMGUIIO_MOUSE_DELTA,
  IMGUIIO_MOUSE_POS_PREV,
  IMGUIIO_MOUSE_CLICKED_POS,
  IMGUIIO_MOUSE_CLICKED_TIME,
  IMGUIIO_MOUSE_CLICKED,
  IMGUIIO_MOUSE_DOUBLE_CLICKED,
  IMGUIIO_MOUSE_RELEASED,
  IMGUIIO_MOUSE_DOWN_OWNED,
  IMGUIIO_MOUSE_DOWN_DURATION,
  IMGUIIO_MOUSE_DOWN_DURATION_PREV,
  IMGUIIO_MOUSE_DRAG_MAX_DISTANCE_ABS,
  IMGUIIO_MOUSE_DRAG_MAX_DISTANCE_SQR,
  IMGUIIO_KEYS_DOWN_DURATION,
  IMGUIIO_KEYS_DOWN_DURATION_PREV,
  IMGUIIO_NAV_INPUTS_DOWN_DURATION,
  IMGUIIO_NAV_INPUTS_DOWN_DURATION_PREV,
  IMGUIIO_INPUT_QUEUE_CHARACTERS
};

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
js_imgui_io_get(JSContext* ctx, JSValueConst this_val, int magic) {
  ImGuiIO* io;
  JSValue ret = JS_UNDEFINED;

  if(!(io = static_cast<ImGuiIO*>(JS_GetOpaque2(ctx, this_val, js_imgui_io_class_id))))
    return ret;

  switch(magic) {
    case IMGUIIO_DELTA_TIME: {
      ret = JS_NewFloat64(ctx, io->DeltaTime);
      break;
    }
    case IMGUIIO_INI_SAVING_RATE: {
      ret = JS_NewFloat64(ctx, io->IniSavingRate);
      break;
    }
  }

  return ret;
}

static JSValue
js_imgui_io_set(JSContext* ctx, JSValueConst this_val, JSValueConst value, int magic) {
  ImGuiIO* io;
  JSValue ret = JS_UNDEFINED;

  if(!(io = static_cast<ImGuiIO*>(JS_GetOpaque2(ctx, this_val, js_imgui_io_class_id))))
    return ret;

  switch(magic) {}

  return ret;
}

static JSClassDef js_imgui_io_class = {
    .class_name = "ImGuiIO",
    .finalizer = js_imgui_io_finalizer,
};

static const JSCFunctionListEntry js_imgui_io_funcs[] = {
    JS_CGETSET_MAGIC_DEF("ConfigFlags", js_imgui_io_get, js_imgui_io_set, IMGUIIO_CONFIG_FLAGS),
    JS_CGETSET_MAGIC_DEF("BackendFlags", js_imgui_io_get, js_imgui_io_set, IMGUIIO_BACKEND_FLAGS),
    JS_CGETSET_MAGIC_DEF("DisplaySize", js_imgui_io_get, js_imgui_io_set, IMGUIIO_DISPLAY_SIZE),
    JS_CGETSET_MAGIC_DEF("DeltaTime", js_imgui_io_get, js_imgui_io_set, IMGUIIO_DELTA_TIME),
    JS_CGETSET_MAGIC_DEF("IniSavingRate", js_imgui_io_get, js_imgui_io_set, IMGUIIO_INI_SAVING_RATE),
    JS_CGETSET_MAGIC_DEF("IniFilename", js_imgui_io_get, js_imgui_io_set, IMGUIIO_INI_FILENAME),
    JS_CGETSET_MAGIC_DEF("LogFilename", js_imgui_io_get, js_imgui_io_set, IMGUIIO_LOG_FILENAME),
    JS_CGETSET_MAGIC_DEF("MouseDoubleClickTime", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DOUBLE_CLICK_TIME),
    JS_CGETSET_MAGIC_DEF("MouseDoubleClickMaxDist", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DOUBLE_CLICK_MAX_DIST),
    JS_CGETSET_MAGIC_DEF("MouseDragThreshold", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DRAG_THRESHOLD),
    JS_CGETSET_MAGIC_DEF("KeyMap", js_imgui_io_get, js_imgui_io_set, IMGUIIO_KEY_MAP),
    JS_CGETSET_MAGIC_DEF("KeyRepeatDelay", js_imgui_io_get, js_imgui_io_set, IMGUIIO_KEY_REPEAT_DELAY),
    JS_CGETSET_MAGIC_DEF("KeyRepeatRate", js_imgui_io_get, js_imgui_io_set, IMGUIIO_KEY_REPEAT_RATE),
    JS_CGETSET_MAGIC_DEF("UserData", js_imgui_io_get, js_imgui_io_set, IMGUIIO_USER_DATA),
    JS_CGETSET_MAGIC_DEF("Fonts", js_imgui_io_get, js_imgui_io_set, IMGUIIO_FONTS),
    JS_CGETSET_MAGIC_DEF("FontGlobalScale", js_imgui_io_get, js_imgui_io_set, IMGUIIO_FONT_GLOBAL_SCALE),
    JS_CGETSET_MAGIC_DEF("FontAllowUserScaling", js_imgui_io_get, js_imgui_io_set, IMGUIIO_FONT_ALLOW_USER_SCALING),
    JS_CGETSET_MAGIC_DEF("FontDefault", js_imgui_io_get, js_imgui_io_set, IMGUIIO_FONT_DEFAULT),
    JS_CGETSET_MAGIC_DEF("DisplayFramebufferScale", js_imgui_io_get, js_imgui_io_set, IMGUIIO_DISPLAY_FRAMEBUFFER_SCALE),
    JS_CGETSET_MAGIC_DEF("MouseDrawCursor", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DRAW_CURSOR),
    JS_CGETSET_MAGIC_DEF("ConfigMacOSXBehaviors", js_imgui_io_get, js_imgui_io_set, IMGUIIO_CONFIG_MACOSX_BEHAVIORS),
    JS_CGETSET_MAGIC_DEF("ConfigInputTextCursorBlink", js_imgui_io_get, js_imgui_io_set, IMGUIIO_CONFIG_INPUT_TEXT_CURSOR_BLINK),
    JS_CGETSET_MAGIC_DEF("ConfigWindowsResizeFromEdges", js_imgui_io_get, js_imgui_io_set, IMGUIIO_CONFIG_WINDOWS_RESIZE_FROM_EDGES),
    JS_CGETSET_MAGIC_DEF("ConfigWindowsMoveFromTitleBarOnly", js_imgui_io_get, js_imgui_io_set, IMGUIIO_CONFIG_WINDOWS_MOVE_FROM_TITLE_BAR_ONLY),
    JS_CGETSET_MAGIC_DEF("BackendPlatformName", js_imgui_io_get, js_imgui_io_set, IMGUIIO_BACKEND_PLATFORM_NAME),
    JS_CGETSET_MAGIC_DEF("BackendRendererName", js_imgui_io_get, js_imgui_io_set, IMGUIIO_BACKEND_RENDERER_NAME),
    JS_CGETSET_MAGIC_DEF("BackendPlatformUserData", js_imgui_io_get, js_imgui_io_set, IMGUIIO_BACKEND_PLATFORM_USER_DATA),
    JS_CGETSET_MAGIC_DEF("BackendRendererUserData", js_imgui_io_get, js_imgui_io_set, IMGUIIO_BACKEND_RENDERER_USER_DATA),
    JS_CGETSET_MAGIC_DEF("BackendLanguageUserData", js_imgui_io_get, js_imgui_io_set, IMGUIIO_BACKEND_LANGUAGE_USER_DATA),
    JS_CGETSET_MAGIC_DEF("GetClipboardTextFn", js_imgui_io_get, js_imgui_io_set, IMGUIIO_GET_CLIPBOARD_TEXT_FN),
    JS_CGETSET_MAGIC_DEF("SetClipboardTextFn", js_imgui_io_get, js_imgui_io_set, IMGUIIO_SET_CLIPBOARD_TEXT_FN),
    JS_CGETSET_MAGIC_DEF("ClipboardUserData", js_imgui_io_get, js_imgui_io_set, IMGUIIO_CLIPBOARD_USER_DATA),
    JS_CGETSET_MAGIC_DEF("ImeSetInputScreenPosFn", js_imgui_io_get, js_imgui_io_set, IMGUIIO_IME_SET_INPUT_SCREEN_POS_FN),
    JS_CGETSET_MAGIC_DEF("ImeWindowHandle", js_imgui_io_get, js_imgui_io_set, IMGUIIO_IME_WINDOW_HANDLE),
    JS_CGETSET_MAGIC_DEF("RenderDrawListsFn", js_imgui_io_get, js_imgui_io_set, IMGUIIO_RENDER_DRAW_LISTS_FN),
    JS_CGETSET_MAGIC_DEF("MousePos", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_POS),
    JS_CGETSET_MAGIC_DEF("MouseDown", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DOWN),
    JS_CGETSET_MAGIC_DEF("MouseWheel", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_WHEEL),
    JS_CGETSET_MAGIC_DEF("MouseWheelH", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_WHEEL_H),
    JS_CGETSET_MAGIC_DEF("KeyCtrl", js_imgui_io_get, js_imgui_io_set, IMGUIIO_KEY_CTRL),
    JS_CGETSET_MAGIC_DEF("KeyShift", js_imgui_io_get, js_imgui_io_set, IMGUIIO_KEY_SHIFT),
    JS_CGETSET_MAGIC_DEF("KeyAlt", js_imgui_io_get, js_imgui_io_set, IMGUIIO_KEY_ALT),
    JS_CGETSET_MAGIC_DEF("KeySuper", js_imgui_io_get, js_imgui_io_set, IMGUIIO_KEY_SUPER),
    JS_CGETSET_MAGIC_DEF("KeysDown", js_imgui_io_get, js_imgui_io_set, IMGUIIO_KEYS_DOWN),
    JS_CGETSET_MAGIC_DEF("NavInputs", js_imgui_io_get, js_imgui_io_set, IMGUIIO_NAV_INPUTS),
    JS_CGETSET_MAGIC_DEF("WantCaptureMouse", js_imgui_io_get, js_imgui_io_set, IMGUIIO_WANT_CAPTURE_MOUSE),
    JS_CGETSET_MAGIC_DEF("WantCaptureKeyboard", js_imgui_io_get, js_imgui_io_set, IMGUIIO_WANT_CAPTURE_KEYBOARD),
    JS_CGETSET_MAGIC_DEF("WantTextInput", js_imgui_io_get, js_imgui_io_set, IMGUIIO_WANT_TEXT_INPUT),
    JS_CGETSET_MAGIC_DEF("WantSetMousePos", js_imgui_io_get, js_imgui_io_set, IMGUIIO_WANT_SET_MOUSE_POS),
    JS_CGETSET_MAGIC_DEF("WantSaveIniSettings", js_imgui_io_get, js_imgui_io_set, IMGUIIO_WANT_SAVE_INI_SETTINGS),
    JS_CGETSET_MAGIC_DEF("NavActive", js_imgui_io_get, js_imgui_io_set, IMGUIIO_NAV_ACTIVE),
    JS_CGETSET_MAGIC_DEF("NavVisible", js_imgui_io_get, js_imgui_io_set, IMGUIIO_NAV_VISIBLE),
    JS_CGETSET_MAGIC_DEF("Framerate", js_imgui_io_get, js_imgui_io_set, IMGUIIO_FRAMERATE),
    JS_CGETSET_MAGIC_DEF("MetricsRenderVertices", js_imgui_io_get, js_imgui_io_set, IMGUIIO_METRICS_RENDER_VERTICES),
    JS_CGETSET_MAGIC_DEF("MetricsRenderIndices", js_imgui_io_get, js_imgui_io_set, IMGUIIO_METRICS_RENDER_INDICES),
    JS_CGETSET_MAGIC_DEF("MetricsRenderWindows", js_imgui_io_get, js_imgui_io_set, IMGUIIO_METRICS_RENDER_WINDOWS),
    JS_CGETSET_MAGIC_DEF("MetricsActiveWindows", js_imgui_io_get, js_imgui_io_set, IMGUIIO_METRICS_ACTIVE_WINDOWS),
    JS_CGETSET_MAGIC_DEF("MetricsActiveAllocations", js_imgui_io_get, js_imgui_io_set, IMGUIIO_METRICS_ACTIVE_ALLOCATIONS),
    JS_CGETSET_MAGIC_DEF("MouseDelta", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DELTA),
    JS_CGETSET_MAGIC_DEF("MousePosPrev", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_POS_PREV),
    JS_CGETSET_MAGIC_DEF("MouseClickedPos", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_CLICKED_POS),
    JS_CGETSET_MAGIC_DEF("MouseClickedTime", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_CLICKED_TIME),
    JS_CGETSET_MAGIC_DEF("MouseClicked", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_CLICKED),
    JS_CGETSET_MAGIC_DEF("MouseDoubleClicked", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DOUBLE_CLICKED),
    JS_CGETSET_MAGIC_DEF("MouseReleased", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_RELEASED),
    JS_CGETSET_MAGIC_DEF("MouseDownOwned", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DOWN_OWNED),
    JS_CGETSET_MAGIC_DEF("MouseDownDuration", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DOWN_DURATION),
    JS_CGETSET_MAGIC_DEF("MouseDownDurationPrev", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DOWN_DURATION_PREV),
    JS_CGETSET_MAGIC_DEF("MouseDragMaxDistanceAbs", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DRAG_MAX_DISTANCE_ABS),
    JS_CGETSET_MAGIC_DEF("MouseDragMaxDistanceSqr", js_imgui_io_get, js_imgui_io_set, IMGUIIO_MOUSE_DRAG_MAX_DISTANCE_SQR),
    JS_CGETSET_MAGIC_DEF("KeysDownDuration", js_imgui_io_get, js_imgui_io_set, IMGUIIO_KEYS_DOWN_DURATION),
    JS_CGETSET_MAGIC_DEF("KeysDownDurationPrev", js_imgui_io_get, js_imgui_io_set, IMGUIIO_KEYS_DOWN_DURATION_PREV),
    JS_CGETSET_MAGIC_DEF("NavInputsDownDuration", js_imgui_io_get, js_imgui_io_set, IMGUIIO_NAV_INPUTS_DOWN_DURATION),
    JS_CGETSET_MAGIC_DEF("NavInputsDownDurationPrev", js_imgui_io_get, js_imgui_io_set, IMGUIIO_NAV_INPUTS_DOWN_DURATION_PREV),
    JS_CGETSET_MAGIC_DEF("InputQueueCharacters", js_imgui_io_get, js_imgui_io_set, IMGUIIO_INPUT_QUEUE_CHARACTERS),
};

#endif // defined(QUICKJS_IMGUI_IO_HPP)
