#ifndef QUICKJS_IMGUI_STYLE_HPP
#define QUICKJS_IMGUI_STYLE_HPP

thread_local VISIBLE JSClassID js_imgui_style_class_id = 0;
thread_local JSValue imgui_style_proto = {JS_TAG_UNDEFINED}, imgui_style_ctor = {JS_TAG_UNDEFINED};

enum {
  IMGUISTYLE_CONFIG_FLAGS,
IMGUISTYLE_BACKEND_FLAGS,
IMGUISTYLE_DISPLAY_SIZE,
IMGUISTYLE_DELTA_TIME,
IMGUISTYLE_INI_SAVING_RATE,
IMGUISTYLE_INI_FILENAME,
IMGUISTYLE_LOG_FILENAME,
IMGUISTYLE_MOUSE_DOUBLE_CLICK_TIME,
IMGUISTYLE_MOUSE_DOUBLE_CLICK_MAX_DIST,
IMGUISTYLE_MOUSE_DRAG_THRESHOLD,
IMGUISTYLE_KEY_MAP,
IMGUISTYLE_KEY_REPEAT_DELAY,
IMGUISTYLE_KEY_REPEAT_RATE,
IMGUISTYLE_USER_DATA,
IMGUISTYLE_FONTS,
IMGUISTYLE_FONT_GLOBAL_SCALE,
IMGUISTYLE_FONT_ALLOW_USER_SCALING,
IMGUISTYLE_FONT_DEFAULT,
IMGUISTYLE_DISPLAY_FRAMEBUFFER_SCALE,
IMGUISTYLE_MOUSE_DRAW_CURSOR,
IMGUISTYLE_CONFIG_MACOSX_BEHAVIORS,
IMGUISTYLE_CONFIG_INPUT_TEXT_CURSOR_BLINK,
IMGUISTYLE_CONFIG_WINDOWS_RESIZE_FROM_EDGES,
IMGUISTYLE_CONFIG_WINDOWS_MOVE_FROM_TITLE_BAR_ONLY,
IMGUISTYLE_BACKEND_PLATFORM_NAME,
IMGUISTYLE_BACKEND_RENDERER_NAME,
IMGUISTYLE_BACKEND_PLATFORM_USER_DATA,
IMGUISTYLE_BACKEND_RENDERER_USER_DATA,
IMGUISTYLE_BACKEND_LANGUAGE_USER_DATA,
IMGUISTYLE_GET_CLIPBOARD_TEXT_FN,
IMGUISTYLE_SET_CLIPBOARD_TEXT_FN,
IMGUISTYLE_CLIPBOARD_USER_DATA,
IMGUISTYLE_IME_SET_INPUT_SCREEN_POS_FN,
IMGUISTYLE_IME_WINDOW_HANDLE,
IMGUISTYLE_RENDER_DRAW_LISTS_FN,
IMGUISTYLE_MOUSE_POS,
IMGUISTYLE_MOUSE_DOWN,
IMGUISTYLE_MOUSE_WHEEL,
IMGUISTYLE_MOUSE_WHEEL_H,
IMGUISTYLE_KEY_CTRL,
IMGUISTYLE_KEY_SHIFT,
IMGUISTYLE_KEY_ALT,
IMGUISTYLE_KEY_SUPER,
IMGUISTYLE_KEYS_DOWN,
IMGUISTYLE_NAV_INPUTS,
IMGUISTYLE_WANT_CAPTURE_MOUSE,
IMGUISTYLE_WANT_CAPTURE_KEYBOARD,
IMGUISTYLE_WANT_TEXT_INPUT,
IMGUISTYLE_WANT_SET_MOUSE_POS,
IMGUISTYLE_WANT_SAVE_INI_SETTINGS,
IMGUISTYLE_NAV_ACTIVE,
IMGUISTYLE_NAV_VISIBLE,
IMGUISTYLE_FRAMERATE,
IMGUISTYLE_METRICS_RENDER_VERTICES,
IMGUISTYLE_METRICS_RENDER_INDICES,
IMGUISTYLE_METRICS_RENDER_WINDOWS,
IMGUISTYLE_METRICS_ACTIVE_WINDOWS,
IMGUISTYLE_METRICS_ACTIVE_ALLOCATIONS,
IMGUISTYLE_MOUSE_DELTA,
IMGUISTYLE_MOUSE_POS_PREV,
IMGUISTYLE_MOUSE_CLICKED_POS,
IMGUISTYLE_MOUSE_CLICKED_TIME,
IMGUISTYLE_MOUSE_CLICKED,
IMGUISTYLE_MOUSE_DOUBLE_CLICKED,
IMGUISTYLE_MOUSE_RELEASED,
IMGUISTYLE_MOUSE_DOWN_OWNED,
IMGUISTYLE_MOUSE_DOWN_DURATION,
IMGUISTYLE_MOUSE_DOWN_DURATION_PREV,
IMGUISTYLE_MOUSE_DRAG_MAX_DISTANCE_ABS,
IMGUISTYLE_MOUSE_DRAG_MAX_DISTANCE_SQR,
IMGUISTYLE_KEYS_DOWN_DURATION,
IMGUISTYLE_KEYS_DOWN_DURATION_PREV,
IMGUISTYLE_NAV_INPUTS_DOWN_DURATION,
IMGUISTYLE_NAV_INPUTS_DOWN_DURATION_PREV,
IMGUISTYLE_INPUT_QUEUE_CHARACTERS,
IMGUISTYLE_DELTA_TIME,
IMGUISTYLE_INI_SAVING_RATE,
IMGUISTYLE_ALPHA,
IMGUISTYLE_WINDOW_PADDING,
IMGUISTYLE_WINDOW_ROUNDING,
IMGUISTYLE_WINDOW_BORDER_SIZE,
IMGUISTYLE_WINDOW_MIN_SIZE,
IMGUISTYLE_WINDOW_TITLE_ALIGN,
IMGUISTYLE_CHILD_ROUNDING,
IMGUISTYLE_CHILD_BORDER_SIZE,
IMGUISTYLE_POPUP_ROUNDING,
IMGUISTYLE_POPUP_BORDER_SIZE,
IMGUISTYLE_FRAME_PADDING,
IMGUISTYLE_FRAME_ROUNDING,
IMGUISTYLE_FRAME_BORDER_SIZE,
IMGUISTYLE_ITEM_SPACING,
IMGUISTYLE_ITEM_INNER_SPACING,
IMGUISTYLE_TOUCH_EXTRA_PADDING,
IMGUISTYLE_INDENT_SPACING,
IMGUISTYLE_COLUMNS_MIN_SPACING,
IMGUISTYLE_SCROLLBAR_SIZE,
IMGUISTYLE_SCROLLBAR_ROUNDING,
IMGUISTYLE_GRAB_MIN_SIZE,
IMGUISTYLE_GRAB_ROUNDING,
IMGUISTYLE_TAB_ROUNDING,
IMGUISTYLE_TAB_BORDER_SIZE,
IMGUISTYLE_BUTTON_TEXT_ALIGN,
IMGUISTYLE_SELECTABLE_TEXT_ALIGN,
IMGUISTYLE_DISPLAY_WINDOW_PADDING,
IMGUISTYLE_DISPLAY_SAFE_AREA_PADDING,
IMGUISTYLE_MOUSE_CURSOR_SCALE,
IMGUISTYLE_ANTI_ALIASED_LINES,
IMGUISTYLE_ANTI_ALIASED_FILL,
IMGUISTYLE_CURVE_TESSELLATION_TOL,
IMGUISTYLE_COLORS,

};

static JSValue
js_imgui_style_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  ImGuiStyle* io;
  JSValue proto, obj = JS_UNDEFINED;

  /* if(!(io = static_cast<ImGuiStyle*>(js_mallocz(ctx, sizeof(ImGuiStyle)))))
     return JS_EXCEPTION;

   new (io)  ImGuiStyle();*/
  io = new ImGuiStyle();

  /* using new_target to get the prototype is necessary when the class is extended. */
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;
  obj = JS_NewObjectProtoClass(ctx, proto, js_imgui_style_class_id);
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
js_imgui_style_finalizer(JSRuntime* rt, JSValue val) {
  ImGuiStyle* io = static_cast<ImGuiStyle*>(JS_GetOpaque(val, js_imgui_style_class_id));
  if(io) {
    delete io;
  }
  JS_FreeValueRT(rt, val);
}

static JSValue
js_imgui_style_get(JSContext* ctx, JSValueConst this_val, int magic) {
  ImGuiStyle* io;
  JSValue ret = JS_UNDEFINED;

  if(!(io = static_cast<ImGuiStyle*>(JS_GetOpaque2(ctx, this_val, js_imgui_style_class_id))))
    return ret;

  switch(magic) {  case IMGUISTYLE_DELTA_TIME: {
      ret = JS_NewFloat64(ctx, io->DeltaTime);
      break;
    }
    case IMGUISTYLE_INI_SAVING_RATE: {
      ret = JS_NewFloat64(ctx, io->IniSavingRate);
      break;
    }}

  return ret;
}

static JSValue
js_imgui_style_set(JSContext* ctx, JSValueConst this_val, JSValueConst value, int magic) {
  ImGuiStyle* io;
  JSValue ret = JS_UNDEFINED;

  if(!(io = static_cast<ImGuiStyle*>(JS_GetOpaque2(ctx, this_val, js_imgui_style_class_id))))
    return ret;

  switch(magic) {
  
  }

  return ret;
}

static JSClassDef js_imgui_style_class = {
    .class_name = "ImGuiStyle",
    .finalizer = js_imgui_style_finalizer,
};

static const JSCFunctionListEntry js_imgui_style_funcs[] = {
    JS_CGETSET_MAGIC_DEF("Alpha", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_ALPHA),
  JS_CGETSET_MAGIC_DEF("WindowPadding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_WINDOW_PADDING),
  JS_CGETSET_MAGIC_DEF("WindowRounding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_WINDOW_ROUNDING),
  JS_CGETSET_MAGIC_DEF("WindowBorderSize", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_WINDOW_BORDER_SIZE),
  JS_CGETSET_MAGIC_DEF("WindowMinSize", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_WINDOW_MIN_SIZE),
  JS_CGETSET_MAGIC_DEF("WindowTitleAlign", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_WINDOW_TITLE_ALIGN),
  JS_CGETSET_MAGIC_DEF("ChildRounding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_CHILD_ROUNDING),
  JS_CGETSET_MAGIC_DEF("ChildBorderSize", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_CHILD_BORDER_SIZE),
  JS_CGETSET_MAGIC_DEF("PopupRounding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_POPUP_ROUNDING),
  JS_CGETSET_MAGIC_DEF("PopupBorderSize", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_POPUP_BORDER_SIZE),
  JS_CGETSET_MAGIC_DEF("FramePadding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_FRAME_PADDING),
  JS_CGETSET_MAGIC_DEF("FrameRounding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_FRAME_ROUNDING),
  JS_CGETSET_MAGIC_DEF("FrameBorderSize", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_FRAME_BORDER_SIZE),
  JS_CGETSET_MAGIC_DEF("ItemSpacing", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_ITEM_SPACING),
  JS_CGETSET_MAGIC_DEF("ItemInnerSpacing", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_ITEM_INNER_SPACING),
  JS_CGETSET_MAGIC_DEF("TouchExtraPadding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_TOUCH_EXTRA_PADDING),
  JS_CGETSET_MAGIC_DEF("IndentSpacing", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_INDENT_SPACING),
  JS_CGETSET_MAGIC_DEF("ColumnsMinSpacing", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_COLUMNS_MIN_SPACING),
  JS_CGETSET_MAGIC_DEF("ScrollbarSize", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_SCROLLBAR_SIZE),
  JS_CGETSET_MAGIC_DEF("ScrollbarRounding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_SCROLLBAR_ROUNDING),
  JS_CGETSET_MAGIC_DEF("GrabMinSize", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_GRAB_MIN_SIZE),
  JS_CGETSET_MAGIC_DEF("GrabRounding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_GRAB_ROUNDING),
  JS_CGETSET_MAGIC_DEF("TabRounding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_TAB_ROUNDING),
  JS_CGETSET_MAGIC_DEF("TabBorderSize", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_TAB_BORDER_SIZE),
  JS_CGETSET_MAGIC_DEF("ButtonTextAlign", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_BUTTON_TEXT_ALIGN),
  JS_CGETSET_MAGIC_DEF("SelectableTextAlign", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_SELECTABLE_TEXT_ALIGN),
  JS_CGETSET_MAGIC_DEF("DisplayWindowPadding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_DISPLAY_WINDOW_PADDING),
  JS_CGETSET_MAGIC_DEF("DisplaySafeAreaPadding", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_DISPLAY_SAFE_AREA_PADDING),
  JS_CGETSET_MAGIC_DEF("MouseCursorScale", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_MOUSE_CURSOR_SCALE),
  JS_CGETSET_MAGIC_DEF("AntiAliasedLines", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_ANTI_ALIASED_LINES),
  JS_CGETSET_MAGIC_DEF("AntiAliasedFill", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_ANTI_ALIASED_FILL),
  JS_CGETSET_MAGIC_DEF("CurveTessellationTol", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_CURVE_TESSELLATION_TOL),
  JS_CGETSET_MAGIC_DEF("Colors", js_imgui_style_get, js_imgui_style_set, IMGUISTYLE_COLORS),

};

#endif // defined(QUICKJS_IMGUI_STYLE_HPP)
