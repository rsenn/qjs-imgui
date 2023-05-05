#ifndef QUICKJS_IMFONTATLAS_HPP
#define QUICKJS_IMFONTATLAS_HPP

thread_local VISIBLE JSClassID js_imfontatlas_class_id = 0;
thread_local JSValue imfontatlas_proto = {JS_TAG_UNDEFINED}, imfontatlas_ctor = {JS_TAG_UNDEFINED};

enum {
  FONTATLAS_ADD_FONT,
  FONTATLAS_ADD_FONT_DEFAULT,
  FONTATLAS_ADD_FONT_FROM_FILE_TTF,
  FONTATLAS_ADD_FONT_FROM_MEMORY_TTF,
  FONTATLAS_ADD_FONT_FROM_MEMORY_COMPRESSED_TTF,
  FONTATLAS_ADD_FONT_FROM_MEMORY_COMPRESSED_BASE85_TTF,
  FONTATLAS_CLEAR_INPUT_DATA,
  FONTATLAS_CLEAR_TEX_DATA,
  FONTATLAS_CLEAR_FONTS,
  FONTATLAS_CLEAR,
  FONTATLAS_BUILD,
  FONTATLAS_GET_TEX_DATA_AS_ALPHA8,
  FONTATLAS_GET_TEX_DATA_ASRGBA32,
  FONTATLAS_GET_GLYPH_RANGES_DEFAULT,
  FONTATLAS_GET_GLYPH_RANGES_KOREAN,
  FONTATLAS_GET_GLYPH_RANGES_JAPANESE,
  FONTATLAS_GET_GLYPH_RANGES_CHINESE_FULL,
  FONTATLAS_GET_GLYPH_RANGES_CHINESE_SIMPLIFIED_COMMON,
  FONTATLAS_GET_GLYPH_RANGES_CYRILLIC,
  FONTATLAS_GET_GLYPH_RANGES_THAI,
  FONTATLAS_GET_GLYPH_RANGES_VIETNAMESE,
  FONTATLAS_ADD_CUSTOM_RECT_REGULAR,
  FONTATLAS_ADD_CUSTOM_RECT_FONT_GLYPH,
  FONTATLAS_CALC_CUSTOM_RECT_UV,
  FONTATLAS_GET_MOUSE_CURSOR_TEX_DATA,
};

static inline ImFontAtlas*
js_imfontatlas_data(JSValueConst value) {
  return static_cast<ImFontAtlas*>(JS_GetOpaque(value, js_imfontatlas_class_id));
}

static inline ImFontAtlas*
js_imfontatlas_data2(JSContext* ctx, JSValueConst value) {
  return static_cast<ImFontAtlas*>(JS_GetOpaque2(ctx, value, js_imfontatlas_class_id));
}

static JSValue
js_imfontatlas_wrap(JSContext* ctx, ImFontAtlas* payload) {
  JSValue obj = JS_NewObjectProtoClass(ctx, imfontatlas_proto, js_imfontatlas_class_id);
  JS_SetOpaque(obj, payload);
  return obj;
}

static JSValue
js_imfontatlas_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  JSValue proto, obj = JS_UNDEFINED;
  ImFontAtlas* payload = new ImFontAtlas();
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;
  obj = JS_NewObjectProtoClass(ctx, proto, js_imfontatlas_class_id);
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
js_imfontatlas_finalizer(JSRuntime* rt, JSValue val) {
  ImFontAtlas* payload = static_cast<ImFontAtlas*>(JS_GetOpaque(val, js_imfontatlas_class_id));
  if(payload) {
    delete payload;
  }
  JS_FreeValueRT(rt, val);
}

static JSValue
js_imfontatlas_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  ImFontAtlas* payload;
  JSValue ret = JS_UNDEFINED;

  if(!(payload = js_imfontatlas_data2(ctx, this_val)))
    return ret;

  switch(magic) {}

  return ret;
}

static JSClassDef js_imfontatlas_class = {
    .class_name = "ImFontAtlas",
    .finalizer = js_imfontatlas_finalizer,
};

static const JSCFunctionListEntry js_imfontatlas_funcs[] = {
    JS_CFUNC_MAGIC_DEF("AddFont", 0, js_imfont_functions, FONTATLAS_ADD_FONT),
    JS_CFUNC_MAGIC_DEF("AddFontDefault", 0, js_imfont_functions, FONTATLAS_ADD_FONT_DEFAULT),
    JS_CFUNC_MAGIC_DEF("AddFontFromFileTTF", 0, js_imfont_functions, FONTATLAS_ADD_FONT_FROM_FILE_TTF),
    JS_CFUNC_MAGIC_DEF("AddFontFromMemoryTTF", 0, js_imfont_functions, FONTATLAS_ADD_FONT_FROM_MEMORY_TTF),
    JS_CFUNC_MAGIC_DEF("AddFontFromMemoryCompressedTTF", 0, js_imfont_functions, FONTATLAS_ADD_FONT_FROM_MEMORY_COMPRESSED_TTF),
    JS_CFUNC_MAGIC_DEF("AddFontFromMemoryCompressedBase85TTF", 0, js_imfont_functions, FONTATLAS_ADD_FONT_FROM_MEMORY_COMPRESSED_BASE85_TTF),
    JS_CFUNC_MAGIC_DEF("ClearInputData", 0, js_imfont_functions, FONTATLAS_CLEAR_INPUT_DATA),
    JS_CFUNC_MAGIC_DEF("ClearTexData", 0, js_imfont_functions, FONTATLAS_CLEAR_TEX_DATA),
    JS_CFUNC_MAGIC_DEF("ClearFonts", 0, js_imfont_functions, FONTATLAS_CLEAR_FONTS),
    JS_CFUNC_MAGIC_DEF("Clear", 0, js_imfont_functions, FONTATLAS_CLEAR),
    JS_CFUNC_MAGIC_DEF("Build", 0, js_imfont_functions, FONTATLAS_BUILD),
    JS_CFUNC_MAGIC_DEF("GetTexDataAsAlpha8", 0, js_imfont_functions, FONTATLAS_GET_TEX_DATA_AS_ALPHA8),
    JS_CFUNC_MAGIC_DEF("GetTexDataAsRGBA32", 0, js_imfont_functions, FONTATLAS_GET_TEX_DATA_ASRGBA32),
    JS_CFUNC_MAGIC_DEF("GetGlyphRangesDefault", 0, js_imfont_functions, FONTATLAS_GET_GLYPH_RANGES_DEFAULT),
    JS_CFUNC_MAGIC_DEF("GetGlyphRangesKorean", 0, js_imfont_functions, FONTATLAS_GET_GLYPH_RANGES_KOREAN),
    JS_CFUNC_MAGIC_DEF("GetGlyphRangesJapanese", 0, js_imfont_functions, FONTATLAS_GET_GLYPH_RANGES_JAPANESE),
    JS_CFUNC_MAGIC_DEF("GetGlyphRangesChineseFull", 0, js_imfont_functions, FONTATLAS_GET_GLYPH_RANGES_CHINESE_FULL),
    JS_CFUNC_MAGIC_DEF("GetGlyphRangesChineseSimplifiedCommon", 0, js_imfont_functions, FONTATLAS_GET_GLYPH_RANGES_CHINESE_SIMPLIFIED_COMMON),
    JS_CFUNC_MAGIC_DEF("GetGlyphRangesCyrillic", 0, js_imfont_functions, FONTATLAS_GET_GLYPH_RANGES_CYRILLIC),
    JS_CFUNC_MAGIC_DEF("GetGlyphRangesThai", 0, js_imfont_functions, FONTATLAS_GET_GLYPH_RANGES_THAI),
    JS_CFUNC_MAGIC_DEF("GetGlyphRangesVietnamese", 0, js_imfont_functions, FONTATLAS_GET_GLYPH_RANGES_VIETNAMESE),
    JS_CFUNC_MAGIC_DEF("AddCustomRectRegular", 0, js_imfont_functions, FONTATLAS_ADD_CUSTOM_RECT_REGULAR),
    JS_CFUNC_MAGIC_DEF("AddCustomRectFontGlyph", 0, js_imfont_functions, FONTATLAS_ADD_CUSTOM_RECT_FONT_GLYPH),
    JS_CFUNC_MAGIC_DEF("CalcCustomRectUV", 0, js_imfont_functions, FONTATLAS_CALC_CUSTOM_RECT_UV),
    JS_CFUNC_MAGIC_DEF("GetMouseCursorTexData", 0, js_imfont_functions, FONTATLAS_GET_MOUSE_CURSOR_TEX_DATA),
};

#endif // defined(QUICKJS_IMFONTATLAS_HPP)
