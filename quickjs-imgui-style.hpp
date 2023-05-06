#ifndef QUICKJS_IMGUI_STYLE_HPP
#define QUICKJS_IMGUI_STYLE_HPP

thread_local VISIBLE JSClassID js_imgui_style_class_id = 0;
thread_local JSValue imgui_style_proto = {JS_TAG_UNDEFINED}, imgui_style_ctor = {JS_TAG_UNDEFINED};

enum {
  STYLE_SCALE_ALL_SIZES,
  STYLE_ALPHA,
  STYLE_DISABLED_ALPHA,
  STYLE_WINDOW_PADDING,
  STYLE_WINDOW_ROUNDING,
  STYLE_WINDOW_BORDER_SIZE,
  STYLE_WINDOW_MIN_SIZE,
  STYLE_WINDOW_TITLE_ALIGN,
  STYLE_WINDOW_MENU_BUTTON_POSITION,
  STYLE_CHILD_ROUNDING,
  STYLE_CHILD_BORDER_SIZE,
  STYLE_POPUP_ROUNDING,
  STYLE_POPUP_BORDER_SIZE,
  STYLE_FRAME_PADDING,
  STYLE_FRAME_ROUNDING,
  STYLE_FRAME_BORDER_SIZE,
  STYLE_ITEM_SPACING,
  STYLE_ITEM_INNER_SPACING,
  STYLE_CELL_PADDING,
  STYLE_TOUCH_EXTRA_PADDING,
  STYLE_INDENT_SPACING,
  STYLE_COLUMNS_MIN_SPACING,
  STYLE_SCROLLBAR_SIZE,
  STYLE_SCROLLBAR_ROUNDING,
  STYLE_GRAB_MIN_SIZE,
  STYLE_GRAB_ROUNDING,
  STYLE_LOG_SLIDER_DEADZONE,
  STYLE_TAB_ROUNDING,
  STYLE_TAB_BORDER_SIZE,
  STYLE_TAB_MIN_WIDTH_FOR_CLOSE_BUTTON,
  STYLE_COLOR_BUTTON_POSITION,
  STYLE_BUTTON_TEXT_ALIGN,
  STYLE_SELECTABLE_TEXT_ALIGN,
  STYLE_DISPLAY_WINDOW_PADDING,
  STYLE_DISPLAY_SAFE_AREA_PADDING,
  STYLE_MOUSE_CURSOR_SCALE,
  STYLE_ANTI_ALIASED_LINES,
  STYLE_ANTI_ALIASED_LINES_USE_TEX,
  STYLE_ANTI_ALIASED_FILL,
  STYLE_CURVE_TESSELLATION_TOL,
  STYLE_CIRCLE_TESSELLATION_MAX_ERROR,
  STYLE_COLORS,
};

static inline ImGuiStyle*
js_imgui_style_data2(JSContext* ctx, JSValueConst value) {
  return static_cast<ImGuiStyle*>(JS_GetOpaque2(ctx, value, js_imgui_style_class_id));
}

static JSValue
js_imgui_style_wrap(JSContext* ctx, ImGuiStyle* style) {
  JSValue obj = JS_NewObjectProtoClass(ctx, imgui_style_proto, js_imgui_style_class_id);
  JS_SetOpaque(obj, style);
  return obj;
}

static JSValue
js_imgui_style_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  JSValue proto, obj = JS_UNDEFINED;
  ImGuiStyle* style = new ImGuiStyle();

  /* using new_target to get the prototype is necessary when the class is extended. */
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;
  obj = JS_NewObjectProtoClass(ctx, proto, js_imgui_style_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, style);

  return obj;
fail:
  js_free(ctx, style);
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

static void
js_imgui_style_finalizer(JSRuntime* rt, JSValue val) {
  ImGuiStyle* style = static_cast<ImGuiStyle*>(JS_GetOpaque(val, js_imgui_style_class_id));
  if(style) {
    delete style;
  }
  /// JS_FreeValueRT(rt, val);
}

static JSValue
js_imgui_style_get(JSContext* ctx, JSValueConst this_val, int magic) {
  ImGuiStyle* style;
  JSValue ret = JS_UNDEFINED;

  if(!(style = js_imgui_style_data2(ctx, this_val)))
    return ret;

  switch(magic) {
    case STYLE_ALPHA: {
      ret = JS_NewFloat64(ctx, style->Alpha);
      break;
    }
    case STYLE_DISABLED_ALPHA: {
      ret = JS_NewFloat64(ctx, style->DisabledAlpha);
      break;
    }
    case STYLE_WINDOW_PADDING: {
      ret = js_imgui_newimvec2(ctx, style->WindowPadding);
      break;
    }
    case STYLE_WINDOW_ROUNDING: {
      ret = JS_NewFloat64(ctx, style->WindowRounding);
      break;
    }
    case STYLE_WINDOW_BORDER_SIZE: {
      ret = JS_NewFloat64(ctx, style->WindowBorderSize);
      break;
    }
    case STYLE_WINDOW_MIN_SIZE: {
      ret = js_imgui_newimvec2(ctx, style->WindowMinSize);
      break;
    }
    case STYLE_WINDOW_TITLE_ALIGN: {
      ret = js_imgui_newimvec2(ctx, style->WindowTitleAlign);
      break;
    }
    case STYLE_WINDOW_MENU_BUTTON_POSITION: {
      ret = JS_NewInt32(ctx, style->WindowMenuButtonPosition);
      break;
    }
    case STYLE_CHILD_ROUNDING: {
      ret = JS_NewFloat64(ctx, style->ChildRounding);
      break;
    }
    case STYLE_CHILD_BORDER_SIZE: {
      ret = JS_NewFloat64(ctx, style->ChildBorderSize);
      break;
    }
    case STYLE_POPUP_ROUNDING: {
      ret = JS_NewFloat64(ctx, style->PopupRounding);
      break;
    }
    case STYLE_POPUP_BORDER_SIZE: {
      ret = JS_NewFloat64(ctx, style->PopupBorderSize);
      break;
    }
    case STYLE_FRAME_PADDING: {
      ret = js_imgui_newimvec2(ctx, style->FramePadding);
      break;
    }
    case STYLE_FRAME_ROUNDING: {
      ret = JS_NewFloat64(ctx, style->FrameRounding);
      break;
    }
    case STYLE_FRAME_BORDER_SIZE: {
      ret = JS_NewFloat64(ctx, style->FrameBorderSize);
      break;
    }
    case STYLE_ITEM_SPACING: {
      ret = js_imgui_newimvec2(ctx, style->ItemSpacing);
      break;
    }
    case STYLE_ITEM_INNER_SPACING: {
      ret = js_imgui_newimvec2(ctx, style->ItemInnerSpacing);
      break;
    }
    case STYLE_CELL_PADDING: {
      ret = js_imgui_newimvec2(ctx, style->CellPadding);
      break;
    }
    case STYLE_TOUCH_EXTRA_PADDING: {
      ret = js_imgui_newimvec2(ctx, style->TouchExtraPadding);
      break;
    }
    case STYLE_INDENT_SPACING: {
      ret = JS_NewFloat64(ctx, style->IndentSpacing);
      break;
    }
    case STYLE_COLUMNS_MIN_SPACING: {
      ret = JS_NewFloat64(ctx, style->ColumnsMinSpacing);
      break;
    }
    case STYLE_SCROLLBAR_SIZE: {
      ret = JS_NewFloat64(ctx, style->ScrollbarSize);
      break;
    }
    case STYLE_SCROLLBAR_ROUNDING: {
      ret = JS_NewFloat64(ctx, style->ScrollbarRounding);
      break;
    }
    case STYLE_GRAB_MIN_SIZE: {
      ret = JS_NewFloat64(ctx, style->GrabMinSize);
      break;
    }
    case STYLE_GRAB_ROUNDING: {
      ret = JS_NewFloat64(ctx, style->GrabRounding);
      break;
    }
    case STYLE_LOG_SLIDER_DEADZONE: {
      ret = JS_NewFloat64(ctx, style->LogSliderDeadzone);
      break;
    }
    case STYLE_TAB_ROUNDING: {
      ret = JS_NewFloat64(ctx, style->TabRounding);
      break;
    }
    case STYLE_TAB_BORDER_SIZE: {
      ret = JS_NewFloat64(ctx, style->TabBorderSize);
      break;
    }
    case STYLE_TAB_MIN_WIDTH_FOR_CLOSE_BUTTON: {
      ret = JS_NewFloat64(ctx, style->TabMinWidthForCloseButton);
      break;
    }
    case STYLE_COLOR_BUTTON_POSITION: {
      ret = JS_NewInt32(ctx, style->ColorButtonPosition);
      break;
    }
    case STYLE_BUTTON_TEXT_ALIGN: {
      ret = js_imgui_newimvec2(ctx, style->ButtonTextAlign);
      break;
    }
    case STYLE_SELECTABLE_TEXT_ALIGN: {
      ret = js_imgui_newimvec2(ctx, style->SelectableTextAlign);
      break;
    }
    case STYLE_DISPLAY_WINDOW_PADDING: {
      ret = js_imgui_newimvec2(ctx, style->DisplayWindowPadding);
      break;
    }
    case STYLE_DISPLAY_SAFE_AREA_PADDING: {
      ret = js_imgui_newimvec2(ctx, style->DisplaySafeAreaPadding);
      break;
    }
    case STYLE_MOUSE_CURSOR_SCALE: {
      ret = JS_NewFloat64(ctx, style->MouseCursorScale);
      break;
    }
    case STYLE_ANTI_ALIASED_LINES: {
      ret = JS_NewBool(ctx, style->AntiAliasedLines);
      break;
    }
    case STYLE_ANTI_ALIASED_LINES_USE_TEX: {
      ret = JS_NewBool(ctx, style->AntiAliasedLinesUseTex);
      break;
    }
    case STYLE_ANTI_ALIASED_FILL: {
      ret = JS_NewBool(ctx, style->AntiAliasedFill);
      break;
    }
    case STYLE_CURVE_TESSELLATION_TOL: {
      ret = JS_NewFloat64(ctx, style->CurveTessellationTol);
      break;
    }
    case STYLE_CIRCLE_TESSELLATION_MAX_ERROR: {
      ret = JS_NewFloat64(ctx, style->CircleTessellationMaxError);
      break;
    }
    case STYLE_COLORS: {
      uint32_t i;
      ret = JS_NewArray(ctx);
      for(i = 0; i < ImGuiCol_COUNT; i++) JS_SetPropertyUint32(ctx, ret, i, js_imgui_newimvec4(ctx, style->Colors[i]));
      break;
    }
  }

  return ret;
}

static JSValue
js_imgui_style_set(JSContext* ctx, JSValueConst this_val, JSValueConst value, int magic) {
  ImGuiStyle* style;
  JSValue ret = JS_UNDEFINED;

  if(!(style = js_imgui_style_data2(ctx, this_val)))
    return ret;

  switch(magic) {
    case STYLE_ALPHA: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->Alpha = d;
      break;
    }
    case STYLE_DISABLED_ALPHA: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->DisabledAlpha = d;
      break;
    }
    case STYLE_WINDOW_PADDING: {
      style->WindowPadding = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_WINDOW_ROUNDING: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->WindowRounding = d;
      break;
    }
    case STYLE_WINDOW_BORDER_SIZE: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->WindowBorderSize = d;
      break;
    }
    case STYLE_WINDOW_MIN_SIZE: {
      style->WindowMinSize = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_WINDOW_TITLE_ALIGN: {
      style->WindowTitleAlign = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_WINDOW_MENU_BUTTON_POSITION: {
      int32_t i;
      JS_ToInt32(ctx, &i, value);
      style->WindowMenuButtonPosition = i;
      break;
    }
    case STYLE_CHILD_ROUNDING: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->ChildRounding = d;
      break;
    }
    case STYLE_CHILD_BORDER_SIZE: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->ChildBorderSize = d;
      break;
    }
    case STYLE_POPUP_ROUNDING: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->PopupRounding = d;
      break;
    }
    case STYLE_POPUP_BORDER_SIZE: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->PopupBorderSize = d;
      break;
    }
    case STYLE_FRAME_PADDING: {
      style->FramePadding = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_FRAME_ROUNDING: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->FrameRounding = d;
      break;
    }
    case STYLE_FRAME_BORDER_SIZE: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->FrameBorderSize = d;
      break;
    }
    case STYLE_ITEM_SPACING: {
      style->ItemSpacing = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_ITEM_INNER_SPACING: {
      style->ItemInnerSpacing = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_CELL_PADDING: {
      style->CellPadding = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_TOUCH_EXTRA_PADDING: {
      style->TouchExtraPadding = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_INDENT_SPACING: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->IndentSpacing = d;
      break;
    }
    case STYLE_COLUMNS_MIN_SPACING: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->ColumnsMinSpacing = d;
      break;
    }
    case STYLE_SCROLLBAR_SIZE: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->ScrollbarSize = d;
      break;
    }
    case STYLE_SCROLLBAR_ROUNDING: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->ScrollbarRounding = d;
      break;
    }
    case STYLE_GRAB_MIN_SIZE: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->GrabMinSize = d;
      break;
    }
    case STYLE_GRAB_ROUNDING: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->GrabRounding = d;
      break;
    }
    case STYLE_LOG_SLIDER_DEADZONE: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->LogSliderDeadzone = d;
      break;
    }
    case STYLE_TAB_ROUNDING: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->TabRounding = d;
      break;
    }
    case STYLE_TAB_BORDER_SIZE: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->TabBorderSize = d;
      break;
    }
    case STYLE_TAB_MIN_WIDTH_FOR_CLOSE_BUTTON: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->TabMinWidthForCloseButton = d;
      break;
    }
    case STYLE_COLOR_BUTTON_POSITION: {
      int32_t i;
      JS_ToInt32(ctx, &i, value);
      style->ColorButtonPosition = i;
      break;
    }
    case STYLE_BUTTON_TEXT_ALIGN: {
      style->ButtonTextAlign = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_SELECTABLE_TEXT_ALIGN: {
      style->SelectableTextAlign = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_DISPLAY_WINDOW_PADDING: {
      style->DisplayWindowPadding = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_DISPLAY_SAFE_AREA_PADDING: {
      style->DisplaySafeAreaPadding = js_imgui_getimvec2(ctx, value);
      break;
    }
    case STYLE_MOUSE_CURSOR_SCALE: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->MouseCursorScale = d;
      break;
    }
    case STYLE_ANTI_ALIASED_LINES: {
      style->AntiAliasedLines = JS_ToBool(ctx, value);
      break;
    }
    case STYLE_ANTI_ALIASED_LINES_USE_TEX: {
      style->AntiAliasedLinesUseTex = JS_ToBool(ctx, value);
      break;
    }
    case STYLE_ANTI_ALIASED_FILL: {
      style->AntiAliasedFill = JS_ToBool(ctx, value);
      break;
    }
    case STYLE_CURVE_TESSELLATION_TOL: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->CurveTessellationTol = d;
      break;
    }
    case STYLE_CIRCLE_TESSELLATION_MAX_ERROR: {
      double d;
      JS_ToFloat64(ctx, &d, value);
      style->CircleTessellationMaxError = d;
      break;
    }
    case STYLE_COLORS: {
      uint32_t i;
      for(i = 0; i < ImGuiCol_COUNT; i++) {
        JSValue color = JS_GetPropertyUint32(ctx, value, i);
        style->Colors[i] = js_imgui_getimvec4(ctx, color);
        JS_FreeValue(ctx, color);
      }
      break;
    }
  }

  return ret;
}

static JSValue
js_imgui_style_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  ImGuiStyle* style;
  JSValue ret = JS_UNDEFINED;

  if(!(style = js_imgui_style_data2(ctx, this_val)))
    return ret;

  switch(magic) {
    case STYLE_SCALE_ALL_SIZES: {
      double factor;
      JS_ToFloat64(ctx, &factor, argv[0]);
      style->ScaleAllSizes(factor);
      break;
    }
  }

  return ret;
}

static JSClassDef js_imgui_style_class = {
    .class_name = "ImGuiStyle",
    .finalizer = js_imgui_style_finalizer,
};

static const JSCFunctionListEntry js_imgui_style_funcs[] = {
    JS_CFUNC_MAGIC_DEF("ScaleAllSizes", 1, js_imgui_style_functions, STYLE_SCALE_ALL_SIZES),
    JS_CGETSET_MAGIC_DEF("Alpha", js_imgui_style_get, js_imgui_style_set, STYLE_ALPHA),
    JS_CGETSET_MAGIC_DEF("WindowPadding", js_imgui_style_get, js_imgui_style_set, STYLE_WINDOW_PADDING),
    JS_CGETSET_MAGIC_DEF("WindowRounding", js_imgui_style_get, js_imgui_style_set, STYLE_WINDOW_ROUNDING),
    JS_CGETSET_MAGIC_DEF("WindowBorderSize", js_imgui_style_get, js_imgui_style_set, STYLE_WINDOW_BORDER_SIZE),
    JS_CGETSET_MAGIC_DEF("WindowMinSize", js_imgui_style_get, js_imgui_style_set, STYLE_WINDOW_MIN_SIZE),
    JS_CGETSET_MAGIC_DEF("WindowTitleAlign", js_imgui_style_get, js_imgui_style_set, STYLE_WINDOW_TITLE_ALIGN),
    JS_CGETSET_MAGIC_DEF("ChildRounding", js_imgui_style_get, js_imgui_style_set, STYLE_CHILD_ROUNDING),
    JS_CGETSET_MAGIC_DEF("ChildBorderSize", js_imgui_style_get, js_imgui_style_set, STYLE_CHILD_BORDER_SIZE),
    JS_CGETSET_MAGIC_DEF("PopupRounding", js_imgui_style_get, js_imgui_style_set, STYLE_POPUP_ROUNDING),
    JS_CGETSET_MAGIC_DEF("PopupBorderSize", js_imgui_style_get, js_imgui_style_set, STYLE_POPUP_BORDER_SIZE),
    JS_CGETSET_MAGIC_DEF("FramePadding", js_imgui_style_get, js_imgui_style_set, STYLE_FRAME_PADDING),
    JS_CGETSET_MAGIC_DEF("FrameRounding", js_imgui_style_get, js_imgui_style_set, STYLE_FRAME_ROUNDING),
    JS_CGETSET_MAGIC_DEF("FrameBorderSize", js_imgui_style_get, js_imgui_style_set, STYLE_FRAME_BORDER_SIZE),
    JS_CGETSET_MAGIC_DEF("ItemSpacing", js_imgui_style_get, js_imgui_style_set, STYLE_ITEM_SPACING),
    JS_CGETSET_MAGIC_DEF("ItemInnerSpacing", js_imgui_style_get, js_imgui_style_set, STYLE_ITEM_INNER_SPACING),
    JS_CGETSET_MAGIC_DEF("TouchExtraPadding", js_imgui_style_get, js_imgui_style_set, STYLE_TOUCH_EXTRA_PADDING),
    JS_CGETSET_MAGIC_DEF("IndentSpacing", js_imgui_style_get, js_imgui_style_set, STYLE_INDENT_SPACING),
    JS_CGETSET_MAGIC_DEF("ColumnsMinSpacing", js_imgui_style_get, js_imgui_style_set, STYLE_COLUMNS_MIN_SPACING),
    JS_CGETSET_MAGIC_DEF("ScrollbarSize", js_imgui_style_get, js_imgui_style_set, STYLE_SCROLLBAR_SIZE),
    JS_CGETSET_MAGIC_DEF("ScrollbarRounding", js_imgui_style_get, js_imgui_style_set, STYLE_SCROLLBAR_ROUNDING),
    JS_CGETSET_MAGIC_DEF("GrabMinSize", js_imgui_style_get, js_imgui_style_set, STYLE_GRAB_MIN_SIZE),
    JS_CGETSET_MAGIC_DEF("GrabRounding", js_imgui_style_get, js_imgui_style_set, STYLE_GRAB_ROUNDING),
    JS_CGETSET_MAGIC_DEF("TabRounding", js_imgui_style_get, js_imgui_style_set, STYLE_TAB_ROUNDING),
    JS_CGETSET_MAGIC_DEF("TabBorderSize", js_imgui_style_get, js_imgui_style_set, STYLE_TAB_BORDER_SIZE),
    JS_CGETSET_MAGIC_DEF("ButtonTextAlign", js_imgui_style_get, js_imgui_style_set, STYLE_BUTTON_TEXT_ALIGN),
    JS_CGETSET_MAGIC_DEF("SelectableTextAlign", js_imgui_style_get, js_imgui_style_set, STYLE_SELECTABLE_TEXT_ALIGN),
    JS_CGETSET_MAGIC_DEF("DisplayWindowPadding", js_imgui_style_get, js_imgui_style_set, STYLE_DISPLAY_WINDOW_PADDING),
    JS_CGETSET_MAGIC_DEF("DisplaySafeAreaPadding", js_imgui_style_get, js_imgui_style_set, STYLE_DISPLAY_SAFE_AREA_PADDING),
    JS_CGETSET_MAGIC_DEF("MouseCursorScale", js_imgui_style_get, js_imgui_style_set, STYLE_MOUSE_CURSOR_SCALE),
    JS_CGETSET_MAGIC_DEF("AntiAliasedLines", js_imgui_style_get, js_imgui_style_set, STYLE_ANTI_ALIASED_LINES),
    JS_CGETSET_MAGIC_DEF("AntiAliasedFill", js_imgui_style_get, js_imgui_style_set, STYLE_ANTI_ALIASED_FILL),
    JS_CGETSET_MAGIC_DEF("CurveTessellationTol", js_imgui_style_get, js_imgui_style_set, STYLE_CURVE_TESSELLATION_TOL),
    JS_CGETSET_MAGIC_DEF("Colors", js_imgui_style_get, js_imgui_style_set, STYLE_COLORS),

};

#endif // defined(QUICKJS_IMGUI_STYLE_HPP)
