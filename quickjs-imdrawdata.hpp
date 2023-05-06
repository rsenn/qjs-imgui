#ifndef QUICKJS_QUICKJS_IMDRAWDATA_HPP
#define QUICKJS_QUICKJS_IMDRAWDATA_HPP

#include "quickjs-imgui.hpp"

thread_local VISIBLE JSClassID js_imdrawdata_class_id = 0;
thread_local JSValue imdrawdata_proto = {JS_TAG_UNDEFINED}, imdrawdata_ctor = {JS_TAG_UNDEFINED};

template<>
ImDrawData*
js_imgui_getobj<ImDrawData>(JSContext* ctx, JSValueConst value) {
  ImDrawData* drawdata;

  if((drawdata = static_cast<ImDrawData*>(JS_GetOpaque(value, js_imdrawdata_class_id))))
    return drawdata;

  return static_cast<ImDrawData*>(js_imgui_getobj<void>(ctx, value));
}

static inline ImDrawData*
js_imdrawdata_data2(JSContext* ctx, JSValueConst value) {
  return static_cast<ImDrawData*>(JS_GetOpaque2(ctx, value, js_imdrawdata_class_id));
}

static JSValue
js_imdrawdata_wrap(JSContext* ctx, ImDrawData* drawdata) {
  JSValue obj = JS_NewObjectProtoClass(ctx, imdrawdata_proto, js_imdrawdata_class_id);
  JS_SetOpaque(obj, drawdata);
  return obj;
}

static JSValue
js_imdrawdata_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  JSValue proto, obj = JS_UNDEFINED;
  ImDrawData* drawdata = 0;

  /* using new_target to get the prototype is necessary when the class is extended. */
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;
  obj = JS_NewObjectProtoClass(ctx, proto, js_imdrawdata_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, drawdata);

  return obj;
fail:
  js_free(ctx, drawdata);
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

static void
js_imdrawdata_finalizer(JSRuntime* rt, JSValue val) {
  ImDrawData* drawdata;

  if((drawdata = static_cast<ImDrawData*>(JS_GetOpaque(val, js_imdrawdata_class_id)))) {}
}

enum {
  DRAWDATA_ID,
  DRAWDATA_VALID,
  DRAWDATA_CMD_LISTS_COUNT,
  DRAWDATA_TOTAL_IDX_COUNT,
  DRAWDATA_TOTAL_VTX_COUNT,
  DRAWDATA_DISPLAY_POS,
  DRAWDATA_DISPLAY_SIZE,
  DRAWDATA_FRAMEBUFFER_SCALE,

};

static JSValue
js_imdrawdata_get(JSContext* ctx, JSValueConst this_val, int magic) {
  ImDrawData* drawdata;
  JSValue ret = JS_UNDEFINED;

  if(!(drawdata = js_imdrawdata_data2(ctx, this_val)))
    return ret;

  switch(magic) {
    case DRAWDATA_ID: {
      ret = js_imgui_newptr(ctx, drawdata);
      break;
    }
    case DRAWDATA_VALID: {
      ret = JS_NewBool(ctx, drawdata->Valid);
      break;
    }
    case DRAWDATA_CMD_LISTS_COUNT: {
      ret = JS_NewInt32(ctx, drawdata->CmdListsCount);
      break;
    }
    case DRAWDATA_TOTAL_IDX_COUNT: {
      ret = JS_NewInt32(ctx, drawdata->TotalIdxCount);
      break;
    }
    case DRAWDATA_TOTAL_VTX_COUNT: {
      ret = JS_NewInt32(ctx, drawdata->TotalVtxCount);
      break;
    }
    case DRAWDATA_DISPLAY_POS: {
      ret = js_imgui_newimvec2(ctx, drawdata->DisplayPos);
      break;
    }
    case DRAWDATA_DISPLAY_SIZE: {
      ret = js_imgui_newimvec2(ctx, drawdata->DisplaySize);
      break;
    }
    case DRAWDATA_FRAMEBUFFER_SCALE: {
      ret = js_imgui_newimvec2(ctx, drawdata->FramebufferScale);
      break;
    }
  }

  return ret;
}

static JSValue
js_imdrawdata_set(JSContext* ctx, JSValueConst this_val, JSValueConst value, int magic) {
  ImDrawData* drawdata;
  JSValue ret = JS_UNDEFINED;

  if(!(drawdata = js_imdrawdata_data2(ctx, this_val)))
    return ret;

  switch(magic) {
    case DRAWDATA_VALID: {
      drawdata->Valid = JS_ToBool(ctx, value);
      break;
    }
  }

  return ret;
}

enum {
  DRAWDATA_CLEAR,
};

static JSValue
js_imdrawdata_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  ImDrawData* drawdata;
  JSValue ret = JS_UNDEFINED;

  if(!(drawdata = js_imdrawdata_data2(ctx, this_val)))
    return ret;

  switch(magic) {
    case DRAWDATA_CLEAR: {
      drawdata->Clear();
      break;
    }
  }

  return ret;
}

static JSClassDef js_imdrawdata_class = {
    .class_name = "ImDrawData",
    .finalizer = js_imdrawdata_finalizer,
};

static const JSCFunctionListEntry js_imdrawdata_funcs[] = {
    JS_CFUNC_MAGIC_DEF("Clear", 0, js_imdrawdata_functions, DRAWDATA_CLEAR),
    JS_CGETSET_MAGIC_DEF("id", js_imdrawdata_get, 0, DRAWDATA_ID),
    JS_CGETSET_MAGIC_DEF("Valid", js_imdrawdata_get, js_imdrawdata_set, DRAWDATA_VALID),
    JS_CGETSET_MAGIC_DEF("CmdListsCount", js_imdrawdata_get, 0, DRAWDATA_CMD_LISTS_COUNT),
    JS_CGETSET_MAGIC_DEF("TotalIdxCount", js_imdrawdata_get, 0, DRAWDATA_TOTAL_IDX_COUNT),
    JS_CGETSET_MAGIC_DEF("TotalVtxCount", js_imdrawdata_get, 0, DRAWDATA_TOTAL_VTX_COUNT),
    JS_CGETSET_MAGIC_DEF("DisplayPos", js_imdrawdata_get, 0, DRAWDATA_DISPLAY_POS),
    JS_CGETSET_MAGIC_DEF("DisplaySize", js_imdrawdata_get, 0, DRAWDATA_DISPLAY_SIZE),
    JS_CGETSET_MAGIC_DEF("FramebufferScale", js_imdrawdata_get, 0, DRAWDATA_FRAMEBUFFER_SCALE),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "ImDrawData", JS_PROP_CONFIGURABLE),

};

#endif // defined(QUICKJS_QUICKJS_IMDRAWDATA_HPP)
