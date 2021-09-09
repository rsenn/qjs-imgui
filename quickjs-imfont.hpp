#ifndef QUICKJS_IMFONT_HPP
#define QUICKJS_IMFONT_HPP

thread_local VISIBLE JSClassID js_imfont_class_id = 0;
thread_local JSValue imfont_proto = {JS_TAG_UNDEFINED}, imfont_ctor = {JS_TAG_UNDEFINED};

enum {
  FONT_FIND_GLYPH,
  FONT_FIND_GLYPH_NO_FALLBACK,
  FONT_CALC_TEXT_SIZE_A,
  FONT_CALC_WORD_WRAP_POSITION_A,
  FONT_RENDER_CHAR,
  FONT_RENDER_TEXT,
  FONT_BUILD_LOOKUP_TABLE,
  FONT_CLEAR_OUTPUT_DATA,
  FONT_GROW_INDEX,
  FONT_ADD_GLYPH,
  FONT_ADD_REMAP_CHAR,
  FONT_SET_GLYPH_VISIBLE,
  FONT_IS_GLYPH_RANGE_UNUSED,
};

static inline ImFont*
js_imfont_data2(JSContext* ctx, JSValueConst value) {
  return static_cast<ImFont*>(JS_GetOpaque2(ctx, value, js_imfont_class_id));
}

static JSValue
js_imfont_wrap(JSContext* ctx, ImFont* payload) {
  JSValue obj = JS_NewObjectProtoClass(ctx, imfont_proto, js_imfont_class_id);
  JS_SetOpaque(obj, payload);
  return obj;
}

static JSValue
js_imfont_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  JSValue proto, obj = JS_UNDEFINED;
  ImFont* payload = new ImFont();
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;
  obj = JS_NewObjectProtoClass(ctx, proto, js_imfont_class_id);
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
js_imfont_finalizer(JSRuntime* rt, JSValue val) {
  ImFont* payload = static_cast<ImFont*>(JS_GetOpaque(val, js_imfont_class_id));
  if(payload) {
    delete payload;
  }
  JS_FreeValueRT(rt, val);
}

static JSValue
js_imfont_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  ImFont* payload;
  JSValue ret = JS_UNDEFINED;

  if(!(payload = js_imfont_data2(ctx, this_val)))
    return ret;

  switch(magic) {}

  return ret;
}

static JSClassDef js_imfont_class = {
    .class_name = "ImFont",
    .finalizer = js_imfont_finalizer,
};

static const JSCFunctionListEntry js_imfont_funcs[] = {
    JS_CFUNC_MAGIC_DEF("FindGlyph", 1, js_imfont_functions, FONT_FIND_GLYPH),
    JS_CFUNC_MAGIC_DEF("FindGlyphNoFallback", 1, js_imfont_functions, FONT_FIND_GLYPH_NO_FALLBACK),
    JS_CFUNC_MAGIC_DEF("CalcTextSizeA", 4, js_imfont_functions, FONT_CALC_TEXT_SIZE_A),
    JS_CFUNC_MAGIC_DEF("CalcWordWrapPositionA", 4, js_imfont_functions, FONT_CALC_WORD_WRAP_POSITION_A),
    JS_CFUNC_MAGIC_DEF("RenderChar", 5, js_imfont_functions, FONT_RENDER_CHAR),
    JS_CFUNC_MAGIC_DEF("RenderText", 7, js_imfont_functions, FONT_RENDER_TEXT),
    JS_CFUNC_MAGIC_DEF("BuildLookupTable", 0, js_imfont_functions, FONT_BUILD_LOOKUP_TABLE),
    JS_CFUNC_MAGIC_DEF("ClearOutputData", 0, js_imfont_functions, FONT_CLEAR_OUTPUT_DATA),
    JS_CFUNC_MAGIC_DEF("GrowIndex", 1, js_imfont_functions, FONT_GROW_INDEX),
    JS_CFUNC_MAGIC_DEF("AddGlyph", 11, js_imfont_functions, FONT_ADD_GLYPH),
    JS_CFUNC_MAGIC_DEF("AddRemapChar", 2, js_imfont_functions, FONT_ADD_REMAP_CHAR),
    JS_CFUNC_MAGIC_DEF("SetGlyphVisible", 2, js_imfont_functions, FONT_SET_GLYPH_VISIBLE),
    JS_CFUNC_MAGIC_DEF("IsGlyphRangeUnused", 2, js_imfont_functions, FONT_IS_GLYPH_RANGE_UNUSED),

};

#endif // defined(QUICKJS_IMFONT_HPP)
