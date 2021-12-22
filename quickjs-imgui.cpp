#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <imgui.h>
#include <cassert>
#include <cctype>
#include <GLFW/glfw3.h>

#include "quickjs-imgui.hpp"
#include "quickjs-imgui-constants.hpp"
#include "quickjs-imgui-payload.hpp"
#include "quickjs-imgui-io.hpp"
#include "quickjs-imfont.hpp"
#include "quickjs-imfontatlas.hpp"

#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"

static bool imgui_is_initialized;

enum {
  IMGUI_INIT,
  IMGUI_CREATE_CONTEXT,
  IMGUI_DESTROY_CONTEXT,
  IMGUI_GET_CURRENT_CONTEXT,
  IMGUI_SET_CURRENT_CONTEXT,
  IMGUI_GET_IO,
  IMGUI_GET_STYLE,
  IMGUI_NEW_FRAME,
  IMGUI_END_FRAME,
  IMGUI_RENDER,
  IMGUI_GET_DRAW_DATA,
  IMGUI_RENDER_DRAW_DATA,
  IMGUI_SHOW_DEMO_WINDOW,
  IMGUI_SHOW_ABOUT_WINDOW,
  IMGUI_SHOW_METRICS_WINDOW,
  IMGUI_SHOW_STYLE_EDITOR,
  IMGUI_SHOW_STYLE_SELECTOR,
  IMGUI_SHOW_FONT_SELECTOR,
  IMGUI_SHOW_USER_GUIDE,
  IMGUI_GET_VERSION,
  IMGUI_STYLE_COLORS_DARK,
  IMGUI_STYLE_COLORS_CLASSIC,
  IMGUI_STYLE_COLORS_LIGHT,
  IMGUI_BEGIN,
  IMGUI_END,
  IMGUI_BEGIN_CHILD,
  IMGUI_END_CHILD,
  IMGUI_IS_WINDOW_APPEARING,
  IMGUI_IS_WINDOW_COLLAPSED,
  IMGUI_IS_WINDOW_FOCUSED,
  IMGUI_IS_WINDOW_HOVERED,
  IMGUI_GET_WINDOW_DRAW_LIST,
  IMGUI_GET_WINDOW_POS,
  IMGUI_GET_WINDOW_SIZE,
  IMGUI_GET_WINDOW_WIDTH,
  IMGUI_GET_WINDOW_HEIGHT,
  IMGUI_GET_CONTENT_REGION_MAX,
  IMGUI_GET_CONTENT_REGION_AVAIL,
  IMGUI_GET_WINDOW_CONTENT_REGION_MIN,
  IMGUI_GET_WINDOW_CONTENT_REGION_MAX,
  IMGUI_SET_NEXT_WINDOW_POS,
  IMGUI_SET_NEXT_WINDOW_SIZE,
  IMGUI_SET_NEXT_WINDOW_SIZE_CONSTRAINTS,
  IMGUI_SET_NEXT_WINDOW_CONTENT_SIZE,
  IMGUI_SET_NEXT_WINDOW_COLLAPSED,
  IMGUI_SET_NEXT_WINDOW_FOCUS,
  IMGUI_SET_NEXT_WINDOW_BG_ALPHA,
  IMGUI_SET_WINDOW_POS,
  IMGUI_SET_WINDOW_SIZE,
  IMGUI_SET_WINDOW_COLLAPSED,
  IMGUI_SET_WINDOW_FOCUS,
  IMGUI_SET_WINDOW_FONT_SCALE,
  IMGUI_GET_SCROLL_X,
  IMGUI_GET_SCROLL_Y,
  IMGUI_GET_SCROLL_MAX_X,
  IMGUI_GET_SCROLL_MAX_Y,
  IMGUI_SET_SCROLL_X,
  IMGUI_SET_SCROLL_Y,
  IMGUI_SET_SCROLL_HERE_X,
  IMGUI_SET_SCROLL_HERE_Y,
  IMGUI_SET_SCROLL_FROM_POS_X,
  IMGUI_SET_SCROLL_FROM_POS_Y,
  IMGUI_PUSH_FONT,
  IMGUI_POP_FONT,
  IMGUI_PUSH_STYLE_COLOR,
  IMGUI_POP_STYLE_COLOR,
  IMGUI_PUSH_STYLE_VAR,
  IMGUI_POP_STYLE_VAR,
  IMGUI_GET_STYLE_COLOR_VEC4,
  IMGUI_GET_FONT,
  IMGUI_GET_FONT_SIZE,
  IMGUI_GET_FONT_TEX_UV_WHITE_PIXEL,
  IMGUI_GET_COLORU32,
  IMGUI_PUSH_ITEM_WIDTH,
  IMGUI_POP_ITEM_WIDTH,
  IMGUI_CALC_ITEM_WIDTH,
  IMGUI_PUSH_TEXT_WRAP_POS,
  IMGUI_POP_TEXT_WRAP_POS,
  IMGUI_PUSH_ALLOW_KEYBOARD_FOCUS,
  IMGUI_POP_ALLOW_KEYBOARD_FOCUS,
  IMGUI_PUSH_BUTTON_REPEAT,
  IMGUI_POP_BUTTON_REPEAT,
  IMGUI_SEPARATOR,
  IMGUI_SAME_LINE,
  IMGUI_NEW_LINE,
  IMGUI_SPACING,
  IMGUI_DUMMY,
  IMGUI_INDENT,
  IMGUI_UNINDENT,
  IMGUI_BEGIN_GROUP,
  IMGUI_END_GROUP,
  IMGUI_GET_CURSOR_POS,
  IMGUI_GET_CURSOR_POS_X,
  IMGUI_GET_CURSOR_POS_Y,
  IMGUI_SET_CURSOR_POS,
  IMGUI_SET_CURSOR_POS_X,
  IMGUI_SET_CURSOR_POS_Y,
  IMGUI_GET_CURSOR_START_POS,
  IMGUI_GET_CURSOR_SCREEN_POS,
  IMGUI_SET_CURSOR_SCREEN_POS,
  IMGUI_ALIGN_TEXT_TO_FRAME_PADDING,
  IMGUI_GET_TEXT_LINE_HEIGHT,
  IMGUI_GET_TEXT_LINE_HEIGHT_WITH_SPACING,
  IMGUI_GET_FRAME_HEIGHT,
  IMGUI_GET_FRAME_HEIGHT_WITH_SPACING,
  IMGUI_PUSH_ID,
  IMGUI_POP_ID,
  IMGUI_GET_ID,
  IMGUI_TEXT_UNFORMATTED,
  IMGUI_TEXT,
  IMGUI_TEXT_COLORED,
  IMGUI_TEXT_DISABLED,
  IMGUI_TEXT_WRAPPED,
  IMGUI_LABEL_TEXT,
  IMGUI_BULLET_TEXT,
  IMGUI_BUTTON,
  IMGUI_SMALL_BUTTON,
  IMGUI_INVISIBLE_BUTTON,
  IMGUI_ARROW_BUTTON,
  IMGUI_IMAGE,
  IMGUI_IMAGE_BUTTON,
  IMGUI_CHECKBOX,
  IMGUI_CHECKBOX_FLAGS,
  IMGUI_RADIO_BUTTON,
  IMGUI_PROGRESS_BAR,
  IMGUI_BULLET,
  IMGUI_BEGIN_COMBO,
  IMGUI_END_COMBO,
  IMGUI_COMBO,
  IMGUI_DRAG_FLOAT,
  IMGUI_DRAG_FLOAT2,
  IMGUI_DRAG_FLOAT3,
  IMGUI_DRAG_FLOAT4,
  IMGUI_DRAG_FLOAT_RANGE2,
  IMGUI_DRAG_INT,
  IMGUI_DRAG_INT2,
  IMGUI_DRAG_INT3,
  IMGUI_DRAG_INT4,
  IMGUI_DRAG_INT_RANGE2,
  IMGUI_DRAG_SCALAR,
  IMGUI_DRAG_SCALAR_N,
  IMGUI_SLIDER_FLOAT,
  IMGUI_SLIDER_FLOAT2,
  IMGUI_SLIDER_FLOAT3,
  IMGUI_SLIDER_FLOAT4,
  IMGUI_SLIDER_ANGLE,
  IMGUI_SLIDER_INT,
  IMGUI_SLIDER_INT2,
  IMGUI_SLIDER_INT3,
  IMGUI_SLIDER_INT4,
  IMGUI_SLIDER_SCALAR,
  IMGUI_SLIDER_SCALAR_N,
  IMGUI_V_SLIDER_FLOAT,
  IMGUI_V_SLIDER_INT,
  IMGUI_V_SLIDER_SCALAR,
  IMGUI_INPUT_TEXT,
  IMGUI_INPUT_TEXT_MULTILINE,
  IMGUI_INPUT_TEXT_WITH_HINT,
  IMGUI_INPUT_FLOAT,
  IMGUI_INPUT_FLOAT2,
  IMGUI_INPUT_FLOAT3,
  IMGUI_INPUT_FLOAT4,
  IMGUI_INPUT_INT,
  IMGUI_INPUT_INT2,
  IMGUI_INPUT_INT3,
  IMGUI_INPUT_INT4,
  IMGUI_INPUT_DOUBLE,
  IMGUI_INPUT_SCALAR,
  IMGUI_INPUT_SCALAR_N,
  IMGUI_COLOR_EDIT3,
  IMGUI_COLOR_EDIT4,
  IMGUI_COLOR_PICKER3,
  IMGUI_COLOR_PICKER4,
  IMGUI_COLOR_BUTTON,
  IMGUI_SET_COLOR_EDIT_OPTIONS,
  IMGUI_TREE_NODE,
  IMGUI_TREE_NODE_EX,
  IMGUI_TREE_PUSH,
  IMGUI_TREE_POP,
  IMGUI_GET_TREE_NODE_TO_LABEL_SPACING,
  IMGUI_COLLAPSING_HEADER,
  IMGUI_SET_NEXT_ITEM_OPEN,
  IMGUI_SELECTABLE,
  IMGUI_BEGIN_LIST_BOX,
  IMGUI_LIST_BOX,
  IMGUI_LIST_BOX_HEADER,
  IMGUI_LIST_BOX_FOOTER,
  IMGUI_END_LIST_BOX,
  IMGUI_PLOT_LINES,
  IMGUI_PLOT_HISTOGRAM,
  IMGUI_VALUE,
  IMGUI_BEGIN_MAIN_MENU_BAR,
  IMGUI_END_MAIN_MENU_BAR,
  IMGUI_BEGIN_MENU_BAR,
  IMGUI_END_MENU_BAR,
  IMGUI_BEGIN_MENU,
  IMGUI_END_MENU,
  IMGUI_MENU_ITEM,
  IMGUI_BEGIN_TOOLTIP,
  IMGUI_END_TOOLTIP,
  IMGUI_SET_TOOLTIP,
  IMGUI_OPEN_POPUP,
  IMGUI_BEGIN_POPUP,
  IMGUI_BEGIN_POPUP_CONTEXT_ITEM,
  IMGUI_BEGIN_POPUP_CONTEXT_WINDOW,
  IMGUI_BEGIN_POPUP_CONTEXT_VOID,
  IMGUI_BEGIN_POPUP_MODAL,
  IMGUI_END_POPUP,
  IMGUI_OPEN_POPUP_ON_ITEM_CLICK,
  IMGUI_IS_POPUP_OPEN,
  IMGUI_BEGIN_TABLE,
  IMGUI_END_TABLE,
  IMGUI_TABLE_NEXT_ROW,
  IMGUI_TABLE_NEXT_COLUMN,
  IMGUI_TABLE_SET_COLUMN_INDEX,
  IMGUI_TABLE_SETUP_COLUMN,
  IMGUI_TABLE_SETUP_SCROLL_FREEZE,
  IMGUI_TABLE_HEADERS_ROW,
  IMGUI_TABLE_HEADER,
  IMGUI_TABLE_GET_SORT_SPECS,
  IMGUI_TABLE_GET_COLUMN_COUNT,
  IMGUI_TABLE_GET_COLUMN_INDEX,
  IMGUI_TABLE_GET_ROW_INDEX,
  IMGUI_TABLE_GET_COLUMN_NAME,
  IMGUI_TABLE_GET_COLUMN_FLAGS,
  IMGUI_TABLE_SET_COLUMN_ENABLED,
  IMGUI_TABLE_SET_BG_COLOR,
  IMGUI_BUILD_LOOKUP_TABLE,
  IMGUI_CLOSE_CURRENT_POPUP,
  IMGUI_COLUMNS,
  IMGUI_NEXT_COLUMN,
  IMGUI_GET_COLUMN_INDEX,
  IMGUI_GET_COLUMN_WIDTH,
  IMGUI_SET_COLUMN_WIDTH,
  IMGUI_GET_COLUMN_OFFSET,
  IMGUI_SET_COLUMN_OFFSET,
  IMGUI_GET_COLUMNS_COUNT,
  IMGUI_BEGIN_TAB_BAR,
  IMGUI_END_TAB_BAR,
  IMGUI_BEGIN_TAB_ITEM,
  IMGUI_END_TAB_ITEM,
  IMGUI_TAB_ITEM_BUTTON,
  IMGUI_SET_TAB_ITEM_CLOSED,
  IMGUI_LOG_TO_TTY,
  IMGUI_LOG_TO_FILE,
  IMGUI_LOG_TO_CLIPBOARD,
  IMGUI_LOG_FINISH,
  IMGUI_LOG_BUTTONS,
  IMGUI_LOG_TEXT,
  IMGUI_BEGIN_DRAG_DROP_SOURCE,
  IMGUI_SET_DRAG_DROP_PAYLOAD,
  IMGUI_END_DRAG_DROP_SOURCE,
  IMGUI_BEGIN_DRAG_DROP_TARGET,
  IMGUI_ACCEPT_DRAG_DROP_PAYLOAD,
  IMGUI_END_DRAG_DROP_TARGET,
  IMGUI_GET_DRAG_DROP_PAYLOAD,
  IMGUI_BEGIN_DISABLED,
  IMGUI_END_DISABLED,
  IMGUI_PUSH_CLIP_RECT,
  IMGUI_POP_CLIP_RECT,
  IMGUI_SET_ITEM_DEFAULT_FOCUS,
  IMGUI_SET_KEYBOARD_FOCUS_HERE,
  IMGUI_IS_ITEM_HOVERED,
  IMGUI_IS_ITEM_ACTIVE,
  IMGUI_IS_ITEM_FOCUSED,
  IMGUI_IS_ITEM_CLICKED,
  IMGUI_IS_ITEM_VISIBLE,
  IMGUI_IS_ITEM_EDITED,
  IMGUI_IS_ITEM_ACTIVATED,
  IMGUI_IS_ITEM_DEACTIVATED,
  IMGUI_IS_ITEM_DEACTIVATED_AFTER_EDIT,
  IMGUI_IS_ANY_ITEM_HOVERED,
  IMGUI_IS_ANY_ITEM_ACTIVE,
  IMGUI_IS_ANY_ITEM_FOCUSED,
  IMGUI_GET_ITEM_RECT_MIN,
  IMGUI_GET_ITEM_RECT_MAX,
  IMGUI_GET_ITEM_RECT_SIZE,
  IMGUI_SET_ITEM_ALLOW_OVERLAP,
  IMGUI_IS_RECT_VISIBLE,
  IMGUI_GET_TIME,
  IMGUI_GET_FRAME_COUNT,
  IMGUI_GET_BACKGROUND_DRAW_LIST,
  IMGUI_GET_FOREGROUND_DRAW_LIST,
  IMGUI_GET_DRAW_LIST_SHARED_DATA,
  IMGUI_GET_STYLE_COLOR_NAME,
  IMGUI_SET_STATE_STORAGE,
  IMGUI_GET_STATE_STORAGE,
  IMGUI_CALC_TEXT_SIZE,
  IMGUI_CALC_LIST_CLIPPING,
  IMGUI_BEGIN_CHILD_FRAME,
  IMGUI_END_CHILD_FRAME,
  IMGUI_COLOR_CONVERTU32_TO_FLOAT4,
  IMGUI_COLOR_CONVERT_FLOAT4_TOU32,
  IMGUI_COLOR_CONVERT_RGB_TO_HSV,
  IMGUI_COLOR_CONVERT_HSV_TO_RGB,
  IMGUI_GET_KEY_INDEX,
  IMGUI_IS_KEY_DOWN,
  IMGUI_IS_KEY_PRESSED,
  IMGUI_IS_KEY_RELEASED,
  IMGUI_GET_KEY_PRESSED_AMOUNT,
  IMGUI_IS_MOUSE_DOWN,
  IMGUI_IS_ANY_MOUSE_DOWN,
  IMGUI_IS_MOUSE_CLICKED,
  IMGUI_IS_MOUSE_DOUBLE_CLICKED,
  IMGUI_IS_MOUSE_RELEASED,
  IMGUI_IS_MOUSE_DRAGGING,
  IMGUI_IS_MOUSE_HOVERING_RECT,
  IMGUI_IS_MOUSE_POS_VALID,
  IMGUI_GET_MOUSE_POS,
  IMGUI_GET_MOUSE_POS_ON_OPENING_CURRENT_POPUP,
  IMGUI_GET_MOUSE_DRAG_DELTA,
  IMGUI_RESET_MOUSE_DRAG_DELTA,
  IMGUI_GET_MOUSE_CURSOR,
  IMGUI_SET_MOUSE_CURSOR,
  IMGUI_CAPTURE_KEYBOARD_FROM_APP,
  IMGUI_CAPTURE_MOUSE_FROM_APP,
  IMGUI_GET_CLIPBOARD_TEXT,
  IMGUI_SET_CLIPBOARD_TEXT,
  IMGUI_LOAD_INI_SETTINGS_FROM_DISK,
  IMGUI_LOAD_INI_SETTINGS_FROM_MEMORY,
  IMGUI_SAVE_INI_SETTINGS_TO_DISK,
  IMGUI_SAVE_INI_SETTINGS_TO_MEMORY,
  IMGUI_SET_ALLOCATOR_FUNCTIONS,
  IMGUI_MEM_ALLOC,
  IMGUI_MEM_FREE,
};

static void
js_imgui_init_gl(GLFWwindow* window) {
  if(!imgui_is_initialized) {
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100"
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
#endif

        IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
  }

  imgui_is_initialized = true;
}

static void
js_imgui_free_func(JSRuntime* rt, void* opaque, void* ptr) {
  ImGui::MemFree(ptr);
}

static ImVec2
js_imgui_getimvec2(JSContext* ctx, JSValueConst value) {
  JSValue xval = JS_UNDEFINED, yval = JS_UNDEFINED;
  double x, y;
  if(JS_IsArray(ctx, value)) {
    xval = JS_GetPropertyUint32(ctx, value, 0);
    yval = JS_GetPropertyUint32(ctx, value, 1);
  } else if(JS_IsObject(value)) {
    xval = JS_GetPropertyStr(ctx, value, "x");
    yval = JS_GetPropertyStr(ctx, value, "y");
  }
  JS_ToFloat64(ctx, &x, xval);
  JS_ToFloat64(ctx, &y, yval);
  return ImVec2(x, y);
}

static ImVec4
js_imgui_getimvec4(JSContext* ctx, JSValueConst value) {
  JSValue xval = JS_UNDEFINED, yval = JS_UNDEFINED, zval = JS_UNDEFINED, wval = JS_UNDEFINED;
  double x, y, z, w;
  if(JS_IsArray(ctx, value)) {
    xval = JS_GetPropertyUint32(ctx, value, 0);
    yval = JS_GetPropertyUint32(ctx, value, 1);
    zval = JS_GetPropertyUint32(ctx, value, 2);
    wval = JS_GetPropertyUint32(ctx, value, 3);
  } else if(JS_IsObject(value)) {
    xval = JS_GetPropertyStr(ctx, value, "x");
    yval = JS_GetPropertyStr(ctx, value, "y");
    zval = JS_GetPropertyStr(ctx, value, "z");
    wval = JS_GetPropertyStr(ctx, value, "w");
  }
  JS_ToFloat64(ctx, &x, xval);
  JS_ToFloat64(ctx, &y, yval);
  JS_ToFloat64(ctx, &x, zval);
  JS_ToFloat64(ctx, &y, wval);
  return ImVec4(x, y, z, w);
}

static ImVec4
js_imgui_getcolor(JSContext* ctx, JSValueConst value) {
  ImVec4 vec = {0, 0, 0, 0};
  if(JS_IsObject(value)) {
    vec = js_imgui_getimvec4(ctx, value);
  } else if(JS_IsNumber(value)) {
    uint32_t color = 0;
    JS_ToUint32(ctx, &color, value);
    vec = ImGui::ColorConvertU32ToFloat4(color);
  } else if(JS_IsString(value)) {
    const char *p, *str = JS_ToCString(ctx, value);
    uint32_t color;
    for(p = str; *p; p++)
      if(isxdigit(*p))
        break;
    color = strtoul(p, 0, 16);
    vec = ImGui::ColorConvertU32ToFloat4(color);
    JS_FreeCString(ctx, str);
  }
  return vec;
}

static JSValue
js_imgui_newptr(JSContext* ctx, void* ptr) {
  char buf[128];
  snprintf(buf, sizeof(buf), "%p", ptr);
  return JS_NewString(ctx, buf);
}

template<class T>
static T*
js_imgui_getptr(JSContext* ctx, JSValueConst value) {
  const char* str = JS_ToCString(ctx, value);
  void* ptr = 0;
  sscanf(str, "%p", &ptr);
  JS_FreeCString(ctx, str);
  return static_cast<T*>(ptr);
}

static ImTextureID
js_imgui_gettexture(JSContext* ctx, JSValueConst value) {
  if(JS_IsNumber(value)) {
    uint64_t id;
    JS_ToIndex(ctx, &id, value);
    return ImTextureID(id);
  }

  return js_imgui_getptr<void>(ctx, value);
}

static JSValue
js_imgui_newimvec2(JSContext* ctx, const ImVec2& vec) {
  JSValue ret = JS_NewArray(ctx);
  JS_SetPropertyUint32(ctx, ret, 0, JS_NewFloat64(ctx, vec.x));
  JS_SetPropertyUint32(ctx, ret, 1, JS_NewFloat64(ctx, vec.y));
  return ret;
}

static JSValue
js_imgui_newimvec4(JSContext* ctx, const ImVec4& vec) {
  JSValue ret = JS_NewArray(ctx);
  JS_SetPropertyUint32(ctx, ret, 0, JS_NewFloat64(ctx, vec.x));
  JS_SetPropertyUint32(ctx, ret, 1, JS_NewFloat64(ctx, vec.y));
  JS_SetPropertyUint32(ctx, ret, 2, JS_NewFloat64(ctx, vec.z));
  JS_SetPropertyUint32(ctx, ret, 3, JS_NewFloat64(ctx, vec.w));
  return ret;
}

static int
js_imgui_formatcount(JSContext* ctx, int argc, JSValueConst argv[]) {
  const char *p, *end, *fmt;
  int i = 0;
  fmt = JS_ToCString(ctx, argv[i++]);
  end = fmt + strlen(fmt);
  for(p = fmt; p < end; p++) {
    if(*p == '%' && p[1] != '%') {
      ++p;
      while(isdigit(*p) || *p == '.' || *p == '-' || *p == '+' || *p == '*') ++p;
      ++i;
    }
  }
  JS_FreeCString(ctx, fmt);
  return i;
}

static void
js_imgui_formatargs(JSContext* ctx, int argc, JSValueConst argv[], void* output[]) {
  const char *p, *end, *fmt;
  int i = 0;

  fmt = JS_ToCString(ctx, argv[i]);
  end = fmt + strlen(fmt);

  output[i++] = (void*)fmt;

  for(p = fmt; p < end; p++) {
    if(*p == '%' && p[1] != '%') {
      ++p;

      while(isdigit(*p) || *p == '.' || *p == '-' || *p == '+' || *p == '*') ++p;

      switch(*p) {
        case 'd':
        case 'i': {
          int64_t i = 0;
          JS_ToInt64(ctx, &i, argv[i]);
          output[i] = (void*)(intptr_t)i;
          break;
        }
        case 'o':
        case 'x':
        case 'u': {
          uint32_t i = 0;
          JS_ToUint32(ctx, &i, argv[i]);
          output[i] = (void*)(uintptr_t)i;
          break;
        }
        case 's': {
          const char* str = JS_ToCString(ctx, argv[i]);
          output[i] = (void*)str;
          break;
        }
      }
      ++i;
    }
  }
  // JS_FreeCString(ctx, fmt);
}

#include "quickjs-imgui-style.hpp"

static JSValue
js_imgui_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  JSValue ret = JS_UNDEFINED;

  switch(magic) {
    case IMGUI_INIT: {
      GLFWwindow* window = 0;
      if(argc >= 1 && JS_IsObject(argv[0])) {
        JSValue id = JS_GetPropertyStr(ctx, argv[0], "id");

        if(JS_IsString(id)) {
          window = js_imgui_getptr<GLFWwindow>(ctx, id);
        } else {
          ImVec2 size = js_imgui_getimvec2(ctx, argv[0]);

          window = glfwCreateWindow(size.x, size.y, "ImGui", NULL, NULL);
        }
      }
      if(window)
        js_imgui_init_gl(window);
      else
        ret = JS_ThrowInternalError(ctx, "ImGui::Init expecting GLFWwindow*");
      break;
    }
    case IMGUI_CREATE_CONTEXT: {
      ImFontAtlas* atlas = 0;
      if(argc >= 1)
        atlas = js_imfontatlas_data2(ctx, argv[0]);
      ret = js_imgui_newptr(ctx, ImGui::CreateContext(atlas));
      break;
    }
    case IMGUI_DESTROY_CONTEXT: {
      ImGuiContext* context = js_imgui_getptr<ImGuiContext>(ctx, argv[0]);
      ImGui::DestroyContext(context);
      break;
    }
    case IMGUI_GET_CURRENT_CONTEXT: {
      ret = js_imgui_newptr(ctx, ImGui::GetCurrentContext());
      break;
    }
    case IMGUI_SET_CURRENT_CONTEXT: {
      ImGuiContext* context = js_imgui_getptr<ImGuiContext>(ctx, argv[0]);
      ImGui::SetCurrentContext(context);
      break;
    }
    case IMGUI_GET_IO: {
      ret = js_imgui_io_wrap(ctx, new ImGuiIO(ImGui::GetIO()));
      break;
    }
    case IMGUI_GET_STYLE: {
      ret = js_imgui_style_wrap(ctx, new ImGuiStyle(ImGui::GetStyle()));
      break;
    }
    case IMGUI_NEW_FRAME: {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();

      ImGui::NewFrame();
      break;
    }
    case IMGUI_END_FRAME: {
      ImGui::EndFrame();
      break;
    }
    case IMGUI_RENDER: {
      ImGui::Render();
      break;
    }
    case IMGUI_GET_DRAW_DATA: {
      ret = js_imgui_newptr(ctx, ImGui::GetDrawData());
      break;
    };
    case IMGUI_RENDER_DRAW_DATA: {
      ImDrawData* data = 0;
      if(argc >= 1)
        data = js_imgui_getptr<ImDrawData>(ctx, argv[0]);
      if(!data)
        data = ImGui::GetDrawData();
      ImGui_ImplOpenGL3_RenderDrawData(data);
      break;
    };
    case IMGUI_SHOW_DEMO_WINDOW: break;
    case IMGUI_SHOW_ABOUT_WINDOW: break;
    case IMGUI_SHOW_METRICS_WINDOW: break;
    case IMGUI_SHOW_STYLE_EDITOR: {
      ImGuiStyle* style = js_imgui_style_data2(ctx, argv[0]);
      ImGui::ShowStyleEditor(style);
      break;
    }
    case IMGUI_SHOW_STYLE_SELECTOR: {
      const char* label = JS_ToCString(ctx, argv[0]);
      ret = JS_NewBool(ctx, ImGui::ShowStyleSelector(label));
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_SHOW_FONT_SELECTOR: {
      const char* label = JS_ToCString(ctx, argv[0]);
      ImGui::ShowFontSelector(label);
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_SHOW_USER_GUIDE: {
      ImGui::ShowUserGuide();
      break;
    }
    case IMGUI_GET_VERSION: {
      ret = JS_NewString(ctx, ImGui::GetVersion());
      break;
    }
    case IMGUI_STYLE_COLORS_DARK: {
      ImGui::StyleColorsDark(js_imgui_style_data2(ctx, argv[0]));
      break;
    }
    case IMGUI_STYLE_COLORS_CLASSIC: {
      ImGui::StyleColorsClassic(js_imgui_style_data2(ctx, argv[0]));
      break;
    }
    case IMGUI_STYLE_COLORS_LIGHT: {
      ImGui::StyleColorsLight(js_imgui_style_data2(ctx, argv[0]));
      break;
    }
    case IMGUI_BEGIN: {
      const char* name = JS_ToCString(ctx, argv[0]);
      int32_t window_flags = 0;
      if(argc >= 3)
        JS_ToInt32(ctx, &window_flags, argv[2]);

      ret = JS_NewBool(ctx, ImGui::Begin(name, 0, window_flags));
      JS_FreeCString(ctx, name);
      break;
    }
    case IMGUI_END: {
      ImGui::End();
      break;
    }
    case IMGUI_BEGIN_CHILD: {
      const char* str_id = JS_IsString(argv[0]) ? JS_ToCString(ctx, argv[0]) : 0;
      int32_t id = -1;
      ImVec2 size(0, 0);
      bool border = false;
      int32_t flags = 0;
      if(argc >= 1)
        JS_ToInt32(ctx, &id, argv[0]);
      if(argc >= 2)
        size = js_imgui_getimvec2(ctx, argv[1]);
      if(argc >= 3)
        border = JS_ToBool(ctx, argv[2]);
      if(argc >= 4)
        JS_ToInt32(ctx, &flags, argv[3]);
      ret = JS_NewBool(ctx, str_id ? ImGui::BeginChild(str_id, size, border, flags) : ImGui::BeginChild(id, size, border, flags));
      if(str_id)
        JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_END_CHILD: {
      ImGui::EndChild();
      break;
    }
    case IMGUI_IS_WINDOW_APPEARING: {
      ret = JS_NewBool(ctx, ImGui::IsWindowAppearing());
      break;
    }
    case IMGUI_IS_WINDOW_COLLAPSED: {
      ret = JS_NewBool(ctx, ImGui::IsWindowCollapsed());
      break;
    }
    case IMGUI_IS_WINDOW_FOCUSED: {
      int32_t flags = 0;
      if(argc >= 1)
        JS_ToInt32(ctx, &flags, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsWindowFocused(flags));
      break;
    }
    case IMGUI_IS_WINDOW_HOVERED: {
      int32_t flags = 0;
      if(argc >= 1)
        JS_ToInt32(ctx, &flags, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsWindowHovered(flags));
      break;
    }
    case IMGUI_GET_WINDOW_DRAW_LIST: break;
    case IMGUI_GET_WINDOW_POS: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetWindowPos());
      break;
    }
    case IMGUI_GET_WINDOW_SIZE: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetWindowSize());
      break;
    }
    case IMGUI_GET_WINDOW_WIDTH: {
      ret = JS_NewFloat64(ctx, ImGui::GetWindowWidth());
      break;
    }
    case IMGUI_GET_WINDOW_HEIGHT: {
      ret = JS_NewFloat64(ctx, ImGui::GetWindowHeight());
      break;
    }
    case IMGUI_GET_CONTENT_REGION_MAX: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetContentRegionMax());
      break;
    }
    case IMGUI_GET_CONTENT_REGION_AVAIL: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetContentRegionAvail());
      break;
    }
    case IMGUI_GET_WINDOW_CONTENT_REGION_MIN: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetWindowContentRegionMin());
      break;
    }
    case IMGUI_GET_WINDOW_CONTENT_REGION_MAX: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetWindowContentRegionMax());
      break;
    }
    case IMGUI_SET_NEXT_WINDOW_POS: {
      ImVec2 pos = js_imgui_getimvec2(ctx, argv[0]), pivot(0, 0);
      int32_t cond = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &cond, argv[1]);
      if(argc >= 3)
        pivot = js_imgui_getimvec2(ctx, argv[2]);
      ImGui::SetNextWindowPos(pos, cond, pivot);
      break;
    }
    case IMGUI_SET_NEXT_WINDOW_SIZE: {
      ImVec2 size = js_imgui_getimvec2(ctx, argv[0]);
      int32_t cond = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &cond, argv[1]);
      ImGui::SetNextWindowSize(size, cond);
      break;
    }
    case IMGUI_SET_NEXT_WINDOW_SIZE_CONSTRAINTS: break;
    case IMGUI_SET_NEXT_WINDOW_CONTENT_SIZE: {
      ImGui::SetNextWindowContentSize(js_imgui_getimvec2(ctx, argv[0]));
      break;
    }
    case IMGUI_SET_NEXT_WINDOW_COLLAPSED: {
      bool collapsed = JS_ToBool(ctx, argv[0]);
      int32_t cond = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &cond, argv[1]);
      ImGui::SetNextWindowCollapsed(collapsed, cond);
    }
    case IMGUI_SET_NEXT_WINDOW_FOCUS: {
      ImGui::SetNextWindowFocus();
      break;
    }
    case IMGUI_SET_NEXT_WINDOW_BG_ALPHA: {
      double alpha;
      JS_ToFloat64(ctx, &alpha, argv[0]);
      ImGui::SetNextWindowBgAlpha(alpha);
      break;
    }
    case IMGUI_SET_WINDOW_POS: {
      ImVec2 pos = js_imgui_getimvec2(ctx, argv[0]);
      int32_t cond = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &cond, argv[1]);
      ImGui::SetWindowPos(pos, cond);
      break;
    }
    case IMGUI_SET_WINDOW_SIZE: {
      ImVec2 size = js_imgui_getimvec2(ctx, argv[0]);
      int32_t cond = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &cond, argv[1]);
      ImGui::SetWindowSize(size, cond);
      break;
    }
    case IMGUI_SET_WINDOW_COLLAPSED: {
      bool collapsed = JS_ToBool(ctx, argv[0]);
      int32_t cond = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &cond, argv[1]);
      ImGui::SetWindowCollapsed(collapsed, cond);
    }
    case IMGUI_SET_WINDOW_FOCUS: {
      if(argc >= 1) {
        const char* name = JS_ToCString(ctx, argv[0]);
        ImGui::SetWindowFocus(name);
        JS_FreeCString(ctx, name);
      } else {
        ImGui::SetWindowFocus();
      }
      break;
    }
    case IMGUI_SET_WINDOW_FONT_SCALE: {
      double scale;
      JS_ToFloat64(ctx, &scale, argv[0]);
      ImGui::SetWindowFontScale(scale);
      break;
    }
    case IMGUI_GET_SCROLL_X: {
      ret = JS_NewFloat64(ctx, ImGui::GetScrollX());
      break;
    }
    case IMGUI_GET_SCROLL_Y: {
      ret = JS_NewFloat64(ctx, ImGui::GetScrollY());
      break;
    }
    case IMGUI_GET_SCROLL_MAX_X: {
      ret = JS_NewFloat64(ctx, ImGui::GetScrollMaxX());
      break;
    }
    case IMGUI_GET_SCROLL_MAX_Y: {
      ret = JS_NewFloat64(ctx, ImGui::GetScrollMaxY());
      break;
    }
    case IMGUI_SET_SCROLL_X: {
      double x;
      JS_ToFloat64(ctx, &x, argv[0]);
      ImGui::SetScrollX(x);
    }
    case IMGUI_SET_SCROLL_Y: {
      double y;
      JS_ToFloat64(ctx, &y, argv[0]);
      ImGui::SetScrollX(y);
    }
    case IMGUI_SET_SCROLL_HERE_X: {
      double center_x_ratio = 0.5;
      if(argc >= 1)
        JS_ToFloat64(ctx, &center_x_ratio, argv[0]);
      ImGui::SetScrollHereX(center_x_ratio);
    }
    case IMGUI_SET_SCROLL_HERE_Y: {
      double center_y_ratio = 0.5;
      if(argc >= 1)
        JS_ToFloat64(ctx, &center_y_ratio, argv[0]);
      ImGui::SetScrollHereX(center_y_ratio);
    }
    case IMGUI_SET_SCROLL_FROM_POS_X: {
      double local_x, center_x_ratio = 0.5;
      JS_ToFloat64(ctx, &local_x, argv[0]);
      if(argc >= 2)
        JS_ToFloat64(ctx, &center_x_ratio, argv[1]);
      ImGui::SetScrollFromPosX(local_x, center_x_ratio);
    }
    case IMGUI_SET_SCROLL_FROM_POS_Y: {
      double local_y, center_y_ratio = 0.5;
      JS_ToFloat64(ctx, &local_y, argv[0]);
      if(argc >= 2)
        JS_ToFloat64(ctx, &center_y_ratio, argv[1]);
      ImGui::SetScrollFromPosX(local_y, center_y_ratio);
    }
    case IMGUI_PUSH_FONT: {
      ImFont* font = js_imfont_data2(ctx, argv[0]);
      ImGui::PushFont(font);
      break;
    }
    case IMGUI_POP_FONT: {
      ImGui::PopFont();
      break;
    }
    case IMGUI_PUSH_STYLE_COLOR: {
      int32_t idx;
      JS_ToInt32(ctx, &idx, argv[0]);
      if(JS_IsNumber(argv[1])) {
        uint32_t col;
        JS_ToUint32(ctx, &col, argv[1]);
        ImGui::PushStyleColor(idx, col);
      } else {
        ImVec4 vec = js_imgui_getimvec4(ctx, argv[1]);
        ImGui::PushStyleColor(idx, vec);
      }
      break;
    }
    case IMGUI_POP_STYLE_COLOR: {
      uint32_t count = 1;
      if(argc >= 1)
        JS_ToUint32(ctx, &count, argv[0]);
      ImGui::PopStyleColor(count);
      break;
    }
    case IMGUI_PUSH_STYLE_VAR: {
      int32_t idx;
      JS_ToInt32(ctx, &idx, argv[0]);
      if(JS_IsNumber(argv[1])) {
        double val;
        JS_ToFloat64(ctx, &val, argv[1]);
        ImGui::PushStyleVar(idx, val);
      } else {
        ImVec2 vec = js_imgui_getimvec2(ctx, argv[1]);
        ImGui::PushStyleVar(idx, vec);
      }
      break;
    }
    case IMGUI_POP_STYLE_VAR: {
      uint32_t count = 1;
      if(argc >= 1)
        JS_ToUint32(ctx, &count, argv[0]);
      ImGui::PopStyleVar(count);
      break;
    }
    case IMGUI_GET_STYLE_COLOR_VEC4: {
      uint32_t col;
      JS_ToUint32(ctx, &col, argv[0]);
      ret = js_imgui_newimvec4(ctx, ImGui::GetStyleColorVec4(col));
      break;
    }
    case IMGUI_GET_FONT: {
      ret = js_imfont_wrap(ctx, ImGui::GetFont());
      break;
    }
    case IMGUI_GET_FONT_SIZE: {
      ret = JS_NewFloat64(ctx, ImGui::GetFontSize());
      break;
    }
    case IMGUI_GET_FONT_TEX_UV_WHITE_PIXEL: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetFontTexUvWhitePixel());
      break;
    }
    case IMGUI_GET_COLORU32: {
      if(JS_IsArray(ctx, argv[0])) {
        ImVec4 color = js_imgui_getimvec4(ctx, argv[0]);
        ret = JS_NewUint32(ctx, ImGui::GetColorU32(color));
      } else if(argc >= 2) {
        int32_t idx;
        double alpha_mul = 1.0f;
        JS_ToInt32(ctx, &idx, argv[0]);
        JS_ToFloat64(ctx, &alpha_mul, argv[1]);
        ret = JS_NewUint32(ctx, ImGui::GetColorU32(idx, alpha_mul));
      } else {
        uint32_t col;
        JS_ToUint32(ctx, &col, argv[0]);
        ret = JS_NewUint32(ctx, ImGui::GetColorU32(col));
      }
      break;
    }
    case IMGUI_PUSH_ITEM_WIDTH: {
      int32_t width;
      JS_ToInt32(ctx, &width, argv[0]);
      ImGui::PushItemWidth(width);
      break;
    }
    case IMGUI_POP_ITEM_WIDTH: {
      ImGui::PopItemWidth();
      break;
    }
    case IMGUI_CALC_ITEM_WIDTH: {
      ret = JS_NewFloat64(ctx, ImGui::CalcItemWidth());
      break;
    }
    case IMGUI_PUSH_TEXT_WRAP_POS: {
      double wrap_local_pos_x = 0;
      JS_ToFloat64(ctx, &wrap_local_pos_x, argv[0]);
      ImGui::PushTextWrapPos(wrap_local_pos_x);
      break;
    }
    case IMGUI_POP_TEXT_WRAP_POS: {
      ImGui::PopTextWrapPos();
      break;
    }
    case IMGUI_PUSH_ALLOW_KEYBOARD_FOCUS: {
      ImGui::PushAllowKeyboardFocus(JS_ToBool(ctx, argv[0]));
      break;
    }
    case IMGUI_POP_ALLOW_KEYBOARD_FOCUS: {
      ImGui::PopAllowKeyboardFocus();
      break;
    }
    case IMGUI_PUSH_BUTTON_REPEAT: {
      ImGui::PushButtonRepeat(JS_ToBool(ctx, argv[0]));
      break;
    }
    case IMGUI_POP_BUTTON_REPEAT: {
      ImGui::PopButtonRepeat();
      break;
    }
    case IMGUI_SEPARATOR: {
      ImGui::Separator();
      break;
    }
    case IMGUI_SAME_LINE: {
      double offset_from_start_x = 0, spacing = -1.0;
      JS_ToFloat64(ctx, &offset_from_start_x, argv[0]);
      if(argc >= 2)
        JS_ToFloat64(ctx, &spacing, argv[1]);
      ImGui::SameLine(offset_from_start_x, spacing);
      break;
    }
    case IMGUI_NEW_LINE: {
      ImGui::NewLine();
      break;
    }
    case IMGUI_SPACING: {
      ImGui::Spacing();
      break;
    }
    case IMGUI_DUMMY: {
      ImGui::Dummy(js_imgui_getimvec2(ctx, argv[0]));
      break;
    }
    case IMGUI_INDENT: {
      double indent_w = 0;
      JS_ToFloat64(ctx, &indent_w, argv[0]);
      ImGui::Indent(indent_w);
      break;
    }
    case IMGUI_UNINDENT: {
      double indent_w = 0;
      JS_ToFloat64(ctx, &indent_w, argv[0]);
      ImGui::Unindent(indent_w);
      break;
    }
    case IMGUI_BEGIN_GROUP: {
      ImGui::BeginGroup();
      break;
    }
    case IMGUI_END_GROUP: {
      ImGui::EndGroup();
      break;
    }
    case IMGUI_GET_CURSOR_POS: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetCursorPos());
      break;
    }
    case IMGUI_GET_CURSOR_POS_X: {
      ret = JS_NewFloat64(ctx, ImGui::GetCursorPosX());
      break;
    }
    case IMGUI_GET_CURSOR_POS_Y: {
      ret = JS_NewFloat64(ctx, ImGui::GetCursorPosY());
      break;
    }
    case IMGUI_SET_CURSOR_POS: {
      ImGui::SetCursorPos(js_imgui_getimvec2(ctx, argv[0]));
      break;
    }
    case IMGUI_SET_CURSOR_POS_X: {
      double x;
      JS_ToFloat64(ctx, &x, argv[0]);
      ImGui::SetCursorPosX(x);
      break;
    }
    case IMGUI_SET_CURSOR_POS_Y: {
      double y;
      JS_ToFloat64(ctx, &y, argv[0]);
      ImGui::SetCursorPosY(y);
      break;
    }
    case IMGUI_GET_CURSOR_START_POS: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetCursorStartPos());
      break;
    }
    case IMGUI_GET_CURSOR_SCREEN_POS: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetCursorScreenPos());
      break;
    }
    case IMGUI_SET_CURSOR_SCREEN_POS: {
      ImGui::SetCursorScreenPos(js_imgui_getimvec2(ctx, argv[0]));
      break;
    }
    case IMGUI_ALIGN_TEXT_TO_FRAME_PADDING: {
      ImGui::AlignTextToFramePadding();
      break;
    }
    case IMGUI_GET_TEXT_LINE_HEIGHT: {
      ret = JS_NewFloat64(ctx, ImGui::GetTextLineHeight());
      break;
    }
    case IMGUI_GET_TEXT_LINE_HEIGHT_WITH_SPACING: {
      ret = JS_NewFloat64(ctx, ImGui::GetTextLineHeightWithSpacing());
      break;
    }
    case IMGUI_GET_FRAME_HEIGHT: {
      ret = JS_NewFloat64(ctx, ImGui::GetFrameHeight());
      break;
    }
    case IMGUI_GET_FRAME_HEIGHT_WITH_SPACING: {
      ret = JS_NewFloat64(ctx, ImGui::GetFrameHeightWithSpacing());
      break;
    }
    case IMGUI_PUSH_ID: {
      if(argc >= 2) {
        const char *id_begin = JS_ToCString(ctx, argv[0]), *id_end = JS_ToCString(ctx, argv[1]);
        ImGui::PushID(id_begin, id_end);
        JS_FreeCString(ctx, id_begin);
        JS_FreeCString(ctx, id_end);
      } else if(JS_IsString(argv[0])) {
        const char* id = JS_ToCString(ctx, argv[0]);
        ImGui::PushID(id);
        JS_FreeCString(ctx, id);
      } else if(JS_IsNumber(argv[0])) {
        int32_t id;
        JS_ToInt32(ctx, &id, argv[0]);
        ImGui::PushID(id);
      } else {
        ret = JS_ThrowInternalError(ctx, "ImGui::PushID() invalid argument");
      }
      break;
    }
    case IMGUI_POP_ID: {
      ImGui::PopID();
      break;
    }
    case IMGUI_GET_ID: {
      ImGuiID id = -1;
      if(argc >= 2) {
        const char *id_begin = JS_ToCString(ctx, argv[0]), *id_end = JS_ToCString(ctx, argv[1]);
        id = ImGui::GetID(id_begin, id_end);
        JS_FreeCString(ctx, id_begin);
        JS_FreeCString(ctx, id_end);
      } else if(JS_IsString(argv[0])) {
        const char* id_str = JS_ToCString(ctx, argv[0]);
        id = ImGui::GetID(id_str);
        JS_FreeCString(ctx, id_str);
      } else {
        ret = JS_ThrowInternalError(ctx, "ImGui::GetID() invalid argument");
        break;
      }
      ret = JS_NewInt32(ctx, id);
      break;
    }
    case IMGUI_TEXT_UNFORMATTED: {
      const char *text = JS_ToCString(ctx, argv[0]), *text_end = 0;
      if(argc >= 2)
        text_end = JS_ToCString(ctx, argv[1]);
      ImGui::TextUnformatted(text, text_end);
      JS_FreeCString(ctx, text);
      if(text_end)
        JS_FreeCString(ctx, text_end);
      break;
    }
    case IMGUI_TEXT: {
      int count = js_imgui_formatcount(ctx, argc, argv);
      assert(count <= 32);
      void* a[count];
      js_imgui_formatargs(ctx, argc, argv, a);
      ImGui::Text((const char*)a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
      break;
    }
    case IMGUI_TEXT_COLORED: {
      ImVec4 color = js_imgui_getcolor(ctx, argv[0]);
      int count = js_imgui_formatcount(ctx, argc - 1, argv + 1);
      assert(count <= 32);
      void* a[count];
      js_imgui_formatargs(ctx, argc - 1, argv + 1, a);
      ImGui::TextColored(color, (const char*)a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
      break;
    }
    case IMGUI_TEXT_DISABLED: {
      int count = js_imgui_formatcount(ctx, argc, argv);
      assert(count <= 32);
      void* a[count];
      js_imgui_formatargs(ctx, argc, argv, a);
      ImGui::TextDisabled((const char*)a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
      break;
    }
    case IMGUI_TEXT_WRAPPED: {
      int count = js_imgui_formatcount(ctx, argc, argv);
      assert(count <= 32);
      void* a[count];
      js_imgui_formatargs(ctx, argc, argv, a);
      ImGui::TextWrapped((const char*)a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
      break;
    }
    case IMGUI_LABEL_TEXT: {
      const char* label = JS_ToCString(ctx, argv[0]);
      int count = js_imgui_formatcount(ctx, argc - 1, argv + 1);
      assert(count <= 32);
      void* a[count];
      js_imgui_formatargs(ctx, argc - 1, argv + 1, a);
      ImGui::LabelText(label, (const char*)a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_BULLET_TEXT: {
      int count = js_imgui_formatcount(ctx, argc, argv);
      assert(count <= 32);
      void* a[count];
      js_imgui_formatargs(ctx, argc, argv, a);
      ImGui::BulletText((const char*)a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
      break;
    }
    case IMGUI_BUTTON: {
      const char* label = JS_ToCString(ctx, argv[0]);
      ImVec2 size(0, 0);
      if(argc >= 2)
        size = js_imgui_getimvec2(ctx, argv[1]);
      ret = JS_NewBool(ctx, ImGui::Button(label, size));
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_SMALL_BUTTON: {
      const char* label = JS_ToCString(ctx, argv[0]);
      ret = JS_NewBool(ctx, ImGui::SmallButton(label));
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_INVISIBLE_BUTTON: {
      const char* str_id = JS_ToCString(ctx, argv[0]);
      ImVec2 size(0, 0);
      int32_t flags = 0;
      if(argc >= 2)
        size = js_imgui_getimvec2(ctx, argv[1]);
      if(argc >= 3)
        JS_ToInt32(ctx, &flags, argv[2]);
      ret = JS_NewBool(ctx, ImGui::InvisibleButton(str_id, size, flags));
      JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_ARROW_BUTTON: {
      const char* str_id = JS_ToCString(ctx, argv[0]);
      int32_t dir = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &dir, argv[1]);
      ret = JS_NewBool(ctx, ImGui::ArrowButton(str_id, dir));
      JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_IMAGE: {
      ImTextureID tex = js_imgui_gettexture(ctx, argv[0]);
      ImVec2 size = js_imgui_getimvec2(ctx, argv[1]);
      ImVec2 uv0(0, 0), uv1(1, 1);
      ImVec4 tint_col(1, 1, 1, 1), border_col(0, 0, 0, 0);
      if(argc >= 3)
        uv0 = js_imgui_getimvec2(ctx, argv[2]);
      if(argc >= 4)
        uv1 = js_imgui_getimvec2(ctx, argv[3]);
      if(argc >= 5)
        tint_col = js_imgui_getimvec4(ctx, argv[4]);
      if(argc >= 6)
        border_col = js_imgui_getimvec4(ctx, argv[5]);
      ImGui::Image(tex, size, uv0, uv1, tint_col, border_col);
      break;
    }
    case IMGUI_IMAGE_BUTTON: {
      ImTextureID tex = js_imgui_gettexture(ctx, argv[0]);
      ImVec2 size = js_imgui_getimvec2(ctx, argv[1]);
      ImVec2 uv0(0, 0), uv1(1, 1);
      int32_t frame_padding = -1;
      ImVec4 tint_col(1, 1, 1, 1), border_col(0, 0, 0, 0);
      if(argc >= 3)
        uv0 = js_imgui_getimvec2(ctx, argv[2]);
      if(argc >= 4)
        uv1 = js_imgui_getimvec2(ctx, argv[3]);
      if(argc >= 5)
        JS_ToInt32(ctx, &frame_padding, argv[4]);
      if(argc >= 6)
        tint_col = js_imgui_getimvec4(ctx, argv[5]);
      if(argc >= 7)
        border_col = js_imgui_getimvec4(ctx, argv[6]);
      ret = JS_NewBool(ctx, ImGui::ImageButton(tex, size, uv0, uv1, frame_padding, tint_col, border_col));
      break;
    }
    case IMGUI_CHECKBOX: break;
    case IMGUI_CHECKBOX_FLAGS: break;
    case IMGUI_RADIO_BUTTON: {
      const char* label = JS_ToCString(ctx, argv[0]);
      bool active = JS_ToBool(ctx, argv[1]);
      ret = JS_NewBool(ctx, ImGui::RadioButton(label, active));
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_PROGRESS_BAR: {
      double fraction;
      ImVec2 size_arg(-FLT_MIN, 0);
      const char* overlay = 0;
      JS_ToFloat64(ctx, &fraction, argv[0]);
      if(argc >= 2)
        size_arg = js_imgui_getimvec2(ctx, argv[1]);
      if(argc >= 3)
        overlay = JS_ToCString(ctx, argv[2]);
      ImGui::ProgressBar(fraction, size_arg, overlay);
      if(overlay)
        JS_FreeCString(ctx, overlay);
      break;
    }
    case IMGUI_BULLET: {
      ImGui::Bullet();
      break;
    }
    case IMGUI_BEGIN_COMBO: {
      const char *label = JS_ToCString(ctx, argv[0]), *preview_value = JS_ToCString(ctx, argv[1]);
      int32_t flags = 0;
      if(argc >= 3)
        JS_ToInt32(ctx, &flags, argv[2]);
      ImGui::BeginCombo(label, preview_value, flags);
      JS_FreeCString(ctx, label);
      JS_FreeCString(ctx, preview_value);
      break;
    }
    case IMGUI_END_COMBO: {
      ImGui::EndCombo();
      break;
    }
    case IMGUI_COMBO: break;
    case IMGUI_DRAG_FLOAT: break;
    case IMGUI_DRAG_FLOAT2: break;
    case IMGUI_DRAG_FLOAT3: break;
    case IMGUI_DRAG_FLOAT4: break;
    case IMGUI_DRAG_FLOAT_RANGE2: break;
    case IMGUI_DRAG_INT: break;
    case IMGUI_DRAG_INT2: break;
    case IMGUI_DRAG_INT3: break;
    case IMGUI_DRAG_INT4: break;
    case IMGUI_DRAG_INT_RANGE2: break;
    case IMGUI_DRAG_SCALAR: break;
    case IMGUI_DRAG_SCALAR_N: break;
    case IMGUI_SLIDER_FLOAT: break;
    case IMGUI_SLIDER_FLOAT2: break;
    case IMGUI_SLIDER_FLOAT3: break;
    case IMGUI_SLIDER_FLOAT4: break;
    case IMGUI_SLIDER_ANGLE: break;
    case IMGUI_SLIDER_INT: break;
    case IMGUI_SLIDER_INT2: break;
    case IMGUI_SLIDER_INT3: break;
    case IMGUI_SLIDER_INT4: break;
    case IMGUI_SLIDER_SCALAR: break;
    case IMGUI_SLIDER_SCALAR_N: break;
    case IMGUI_V_SLIDER_FLOAT: break;
    case IMGUI_V_SLIDER_INT: break;
    case IMGUI_V_SLIDER_SCALAR: break;
    case IMGUI_INPUT_TEXT: break;
    case IMGUI_INPUT_TEXT_MULTILINE: break;
    case IMGUI_INPUT_TEXT_WITH_HINT: break;
    case IMGUI_INPUT_FLOAT: break;
    case IMGUI_INPUT_FLOAT2: break;
    case IMGUI_INPUT_FLOAT3: break;
    case IMGUI_INPUT_FLOAT4: break;
    case IMGUI_INPUT_INT: break;
    case IMGUI_INPUT_INT2: break;
    case IMGUI_INPUT_INT3: break;
    case IMGUI_INPUT_INT4: break;
    case IMGUI_INPUT_DOUBLE: break;
    case IMGUI_INPUT_SCALAR: break;
    case IMGUI_INPUT_SCALAR_N: break;
    case IMGUI_COLOR_EDIT3: break;
    case IMGUI_COLOR_EDIT4: break;
    case IMGUI_COLOR_PICKER3: break;
    case IMGUI_COLOR_PICKER4: break;
    case IMGUI_COLOR_BUTTON: break;
    case IMGUI_SET_COLOR_EDIT_OPTIONS: {
      int32_t options;
      JS_ToInt32(ctx, &options, argv[0]);
      ImGui::SetColorEditOptions(options);
      break;
    }
    case IMGUI_TREE_NODE: {
      if(argc > 1 /* && JS_IsString(argv[0])*/) {
        const char* str_id = JS_ToCString(ctx, argv[0]);
        int count = js_imgui_formatcount(ctx, argc - 1, argv + 1);
        assert(count <= 32);
        void* a[count];
        js_imgui_formatargs(ctx, argc - 1, argv + 1, a);
        ret = JS_NewBool(ctx, ImGui::TreeNode(str_id, (const char*)a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]));
        JS_FreeCString(ctx, str_id);
      } else {
        const char* label = JS_ToCString(ctx, argv[0]);
        ret = JS_NewBool(ctx, ImGui::TreeNode(label));
        JS_FreeCString(ctx, label);
      }
      break;
    }
    case IMGUI_TREE_NODE_EX: {
      int32_t flags = 0;
      JS_ToInt32(ctx, &flags, argv[1]);

      if(argc > 1 /* && JS_IsString(argv[0])*/) {
        const char* str_id = JS_ToCString(ctx, argv[0]);
        int count = js_imgui_formatcount(ctx, argc - 2, argv + 2);
        assert(count <= 32);
        void* a[count];
        js_imgui_formatargs(ctx, argc - 2, argv + 2, a);
        ret = JS_NewBool(ctx, ImGui::TreeNodeEx(str_id, flags, (const char*)a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]));
        JS_FreeCString(ctx, str_id);
      } else {
        const char* label = JS_ToCString(ctx, argv[0]);
        ret = JS_NewBool(ctx, ImGui::TreeNodeEx(label, flags));
        JS_FreeCString(ctx, label);
      }
      break;
    }
    case IMGUI_TREE_PUSH: {
      const char* label = JS_ToCString(ctx, argv[0]);
      ImGui::TreePush(label);
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_TREE_POP: {
      ImGui::TreePop();
      break;
    }
    case IMGUI_GET_TREE_NODE_TO_LABEL_SPACING: {
      ret = JS_NewFloat64(ctx, ImGui::GetTreeNodeToLabelSpacing());
      break;
    }
    case IMGUI_COLLAPSING_HEADER: {
      const char* label = JS_ToCString(ctx, argv[0]);
      int32_t flags = 0;
      JS_ToInt32(ctx, &flags, argv[1]);
      ImGui::CollapsingHeader(label, flags);
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_SET_NEXT_ITEM_OPEN: {
      bool is_open = JS_ToBool(ctx, argv[0]);
      int32_t flags = 0;
      JS_ToInt32(ctx, &flags, argv[1]);
      ImGui::SetNextItemOpen(is_open, flags);
      break;
    }
    case IMGUI_SELECTABLE: {
      const char* label = JS_ToCString(ctx, argv[0]);
      bool selected = false;
      int32_t flags = 0;
      ImVec2 size(0, 0);
      if(argc >= 2)
        selected = JS_ToBool(ctx, argv[1]);
      if(argc >= 3)
        JS_ToInt32(ctx, &flags, argv[2]);
      if(argc >= 4)
        size = js_imgui_getimvec2(ctx, argv[3]);
      ImGui::Selectable(label, selected, flags, size);
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_BEGIN_LIST_BOX: {
      const char* label = JS_ToCString(ctx, argv[0]);
      ImVec2 size(0, 0);
      if(argc >= 2)
        size = js_imgui_getimvec2(ctx, argv[1]);
      ImGui::BeginListBox(label, size);
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_END_LIST_BOX: {
      ImGui::EndListBox();
      break;
    }
    case IMGUI_LIST_BOX: break;
    case IMGUI_LIST_BOX_HEADER: break;
    case IMGUI_LIST_BOX_FOOTER: break;

    case IMGUI_PLOT_LINES: break;
    case IMGUI_PLOT_HISTOGRAM: break;
    case IMGUI_VALUE: {
      const char* prefix = JS_ToCString(ctx, argv[0]);
      if(JS_IsBool(argv[1])) {
        ImGui::Value(prefix, static_cast<bool>(JS_ToBool(ctx, argv[1])));
      } else if(JS_IsNumber(argv[1])) {
        if(JS_VALUE_GET_TAG(argv[1]) == JS_TAG_FLOAT64) {
          double f;
          JS_ToFloat64(ctx, &f, argv[1]);
          ImGui::Value(prefix, static_cast<float>(f));
        } else {
          int64_t i64;
          JS_ToInt64(ctx, &i64, argv[1]);
          if(i64 >= 0)
            ImGui::Value(prefix, static_cast<unsigned int>(i64));
          else
            ImGui::Value(prefix, static_cast<int>(i64));
        }
      }
      JS_FreeCString(ctx, prefix);
      break;
    }
    case IMGUI_BEGIN_MAIN_MENU_BAR: {
      ret = JS_NewBool(ctx, ImGui::BeginMainMenuBar());
      break;
    }
    case IMGUI_END_MAIN_MENU_BAR: {
      ImGui::EndMainMenuBar();
      break;
    }
    case IMGUI_BEGIN_MENU_BAR: {
      ret = JS_NewBool(ctx, ImGui::BeginMenuBar());
      break;
    }
    case IMGUI_END_MENU_BAR: {
      ImGui::EndMenuBar();
      break;
    }
    case IMGUI_BEGIN_MENU: {
      const char* label = JS_ToCString(ctx, argv[0]);
      bool enabled = true;
      if(argc >= 2)
        enabled = JS_ToBool(ctx, argv[1]);
      ImGui::BeginMenu(label, enabled);
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_END_MENU: {
      ImGui::EndMenu();
      break;
    }
    case IMGUI_MENU_ITEM: {
      const char *label = JS_ToCString(ctx, argv[0]), *shortcut = 0;
      bool selected = false, enabled = true;
      if(argc >= 2)
        shortcut = JS_ToCString(ctx, argv[1]);
      if(argc >= 3)
        selected = JS_ToBool(ctx, argv[2]);
      if(argc >= 4)
        enabled = JS_ToBool(ctx, argv[3]);
      ret = JS_NewBool(ctx, ImGui::MenuItem(label, shortcut, selected, enabled));
      JS_FreeCString(ctx, label);
      if(shortcut)
        JS_FreeCString(ctx, shortcut);
      break;
    }
    case IMGUI_BEGIN_TOOLTIP: {
      ImGui::BeginTooltip();
      break;
    }
    case IMGUI_END_TOOLTIP: {
      ImGui::EndTooltip();
      break;
    }
    case IMGUI_SET_TOOLTIP: {
      int count = js_imgui_formatcount(ctx, argc, argv);
      assert(count <= 32);
      void* a[count];
      js_imgui_formatargs(ctx, argc, argv, a);
      ImGui::SetTooltip((const char*)a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
      break;
    }
    case IMGUI_OPEN_POPUP: {
      if(JS_IsString(argv[0])) {
        const char* str_id = JS_ToCString(ctx, argv[0]);
        int32_t flags = 0;
        if(argc >= 2)
          JS_ToInt32(ctx, &flags, argv[1]);
        ImGui::OpenPopup(str_id, flags);
        JS_FreeCString(ctx, str_id);
      } else {
        int32_t id;
        JS_ToInt32(ctx, &id, argv[0]);
        int32_t flags = 0;
        if(argc >= 2)
          JS_ToInt32(ctx, &flags, argv[1]);
        ImGui::OpenPopup(id, flags);
      }
      break;
    }
    case IMGUI_BEGIN_POPUP: {
      const char* str_id = JS_ToCString(ctx, argv[0]);
      int32_t flags = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &flags, argv[1]);
      ret = JS_NewBool(ctx, ImGui::BeginPopup(str_id, flags));
      JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_BEGIN_POPUP_CONTEXT_ITEM: {
      const char* str_id = 0;
      int32_t flags = 1;
      if(argc >= 1)
        str_id = JS_ToCString(ctx, argv[0]);
      if(argc >= 2)
        JS_ToInt32(ctx, &flags, argv[1]);
      ImGui::BeginPopupContextItem(str_id, flags);
      if(str_id)
        JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_BEGIN_POPUP_CONTEXT_WINDOW: {
      const char* str_id = 0;
      int32_t flags = 1;
      if(argc >= 1)
        str_id = JS_ToCString(ctx, argv[0]);
      if(argc >= 2)
        JS_ToInt32(ctx, &flags, argv[1]);
      ImGui::BeginPopupContextWindow(str_id, flags);
      if(str_id)
        JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_BEGIN_POPUP_CONTEXT_VOID: {
      const char* str_id = 0;
      int32_t flags = 1;
      if(argc >= 1)
        str_id = JS_ToCString(ctx, argv[0]);
      if(argc >= 2)
        JS_ToInt32(ctx, &flags, argv[1]);
      ImGui::BeginPopupContextVoid(str_id, flags);
      if(str_id)
        JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_BEGIN_POPUP_MODAL: break;
    case IMGUI_END_POPUP: {
      ImGui::EndPopup();
      break;
    }
    case IMGUI_OPEN_POPUP_ON_ITEM_CLICK: {
      const char* str_id = 0;
      int32_t flags = 1;
      if(argc >= 1)
        str_id = JS_ToCString(ctx, argv[0]);
      if(argc >= 2)
        JS_ToInt32(ctx, &flags, argv[1]);
      ImGui::OpenPopupOnItemClick(str_id, flags);
      if(str_id)
        JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_IS_POPUP_OPEN: {
      const char* str_id = JS_ToCString(ctx, argv[0]);
      int32_t flags = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &flags, argv[1]);
      ImGui::IsPopupOpen(str_id, flags);
      JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_BEGIN_TABLE: {
      const char* str_id = JS_ToCString(ctx, argv[0]);
      int32_t column, flags = 0;
      ImVec2 outer_size(0, 0);
      double inner_width = 0.0f;
      JS_ToInt32(ctx, &column, argv[1]);
      if(argc >= 3)
        JS_ToInt32(ctx, &flags, argv[2]);
      if(argc >= 4)
        outer_size = js_imgui_getimvec2(ctx, argv[3]);
      if(argc >= 5)
        JS_ToFloat64(ctx, &inner_width, argv[4]);
      ret = JS_NewBool(ctx, ImGui::BeginTable(str_id, column, flags, outer_size, inner_width));
      JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_END_TABLE: {
      ImGui::EndTable();
      break;
    }
    case IMGUI_TABLE_NEXT_ROW: {
      int32_t row_flags = 0;
      double min_row_height = 0.0f;

      if(argc >= 1)
        JS_ToInt32(ctx, &row_flags, argv[0]);
      if(argc >= 2)
        JS_ToFloat64(ctx, &min_row_height, argv[1]);
      ImGui::TableNextRow(row_flags, min_row_height);
      break;
    }
    case IMGUI_TABLE_NEXT_COLUMN: {
      ret = JS_NewBool(ctx, ImGui::TableNextColumn());
      break;
    }
    case IMGUI_TABLE_SET_COLUMN_INDEX: {
      int32_t column_index;
      JS_ToInt32(ctx, &column_index, argv[0]);
      ret = JS_NewBool(ctx, ImGui::TableSetColumnIndex(column_index));
      break;
    }
    case IMGUI_TABLE_SETUP_COLUMN: {
      const char* label = JS_ToCString(ctx, argv[0]);
      int32_t flags = 0, user_id = 0;
      double init_width_or_weight = 0.0f;
      if(argc >= 2)
        JS_ToInt32(ctx, &flags, argv[1]);
      if(argc >= 3)
        JS_ToFloat64(ctx, &init_width_or_weight, argv[2]);
      if(argc >= 4)
        JS_ToInt32(ctx, &user_id, argv[3]);
      ImGui::TableSetupColumn(label, flags, init_width_or_weight, user_id);
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_TABLE_SETUP_SCROLL_FREEZE: {
      int32_t cols, rows;
      JS_ToInt32(ctx, &cols, argv[0]);
      JS_ToInt32(ctx, &rows, argv[1]);
      ImGui::TableSetupScrollFreeze(cols, rows);
      break;
    }
    case IMGUI_TABLE_HEADERS_ROW: {
      ImGui::TableHeadersRow();
      break;
    }
    case IMGUI_TABLE_HEADER: {
      const char* label = JS_ToCString(ctx, argv[0]);

      ImGui::TableHeader(label);
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_TABLE_GET_SORT_SPECS: break;
    case IMGUI_TABLE_GET_COLUMN_COUNT: {
      ret = JS_NewUint32(ctx, ImGui::TableGetColumnCount());
      break;
    }
    case IMGUI_TABLE_GET_COLUMN_INDEX: {
      ret = JS_NewInt32(ctx, ImGui::TableGetColumnIndex());
      break;
    }
    case IMGUI_TABLE_GET_ROW_INDEX: {
      ret = JS_NewInt32(ctx, ImGui::TableGetRowIndex());
      break;
    }
    case IMGUI_TABLE_GET_COLUMN_NAME: {
      int32_t col = -1;
      if(argc >= 1)
        JS_ToInt32(ctx, &col, argv[0]);
      ret = JS_NewString(ctx, ImGui::TableGetColumnName(col));
      break;
    }
    case IMGUI_TABLE_GET_COLUMN_FLAGS: {
      int32_t col = -1;
      if(argc >= 1)
        JS_ToInt32(ctx, &col, argv[0]);
      ret = JS_NewInt32(ctx, ImGui::TableGetColumnFlags(col));
      break;
    }
    case IMGUI_TABLE_SET_COLUMN_ENABLED: {
      int32_t col;
      JS_ToInt32(ctx, &col, argv[0]);
      ImGui::TableSetColumnEnabled(col, JS_ToBool(ctx, argv[1]));
      break;
    }
    case IMGUI_TABLE_SET_BG_COLOR: break;
    case IMGUI_BUILD_LOOKUP_TABLE: break;
    case IMGUI_CLOSE_CURRENT_POPUP: {
      ImGui::CloseCurrentPopup();
      break;
    }
    case IMGUI_COLUMNS: {
      int32_t count = 1;
      const char* id = 0;
      bool border = true;
      if(argc >= 1)
        JS_ToInt32(ctx, &count, argv[0]);
      if(argc >= 2)
        id = JS_ToCString(ctx, argv[1]);
      if(argc >= 3)
        border = JS_ToBool(ctx, argv[2]);
      ImGui::Columns(count, id, border);
      if(id)
        JS_FreeCString(ctx, id);
      break;
    }
    case IMGUI_NEXT_COLUMN: {
      ImGui::NextColumn();
      break;
    }
    case IMGUI_GET_COLUMN_INDEX: {
      ret = JS_NewInt32(ctx, ImGui::GetColumnIndex());
      break;
    }
    case IMGUI_GET_COLUMN_WIDTH: {
      int32_t col = -1;
      if(argc >= 1)
        JS_ToInt32(ctx, &col, argv[0]);
      ret = JS_NewFloat64(ctx, ImGui::GetColumnWidth(col));
      break;
    }
    case IMGUI_SET_COLUMN_WIDTH: {
      int32_t col;
      double width;
      JS_ToInt32(ctx, &col, argv[0]);
      JS_ToFloat64(ctx, &width, argv[1]);
      ImGui::SetColumnWidth(col, width);
      break;
    }
    case IMGUI_GET_COLUMN_OFFSET: {
      int32_t col = -1;
      if(argc >= 1)
        JS_ToInt32(ctx, &col, argv[0]);
      ret = JS_NewFloat64(ctx, ImGui::GetColumnOffset(col));
      break;
    }
    case IMGUI_SET_COLUMN_OFFSET: {
      int32_t col;
      double offset_x;
      JS_ToInt32(ctx, &col, argv[0]);
      JS_ToFloat64(ctx, &offset_x, argv[1]);
      ImGui::SetColumnOffset(col, offset_x);
      break;
    }
    case IMGUI_GET_COLUMNS_COUNT: {
      ret = JS_NewUint32(ctx, ImGui::GetColumnsCount());
      break;
    }
    case IMGUI_BEGIN_TAB_BAR: {
      const char* str_id = JS_ToCString(ctx, argv[0]);
      int32_t flags = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &flags, argv[1]);
      ret = JS_NewBool(ctx, ImGui::BeginTabBar(str_id, flags));
      JS_FreeCString(ctx, str_id);
      break;
    }
    case IMGUI_END_TAB_BAR: {
      ImGui::EndTabBar();
      break;
    }
    case IMGUI_BEGIN_TAB_ITEM: break;
    case IMGUI_END_TAB_ITEM: {
      ImGui::EndTabItem();
      break;
    }
    case IMGUI_TAB_ITEM_BUTTON: {
      const char* label = JS_ToCString(ctx, argv[0]);
      int32_t flags = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &flags, argv[1]);
      ret = JS_NewBool(ctx, ImGui::TabItemButton(label, flags));
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_SET_TAB_ITEM_CLOSED: {
      const char* label = JS_ToCString(ctx, argv[0]);
      ImGui::SetTabItemClosed(label);
      JS_FreeCString(ctx, label);
      break;
    }
    case IMGUI_LOG_TO_TTY: {
      int32_t auto_open_depth = -1;
      if(argc >= 1)
        JS_ToInt32(ctx, &auto_open_depth, argv[0]);
      ImGui::LogToTTY(auto_open_depth);
      break;
    }
    case IMGUI_LOG_TO_FILE: {
      int32_t auto_open_depth = -1;
      const char* filename = 0;
      if(argc >= 1)
        JS_ToInt32(ctx, &auto_open_depth, argv[0]);
      if(argc >= 2)
        filename = JS_ToCString(ctx, argv[1]);
      ImGui::LogToFile(auto_open_depth, filename);
      if(filename)
        JS_FreeCString(ctx, filename);
      break;
    }
    case IMGUI_LOG_TO_CLIPBOARD: {
      int32_t auto_open_depth = -1;
      if(argc >= 1)
        JS_ToInt32(ctx, &auto_open_depth, argv[0]);
      ImGui::LogToClipboard(auto_open_depth);
      break;
    }
    case IMGUI_LOG_FINISH: {
      ImGui::LogFinish();
      break;
    }
    case IMGUI_LOG_BUTTONS: {
      ImGui::LogButtons();
      break;
    }
    case IMGUI_LOG_TEXT: {
      int count = js_imgui_formatcount(ctx, argc, argv);
      assert(count <= 32);
      void* a[count];
      js_imgui_formatargs(ctx, argc, argv, a);
      ImGui::LogText((const char*)a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
      break;
    }
    case IMGUI_BEGIN_DRAG_DROP_SOURCE: {
      int32_t flags = 0;
      if(argc >= 1)
        JS_ToInt32(ctx, &flags, argv[0]);
      ret = JS_NewBool(ctx, ImGui::BeginDragDropSource(flags));
      break;
    }
    case IMGUI_SET_DRAG_DROP_PAYLOAD: {
      const char* type = JS_ToCString(ctx, argv[0]);
      uint8_t* ptr;
      size_t len;
      int32_t cond = 0;
      if(argc >= 3)
        JS_ToInt32(ctx, &cond, argv[2]);
      ptr = JS_GetArrayBuffer(ctx, &len, argv[1]);
      ret = JS_NewBool(ctx, ImGui::SetDragDropPayload(type, ptr, len, cond));
      JS_FreeCString(ctx, type);
      break;
    }
    case IMGUI_END_DRAG_DROP_SOURCE: {
      ImGui::EndDragDropSource();
      break;
    }
    case IMGUI_BEGIN_DRAG_DROP_TARGET: {
      ret = JS_NewBool(ctx, ImGui::BeginDragDropTarget());
      break;
    }
    case IMGUI_ACCEPT_DRAG_DROP_PAYLOAD: {
      const char* type = JS_ToCString(ctx, argv[0]);
      int32_t flags = 0;
      if(argc >= 2)
        JS_ToInt32(ctx, &flags, argv[1]);
      ret = js_imgui_payload_wrap(ctx, new ImGuiPayload(*ImGui::AcceptDragDropPayload(type, flags)));
      JS_FreeCString(ctx, type);
      break;
    }
    case IMGUI_END_DRAG_DROP_TARGET: {
      ImGui::EndDragDropTarget();
      break;
    }
    case IMGUI_GET_DRAG_DROP_PAYLOAD: {
      ret = js_imgui_payload_wrap(ctx, new ImGuiPayload(*ImGui::GetDragDropPayload()));
      break;
    }
    case IMGUI_BEGIN_DISABLED: {
      bool disabled = true;
      if(argc >= 1)
        disabled = JS_ToBool(ctx, argv[0]);
      ImGui::BeginDisabled(disabled);
      break;
    }
    case IMGUI_END_DISABLED: {
      ImGui::EndDisabled();
      break;
    }
    case IMGUI_PUSH_CLIP_RECT: {
      ImVec2 clip_rect_min = js_imgui_getimvec2(ctx, argv[0]), clip_rect_max = js_imgui_getimvec2(ctx, argv[1]);
      bool intersect_with_current_clip_rect = JS_ToBool(ctx, argv[2]);
      ImGui::PushClipRect(clip_rect_min, clip_rect_max, intersect_with_current_clip_rect);
      break;
    }
    case IMGUI_POP_CLIP_RECT: {
      ImGui::PopClipRect();
      break;
    }
    case IMGUI_SET_ITEM_DEFAULT_FOCUS: {
      ImGui::SetItemDefaultFocus();
      break;
    }
    case IMGUI_SET_KEYBOARD_FOCUS_HERE: {
      int32_t offset = 0;
      if(argc >= 1)
        JS_ToInt32(ctx, &offset, argv[0]);
      ImGui::SetKeyboardFocusHere(offset);
      break;
    }
    case IMGUI_IS_ITEM_HOVERED: {
      int32_t flags = 0;
      if(argc >= 1)
        JS_ToInt32(ctx, &flags, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsItemHovered(flags));
      break;
    }
    case IMGUI_IS_ITEM_ACTIVE: {
      ret = JS_NewBool(ctx, ImGui::IsItemActive());
      break;
    }
    case IMGUI_IS_ITEM_FOCUSED: {
      ret = JS_NewBool(ctx, ImGui::IsItemFocused());
      break;
    }
    case IMGUI_IS_ITEM_CLICKED: {
      int32_t mouse_button = 0;
      if(argc >= 1)
        JS_ToInt32(ctx, &mouse_button, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsItemClicked(mouse_button));
      break;
    }
    case IMGUI_IS_ITEM_VISIBLE: {
      ret = JS_NewBool(ctx, ImGui::IsItemVisible());
      break;
    }
    case IMGUI_IS_ITEM_EDITED: {
      ret = JS_NewBool(ctx, ImGui::IsItemEdited());
      break;
    }
    case IMGUI_IS_ITEM_ACTIVATED: {
      ret = JS_NewBool(ctx, ImGui::IsItemActivated());
      break;
    }
    case IMGUI_IS_ITEM_DEACTIVATED: {
      ret = JS_NewBool(ctx, ImGui::IsItemDeactivated());
      break;
    }
    case IMGUI_IS_ITEM_DEACTIVATED_AFTER_EDIT: {
      ret = JS_NewBool(ctx, ImGui::IsItemDeactivatedAfterEdit());
      break;
    }
    case IMGUI_IS_ANY_ITEM_HOVERED: {
      ret = JS_NewBool(ctx, ImGui::IsAnyItemHovered());
      break;
    }
    case IMGUI_IS_ANY_ITEM_ACTIVE: {
      ret = JS_NewBool(ctx, ImGui::IsAnyItemActive());
      break;
    }
    case IMGUI_IS_ANY_ITEM_FOCUSED: {
      ret = JS_NewBool(ctx, ImGui::IsAnyItemFocused());
      break;
    }
    case IMGUI_GET_ITEM_RECT_MIN: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetItemRectMin());
      break;
    }
    case IMGUI_GET_ITEM_RECT_MAX: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetItemRectMax());
      break;
    }
    case IMGUI_GET_ITEM_RECT_SIZE: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetItemRectSize());
      break;
    }
    case IMGUI_SET_ITEM_ALLOW_OVERLAP: {
      ImGui::SetItemAllowOverlap();
      break;
    }
    case IMGUI_IS_RECT_VISIBLE: {
      if(argc >= 2) {
        ImVec2 rect_min = js_imgui_getimvec2(ctx, argv[0]), rect_max = js_imgui_getimvec2(ctx, argv[1]);
        ret = JS_NewBool(ctx, ImGui::IsRectVisible(rect_min, rect_max));
      } else {
        ImVec2 size = js_imgui_getimvec2(ctx, argv[0]);
        ret = JS_NewBool(ctx, ImGui::IsRectVisible(size));
      }
      break;
    }
    case IMGUI_GET_TIME: {
      ret = JS_NewFloat64(ctx, ImGui::GetTime());
      break;
    }
    case IMGUI_GET_FRAME_COUNT: {
      ret = JS_NewInt64(ctx, ImGui::GetFrameCount());
      break;
    }
    case IMGUI_GET_BACKGROUND_DRAW_LIST: break;
    case IMGUI_GET_FOREGROUND_DRAW_LIST: break;
    case IMGUI_GET_DRAW_LIST_SHARED_DATA: break;
    case IMGUI_GET_STYLE_COLOR_NAME: {
      int32_t idx;
      JS_ToInt32(ctx, &idx, argv[0]);
      ret = JS_NewString(ctx, ImGui::GetStyleColorName(idx));
      break;
    }
    case IMGUI_SET_STATE_STORAGE: break;
    case IMGUI_GET_STATE_STORAGE: break;
    case IMGUI_CALC_TEXT_SIZE: {
      const char *text = JS_ToCString(ctx, argv[0]), *text_end = 0;
      bool hide_text_after_double_hash = false;
      double wrap_width = -1.0f;
      if(argc >= 2)
        text_end = JS_ToCString(ctx, argv[1]);
      if(argc >= 3)
        hide_text_after_double_hash = JS_ToBool(ctx, argv[2]);
      if(argc >= 4)
        JS_ToFloat64(ctx, &wrap_width, argv[3]);
      ret = js_imgui_newimvec2(ctx, ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width));
      JS_FreeCString(ctx, text);
      if(text_end)
        JS_FreeCString(ctx, text_end);
      break;
    }
    case IMGUI_CALC_LIST_CLIPPING: break;
    case IMGUI_BEGIN_CHILD_FRAME: {
      int32_t id, window_flags = 0;
      ImVec2 size = js_imgui_getimvec2(ctx, argv[1]);
      JS_ToInt32(ctx, &id, argv[0]);
      if(argc >= 3)
        JS_ToInt32(ctx, &window_flags, argv[2]);
      ret = JS_NewBool(ctx, ImGui::BeginChildFrame(id, size, window_flags));
      break;
    }
    case IMGUI_END_CHILD_FRAME: {
      ImGui::EndChildFrame();
      break;
    }
    case IMGUI_COLOR_CONVERTU32_TO_FLOAT4: {
      uint32_t in;
      JS_ToUint32(ctx, &in, argv[0]);
      ret = js_imgui_newimvec4(ctx, ImGui::ColorConvertU32ToFloat4(in));
      break;
    }
    case IMGUI_COLOR_CONVERT_FLOAT4_TOU32: {
      ImVec4 in = js_imgui_getimvec4(ctx, argv[0]);
      ret = JS_NewUint32(ctx, ImGui::ColorConvertFloat4ToU32(in));
      break;
    }
    case IMGUI_COLOR_CONVERT_RGB_TO_HSV: {
      double r, g, b;
      float h, s, v;
      JS_ToFloat64(ctx, &r, argv[0]);
      JS_ToFloat64(ctx, &g, argv[1]);
      JS_ToFloat64(ctx, &b, argv[2]);
      ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
      ret = JS_NewArray(ctx);
      JS_SetPropertyUint32(ctx, ret, 0, JS_NewFloat64(ctx, h));
      JS_SetPropertyUint32(ctx, ret, 1, JS_NewFloat64(ctx, s));
      JS_SetPropertyUint32(ctx, ret, 2, JS_NewFloat64(ctx, v));
      break;
    }
    case IMGUI_COLOR_CONVERT_HSV_TO_RGB: {
      double h, s, v;
      float r, g, b;
      JS_ToFloat64(ctx, &h, argv[0]);
      JS_ToFloat64(ctx, &s, argv[1]);
      JS_ToFloat64(ctx, &v, argv[2]);
      ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
      ret = JS_NewArray(ctx);
      JS_SetPropertyUint32(ctx, ret, 0, JS_NewFloat64(ctx, r));
      JS_SetPropertyUint32(ctx, ret, 1, JS_NewFloat64(ctx, g));
      JS_SetPropertyUint32(ctx, ret, 2, JS_NewFloat64(ctx, b));
      break;
    }
    case IMGUI_GET_KEY_INDEX: {
      int32_t imgui_key;
      JS_ToInt32(ctx, &imgui_key, argv[0]);
      ret = JS_NewInt32(ctx, ImGui::GetKeyIndex(imgui_key));
      break;
    }
    case IMGUI_IS_KEY_DOWN: {
      int32_t user_key_index;
      JS_ToInt32(ctx, &user_key_index, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsKeyDown(user_key_index));
      break;
    }
    case IMGUI_IS_KEY_PRESSED: {
      int32_t user_key_index;
      bool repeat = true;
      if(argc >= 2)
        repeat = JS_ToBool(ctx, argv[1]);
      JS_ToInt32(ctx, &user_key_index, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsKeyPressed(user_key_index, repeat));
      break;
    }
    case IMGUI_IS_KEY_RELEASED: {
      int32_t user_key_index;
      JS_ToInt32(ctx, &user_key_index, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsKeyReleased(user_key_index));
      break;
    }
    case IMGUI_GET_KEY_PRESSED_AMOUNT: {
      int32_t key_index;
      double repeat_delay, rate;
      JS_ToInt32(ctx, &key_index, argv[0]);
      JS_ToFloat64(ctx, &repeat_delay, argv[1]);
      JS_ToFloat64(ctx, &rate, argv[2]);
      ret = JS_NewInt32(ctx, ImGui::GetKeyPressedAmount(key_index, repeat_delay, rate));
      break;
    }
    case IMGUI_IS_MOUSE_DOWN: {
      int32_t button;
      JS_ToInt32(ctx, &button, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsMouseDown(button));
      break;
    }
    case IMGUI_IS_ANY_MOUSE_DOWN: {
      ret = JS_NewBool(ctx, ImGui::IsAnyMouseDown());
      break;
    }
    case IMGUI_IS_MOUSE_CLICKED: {
      int32_t button;
      bool repeat = true;
      if(argc >= 2)
        repeat = JS_ToBool(ctx, argv[1]);
      JS_ToInt32(ctx, &button, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsMouseClicked(button, repeat));
      break;
    }
    case IMGUI_IS_MOUSE_DOUBLE_CLICKED: {
      int32_t button;
      JS_ToInt32(ctx, &button, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsMouseDoubleClicked(button));
      break;
    }
    case IMGUI_IS_MOUSE_RELEASED: {
      int32_t button;
      JS_ToInt32(ctx, &button, argv[0]);
      ret = JS_NewBool(ctx, ImGui::IsMouseReleased(button));
      break;
    }
    case IMGUI_IS_MOUSE_DRAGGING: {
      int32_t button;
      double lock_threshold = -1.0;
      JS_ToInt32(ctx, &button, argv[0]);
      if(argc >= 2)
        JS_ToFloat64(ctx, &lock_threshold, argv[1]);
      ret = JS_NewBool(ctx, ImGui::IsMouseDragging(button, lock_threshold));
      break;
    }
    case IMGUI_IS_MOUSE_HOVERING_RECT: {
      ImVec2 r_min = js_imgui_getimvec2(ctx, argv[0]), r_max = js_imgui_getimvec2(ctx, argv[1]);
      bool clip = true;
      if(argc >= 3)
        clip = JS_ToBool(ctx, argv[2]);
      ImGui::IsMouseHoveringRect(r_min, r_max, clip);
      break;
    }
    case IMGUI_IS_MOUSE_POS_VALID: {
      const ImVec2* ptr = 0;
      ImVec2 pos;
      if(argc >= 1) {
        pos = js_imgui_getimvec2(ctx, argv[0]);
        ptr = &pos;
      }
      ret = JS_NewBool(ctx, ImGui::IsMousePosValid(ptr));
      break;
    }
    case IMGUI_GET_MOUSE_POS: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetMousePos());
      break;
    }
    case IMGUI_GET_MOUSE_POS_ON_OPENING_CURRENT_POPUP: {
      ret = js_imgui_newimvec2(ctx, ImGui::GetMousePosOnOpeningCurrentPopup());
      break;
    }
    case IMGUI_GET_MOUSE_DRAG_DELTA: {
      int32_t mouse_button = 0;
      double lock_threshold = -1.0;
      if(argc >= 1)
        JS_ToInt32(ctx, &mouse_button, argv[0]);
      if(argc >= 2)
        JS_ToFloat64(ctx, &lock_threshold, argv[1]);
      ret = js_imgui_newimvec2(ctx, ImGui::GetMouseDragDelta(mouse_button, lock_threshold));
      break;
    }
    case IMGUI_RESET_MOUSE_DRAG_DELTA: {
      int32_t mouse_button = 0;
      if(argc >= 1)
        JS_ToInt32(ctx, &mouse_button, argv[0]);
      ImGui::ResetMouseDragDelta(mouse_button);
      break;
    }
    case IMGUI_GET_MOUSE_CURSOR: {
      ret = JS_NewInt32(ctx, ImGui::GetMouseCursor());
      break;
    }
    case IMGUI_SET_MOUSE_CURSOR: {
      int32_t mouse_cursor;
      JS_ToInt32(ctx, &mouse_cursor, argv[0]);
      ImGui::SetMouseCursor(mouse_cursor);
      break;
    }
    case IMGUI_CAPTURE_KEYBOARD_FROM_APP: {
      bool want_capture = true;
      if(argc >= 1)
        want_capture = JS_ToBool(ctx, argv[0]);
      ImGui::CaptureKeyboardFromApp(want_capture);
      break;
    }
    case IMGUI_CAPTURE_MOUSE_FROM_APP: {
      bool want_capture = true;
      if(argc >= 1)
        want_capture = JS_ToBool(ctx, argv[0]);
      ImGui::CaptureMouseFromApp(want_capture);
      break;
    }
    case IMGUI_GET_CLIPBOARD_TEXT: {
      ret = JS_NewString(ctx, ImGui::GetClipboardText());
      break;
    }
    case IMGUI_SET_CLIPBOARD_TEXT: {
      const char* text = JS_ToCString(ctx, argv[0]);
      ImGui::SetClipboardText(text);
      JS_FreeCString(ctx, text);

      break;
    }
    case IMGUI_LOAD_INI_SETTINGS_FROM_DISK: {
      const char* file = JS_ToCString(ctx, argv[0]);
      ImGui::LoadIniSettingsFromDisk(file);
      JS_FreeCString(ctx, file);
      break;
    }
    case IMGUI_LOAD_INI_SETTINGS_FROM_MEMORY: {
      uint8_t* ptr;
      size_t len;
      if(JS_IsString(argv[0])) {
        const char* data = JS_ToCStringLen(ctx, &len, argv[0]);
        ImGui::LoadIniSettingsFromMemory(data, len);
        JS_FreeCString(ctx, data);
      } else if((ptr = JS_GetArrayBuffer(ctx, &len, argv[0]))) {
        ImGui::LoadIniSettingsFromMemory(reinterpret_cast<const char*>(ptr), len);
      } else {
        ret = JS_ThrowInternalError(ctx, "argument 1 is neither String nor ArrayBuffer");
      }
      break;
    }
    case IMGUI_SAVE_INI_SETTINGS_TO_DISK: {
      const char* file = JS_ToCString(ctx, argv[0]);
      ImGui::SaveIniSettingsToDisk(file);
      JS_FreeCString(ctx, file);
      break;
    }
    case IMGUI_SAVE_INI_SETTINGS_TO_MEMORY: {
      size_t len;
      const char* data = ImGui::SaveIniSettingsToMemory(&len);

      ret = JS_NewArrayBufferCopy(ctx, reinterpret_cast<const uint8_t*>(data), len);
      break;
    }
    case IMGUI_SET_ALLOCATOR_FUNCTIONS: break;
    case IMGUI_MEM_ALLOC: {
      uint64_t len;
      void* data;
      JS_ToIndex(ctx, &len, argv[0]);
      data = ImGui::MemAlloc(len);
      ret = JS_NewArrayBuffer(ctx, static_cast<uint8_t*>(data), len, js_imgui_free_func, (void*)len, FALSE);
      break;
    }
    case IMGUI_MEM_FREE: {
      JS_DetachArrayBuffer(ctx, argv[0]);
      break;
    }
  }

  return ret;
}

static const JSCFunctionListEntry js_imgui_static_funcs[] = {
    JS_CFUNC_MAGIC_DEF("Init", 1, js_imgui_functions, IMGUI_INIT),
    JS_CFUNC_MAGIC_DEF("CreateContext", 0, js_imgui_functions, IMGUI_CREATE_CONTEXT),
    JS_CFUNC_MAGIC_DEF("DestroyContext", 1, js_imgui_functions, IMGUI_DESTROY_CONTEXT),
    JS_CFUNC_MAGIC_DEF("GetCurrentContext", 0, js_imgui_functions, IMGUI_GET_CURRENT_CONTEXT),
    JS_CFUNC_MAGIC_DEF("SetCurrentContext", 1, js_imgui_functions, IMGUI_SET_CURRENT_CONTEXT),
    JS_CFUNC_MAGIC_DEF("GetIO", 0, js_imgui_functions, IMGUI_GET_IO),
    JS_CFUNC_MAGIC_DEF("GetStyle", 0, js_imgui_functions, IMGUI_GET_STYLE),
    JS_CFUNC_MAGIC_DEF("NewFrame", 0, js_imgui_functions, IMGUI_NEW_FRAME),
    JS_CFUNC_MAGIC_DEF("EndFrame", 0, js_imgui_functions, IMGUI_END_FRAME),
    JS_CFUNC_MAGIC_DEF("Render", 0, js_imgui_functions, IMGUI_RENDER),
    JS_CFUNC_MAGIC_DEF("GetDrawData", 0, js_imgui_functions, IMGUI_GET_DRAW_DATA),
    JS_CFUNC_MAGIC_DEF("RenderDrawData", 0, js_imgui_functions, IMGUI_RENDER_DRAW_DATA),
    JS_CFUNC_MAGIC_DEF("ShowDemoWindow", 1, js_imgui_functions, IMGUI_SHOW_DEMO_WINDOW),
    JS_CFUNC_MAGIC_DEF("ShowAboutWindow", 1, js_imgui_functions, IMGUI_SHOW_ABOUT_WINDOW),
    JS_CFUNC_MAGIC_DEF("ShowMetricsWindow", 1, js_imgui_functions, IMGUI_SHOW_METRICS_WINDOW),
    JS_CFUNC_MAGIC_DEF("ShowStyleEditor", 1, js_imgui_functions, IMGUI_SHOW_STYLE_EDITOR),
    JS_CFUNC_MAGIC_DEF("ShowStyleSelector", 1, js_imgui_functions, IMGUI_SHOW_STYLE_SELECTOR),
    JS_CFUNC_MAGIC_DEF("ShowFontSelector", 1, js_imgui_functions, IMGUI_SHOW_FONT_SELECTOR),
    JS_CFUNC_MAGIC_DEF("ShowUserGuide", 0, js_imgui_functions, IMGUI_SHOW_USER_GUIDE),
    JS_CFUNC_MAGIC_DEF("GetVersion", 0, js_imgui_functions, IMGUI_GET_VERSION),
    JS_CFUNC_MAGIC_DEF("StyleColorsDark", 1, js_imgui_functions, IMGUI_STYLE_COLORS_DARK),
    JS_CFUNC_MAGIC_DEF("StyleColorsClassic", 1, js_imgui_functions, IMGUI_STYLE_COLORS_CLASSIC),
    JS_CFUNC_MAGIC_DEF("StyleColorsLight", 1, js_imgui_functions, IMGUI_STYLE_COLORS_LIGHT),
    JS_CFUNC_MAGIC_DEF("Begin", 3, js_imgui_functions, IMGUI_BEGIN),
    JS_CFUNC_MAGIC_DEF("End", 0, js_imgui_functions, IMGUI_END),
    JS_CFUNC_MAGIC_DEF("BeginChild", 4, js_imgui_functions, IMGUI_BEGIN_CHILD),
    JS_CFUNC_MAGIC_DEF("EndChild", 0, js_imgui_functions, IMGUI_END_CHILD),
    JS_CFUNC_MAGIC_DEF("IsWindowAppearing", 0, js_imgui_functions, IMGUI_IS_WINDOW_APPEARING),
    JS_CFUNC_MAGIC_DEF("IsWindowCollapsed", 0, js_imgui_functions, IMGUI_IS_WINDOW_COLLAPSED),
    JS_CFUNC_MAGIC_DEF("IsWindowFocused", 1, js_imgui_functions, IMGUI_IS_WINDOW_FOCUSED),
    JS_CFUNC_MAGIC_DEF("IsWindowHovered", 1, js_imgui_functions, IMGUI_IS_WINDOW_HOVERED),
    JS_CFUNC_MAGIC_DEF("GetWindowDrawList", 0, js_imgui_functions, IMGUI_GET_WINDOW_DRAW_LIST),
    JS_CFUNC_MAGIC_DEF("GetWindowPos", 0, js_imgui_functions, IMGUI_GET_WINDOW_POS),
    JS_CFUNC_MAGIC_DEF("GetWindowSize", 0, js_imgui_functions, IMGUI_GET_WINDOW_SIZE),
    JS_CFUNC_MAGIC_DEF("GetWindowWidth", 0, js_imgui_functions, IMGUI_GET_WINDOW_WIDTH),
    JS_CFUNC_MAGIC_DEF("GetWindowHeight", 0, js_imgui_functions, IMGUI_GET_WINDOW_HEIGHT),
    JS_CFUNC_MAGIC_DEF("GetContentRegionMax", 0, js_imgui_functions, IMGUI_GET_CONTENT_REGION_MAX),
    JS_CFUNC_MAGIC_DEF("GetContentRegionAvail", 0, js_imgui_functions, IMGUI_GET_CONTENT_REGION_AVAIL),
    JS_CFUNC_MAGIC_DEF("GetWindowContentRegionMin", 0, js_imgui_functions, IMGUI_GET_WINDOW_CONTENT_REGION_MIN),
    JS_CFUNC_MAGIC_DEF("GetWindowContentRegionMax", 0, js_imgui_functions, IMGUI_GET_WINDOW_CONTENT_REGION_MAX),
    JS_CFUNC_MAGIC_DEF("SetNextWindowPos", 3, js_imgui_functions, IMGUI_SET_NEXT_WINDOW_POS),
    JS_CFUNC_MAGIC_DEF("SetNextWindowSize", 2, js_imgui_functions, IMGUI_SET_NEXT_WINDOW_SIZE),
    JS_CFUNC_MAGIC_DEF("SetNextWindowSizeConstraints", 4, js_imgui_functions, IMGUI_SET_NEXT_WINDOW_SIZE_CONSTRAINTS),
    JS_CFUNC_MAGIC_DEF("SetNextWindowContentSize", 1, js_imgui_functions, IMGUI_SET_NEXT_WINDOW_CONTENT_SIZE),
    JS_CFUNC_MAGIC_DEF("SetNextWindowCollapsed", 2, js_imgui_functions, IMGUI_SET_NEXT_WINDOW_COLLAPSED),
    JS_CFUNC_MAGIC_DEF("SetNextWindowFocus", 0, js_imgui_functions, IMGUI_SET_NEXT_WINDOW_FOCUS),
    JS_CFUNC_MAGIC_DEF("SetNextWindowBgAlpha", 1, js_imgui_functions, IMGUI_SET_NEXT_WINDOW_BG_ALPHA),
    JS_CFUNC_MAGIC_DEF("SetWindowPos", 3, js_imgui_functions, IMGUI_SET_WINDOW_POS),
    JS_CFUNC_MAGIC_DEF("SetWindowSize", 3, js_imgui_functions, IMGUI_SET_WINDOW_SIZE),
    JS_CFUNC_MAGIC_DEF("SetWindowCollapsed", 3, js_imgui_functions, IMGUI_SET_WINDOW_COLLAPSED),
    JS_CFUNC_MAGIC_DEF("SetWindowFocus", 1, js_imgui_functions, IMGUI_SET_WINDOW_FOCUS),
    JS_CFUNC_MAGIC_DEF("SetWindowFontScale", 1, js_imgui_functions, IMGUI_SET_WINDOW_FONT_SCALE),
    JS_CFUNC_MAGIC_DEF("GetScrollX", 0, js_imgui_functions, IMGUI_GET_SCROLL_X),
    JS_CFUNC_MAGIC_DEF("GetScrollY", 0, js_imgui_functions, IMGUI_GET_SCROLL_Y),
    JS_CFUNC_MAGIC_DEF("GetScrollMaxX", 0, js_imgui_functions, IMGUI_GET_SCROLL_MAX_X),
    JS_CFUNC_MAGIC_DEF("GetScrollMaxY", 0, js_imgui_functions, IMGUI_GET_SCROLL_MAX_Y),
    JS_CFUNC_MAGIC_DEF("SetScrollX", 1, js_imgui_functions, IMGUI_SET_SCROLL_X),
    JS_CFUNC_MAGIC_DEF("SetScrollY", 1, js_imgui_functions, IMGUI_SET_SCROLL_Y),
    JS_CFUNC_MAGIC_DEF("SetScrollHereY", 1, js_imgui_functions, IMGUI_SET_SCROLL_HERE_Y),
    JS_CFUNC_MAGIC_DEF("SetScrollFromPosY", 2, js_imgui_functions, IMGUI_SET_SCROLL_FROM_POS_Y),
    JS_CFUNC_MAGIC_DEF("PushFont", 1, js_imgui_functions, IMGUI_PUSH_FONT),
    JS_CFUNC_MAGIC_DEF("PopFont", 0, js_imgui_functions, IMGUI_POP_FONT),
    JS_CFUNC_MAGIC_DEF("PushStyleColor", 2, js_imgui_functions, IMGUI_PUSH_STYLE_COLOR),
    JS_CFUNC_MAGIC_DEF("PopStyleColor", 1, js_imgui_functions, IMGUI_POP_STYLE_COLOR),
    JS_CFUNC_MAGIC_DEF("PushStyleVar", 2, js_imgui_functions, IMGUI_PUSH_STYLE_VAR),
    JS_CFUNC_MAGIC_DEF("PopStyleVar", 1, js_imgui_functions, IMGUI_POP_STYLE_VAR),
    JS_CFUNC_MAGIC_DEF("GetStyleColorVec4", 1, js_imgui_functions, IMGUI_GET_STYLE_COLOR_VEC4),
    JS_CFUNC_MAGIC_DEF("GetFont", 0, js_imgui_functions, IMGUI_GET_FONT),
    JS_CFUNC_MAGIC_DEF("GetFontSize", 0, js_imgui_functions, IMGUI_GET_FONT_SIZE),
    JS_CFUNC_MAGIC_DEF("GetFontTexUvWhitePixel", 0, js_imgui_functions, IMGUI_GET_FONT_TEX_UV_WHITE_PIXEL),
    JS_CFUNC_MAGIC_DEF("GetColorU32", 1, js_imgui_functions, IMGUI_GET_COLORU32),
    JS_CFUNC_MAGIC_DEF("PushItemWidth", 1, js_imgui_functions, IMGUI_PUSH_ITEM_WIDTH),
    JS_CFUNC_MAGIC_DEF("PopItemWidth", 0, js_imgui_functions, IMGUI_POP_ITEM_WIDTH),
    JS_CFUNC_MAGIC_DEF("CalcItemWidth", 0, js_imgui_functions, IMGUI_CALC_ITEM_WIDTH),
    JS_CFUNC_MAGIC_DEF("PushTextWrapPos", 1, js_imgui_functions, IMGUI_PUSH_TEXT_WRAP_POS),
    JS_CFUNC_MAGIC_DEF("PopTextWrapPos", 0, js_imgui_functions, IMGUI_POP_TEXT_WRAP_POS),
    JS_CFUNC_MAGIC_DEF("PushAllowKeyboardFocus", 1, js_imgui_functions, IMGUI_PUSH_ALLOW_KEYBOARD_FOCUS),
    JS_CFUNC_MAGIC_DEF("PopAllowKeyboardFocus", 0, js_imgui_functions, IMGUI_POP_ALLOW_KEYBOARD_FOCUS),
    JS_CFUNC_MAGIC_DEF("PushButtonRepeat", 1, js_imgui_functions, IMGUI_PUSH_BUTTON_REPEAT),
    JS_CFUNC_MAGIC_DEF("PopButtonRepeat", 0, js_imgui_functions, IMGUI_POP_BUTTON_REPEAT),
    JS_CFUNC_MAGIC_DEF("Separator", 0, js_imgui_functions, IMGUI_SEPARATOR),
    JS_CFUNC_MAGIC_DEF("SameLine", 2, js_imgui_functions, IMGUI_SAME_LINE),
    JS_CFUNC_MAGIC_DEF("NewLine", 0, js_imgui_functions, IMGUI_NEW_LINE),
    JS_CFUNC_MAGIC_DEF("Spacing", 0, js_imgui_functions, IMGUI_SPACING),
    JS_CFUNC_MAGIC_DEF("Dummy", 1, js_imgui_functions, IMGUI_DUMMY),
    JS_CFUNC_MAGIC_DEF("Indent", 1, js_imgui_functions, IMGUI_INDENT),
    JS_CFUNC_MAGIC_DEF("Unindent", 1, js_imgui_functions, IMGUI_UNINDENT),
    JS_CFUNC_MAGIC_DEF("BeginGroup", 0, js_imgui_functions, IMGUI_BEGIN_GROUP),
    JS_CFUNC_MAGIC_DEF("EndGroup", 0, js_imgui_functions, IMGUI_END_GROUP),
    JS_CFUNC_MAGIC_DEF("GetCursorPos", 0, js_imgui_functions, IMGUI_GET_CURSOR_POS),
    JS_CFUNC_MAGIC_DEF("GetCursorPosX", 0, js_imgui_functions, IMGUI_GET_CURSOR_POS_X),
    JS_CFUNC_MAGIC_DEF("GetCursorPosY", 0, js_imgui_functions, IMGUI_GET_CURSOR_POS_Y),
    JS_CFUNC_MAGIC_DEF("SetCursorPos", 1, js_imgui_functions, IMGUI_SET_CURSOR_POS),
    JS_CFUNC_MAGIC_DEF("SetCursorPosX", 1, js_imgui_functions, IMGUI_SET_CURSOR_POS_X),
    JS_CFUNC_MAGIC_DEF("SetCursorPosY", 1, js_imgui_functions, IMGUI_SET_CURSOR_POS_Y),
    JS_CFUNC_MAGIC_DEF("GetCursorStartPos", 0, js_imgui_functions, IMGUI_GET_CURSOR_START_POS),
    JS_CFUNC_MAGIC_DEF("GetCursorScreenPos", 0, js_imgui_functions, IMGUI_GET_CURSOR_SCREEN_POS),
    JS_CFUNC_MAGIC_DEF("SetCursorScreenPos", 1, js_imgui_functions, IMGUI_SET_CURSOR_SCREEN_POS),
    JS_CFUNC_MAGIC_DEF("AlignTextToFramePadding", 0, js_imgui_functions, IMGUI_ALIGN_TEXT_TO_FRAME_PADDING),
    JS_CFUNC_MAGIC_DEF("GetTextLineHeight", 0, js_imgui_functions, IMGUI_GET_TEXT_LINE_HEIGHT),
    JS_CFUNC_MAGIC_DEF("GetTextLineHeightWithSpacing", 0, js_imgui_functions, IMGUI_GET_TEXT_LINE_HEIGHT_WITH_SPACING),
    JS_CFUNC_MAGIC_DEF("GetFrameHeight", 0, js_imgui_functions, IMGUI_GET_FRAME_HEIGHT),
    JS_CFUNC_MAGIC_DEF("GetFrameHeightWithSpacing", 0, js_imgui_functions, IMGUI_GET_FRAME_HEIGHT_WITH_SPACING),
    JS_CFUNC_MAGIC_DEF("PushID", 1, js_imgui_functions, IMGUI_PUSH_ID),
    JS_CFUNC_MAGIC_DEF("PopID", 0, js_imgui_functions, IMGUI_POP_ID),
    JS_CFUNC_MAGIC_DEF("GetID", 1, js_imgui_functions, IMGUI_GET_ID),
    JS_CFUNC_MAGIC_DEF("TextUnformatted", 2, js_imgui_functions, IMGUI_TEXT_UNFORMATTED),
    JS_CFUNC_MAGIC_DEF("Text", 1, js_imgui_functions, IMGUI_TEXT),
    JS_CFUNC_MAGIC_DEF("TextColored", 2, js_imgui_functions, IMGUI_TEXT_COLORED),
    JS_CFUNC_MAGIC_DEF("TextDisabled", 1, js_imgui_functions, IMGUI_TEXT_DISABLED),
    JS_CFUNC_MAGIC_DEF("TextWrapped", 1, js_imgui_functions, IMGUI_TEXT_WRAPPED),
    JS_CFUNC_MAGIC_DEF("LabelText", 2, js_imgui_functions, IMGUI_LABEL_TEXT),
    JS_CFUNC_MAGIC_DEF("BulletText", 1, js_imgui_functions, IMGUI_BULLET_TEXT),
    JS_CFUNC_MAGIC_DEF("Button", 2, js_imgui_functions, IMGUI_BUTTON),
    JS_CFUNC_MAGIC_DEF("SmallButton", 1, js_imgui_functions, IMGUI_SMALL_BUTTON),
    JS_CFUNC_MAGIC_DEF("InvisibleButton", 2, js_imgui_functions, IMGUI_INVISIBLE_BUTTON),
    JS_CFUNC_MAGIC_DEF("ArrowButton", 2, js_imgui_functions, IMGUI_ARROW_BUTTON),
    JS_CFUNC_MAGIC_DEF("Image", 6, js_imgui_functions, IMGUI_IMAGE),
    JS_CFUNC_MAGIC_DEF("ImageButton", 7, js_imgui_functions, IMGUI_IMAGE_BUTTON),
    JS_CFUNC_MAGIC_DEF("Checkbox", 2, js_imgui_functions, IMGUI_CHECKBOX),
    JS_CFUNC_MAGIC_DEF("CheckboxFlags", 3, js_imgui_functions, IMGUI_CHECKBOX_FLAGS),
    JS_CFUNC_MAGIC_DEF("RadioButton", 3, js_imgui_functions, IMGUI_RADIO_BUTTON),
    JS_CFUNC_MAGIC_DEF("ProgressBar", 3, js_imgui_functions, IMGUI_PROGRESS_BAR),
    JS_CFUNC_MAGIC_DEF("Bullet", 0, js_imgui_functions, IMGUI_BULLET),
    JS_CFUNC_MAGIC_DEF("BeginCombo", 3, js_imgui_functions, IMGUI_BEGIN_COMBO),
    JS_CFUNC_MAGIC_DEF("EndCombo", 0, js_imgui_functions, IMGUI_END_COMBO),
    JS_CFUNC_MAGIC_DEF("Combo", 6, js_imgui_functions, IMGUI_COMBO),
    JS_CFUNC_MAGIC_DEF("DragFloat", 7, js_imgui_functions, IMGUI_DRAG_FLOAT),
    JS_CFUNC_MAGIC_DEF("DragFloat2", 7, js_imgui_functions, IMGUI_DRAG_FLOAT2),
    JS_CFUNC_MAGIC_DEF("DragFloat3", 7, js_imgui_functions, IMGUI_DRAG_FLOAT3),
    JS_CFUNC_MAGIC_DEF("DragFloat4", 7, js_imgui_functions, IMGUI_DRAG_FLOAT4),
    JS_CFUNC_MAGIC_DEF("DragFloatRange2", 9, js_imgui_functions, IMGUI_DRAG_FLOAT_RANGE2),
    JS_CFUNC_MAGIC_DEF("DragInt", 6, js_imgui_functions, IMGUI_DRAG_INT),
    JS_CFUNC_MAGIC_DEF("DragInt2", 6, js_imgui_functions, IMGUI_DRAG_INT2),
    JS_CFUNC_MAGIC_DEF("DragInt3", 6, js_imgui_functions, IMGUI_DRAG_INT3),
    JS_CFUNC_MAGIC_DEF("DragInt4", 6, js_imgui_functions, IMGUI_DRAG_INT4),
    JS_CFUNC_MAGIC_DEF("DragIntRange2", 8, js_imgui_functions, IMGUI_DRAG_INT_RANGE2),
    JS_CFUNC_MAGIC_DEF("DragScalar", 8, js_imgui_functions, IMGUI_DRAG_SCALAR),
    JS_CFUNC_MAGIC_DEF("DragScalarN", 9, js_imgui_functions, IMGUI_DRAG_SCALAR_N),
    JS_CFUNC_MAGIC_DEF("SliderFloat", 6, js_imgui_functions, IMGUI_SLIDER_FLOAT),
    JS_CFUNC_MAGIC_DEF("SliderFloat2", 6, js_imgui_functions, IMGUI_SLIDER_FLOAT2),
    JS_CFUNC_MAGIC_DEF("SliderFloat3", 6, js_imgui_functions, IMGUI_SLIDER_FLOAT3),
    JS_CFUNC_MAGIC_DEF("SliderFloat4", 6, js_imgui_functions, IMGUI_SLIDER_FLOAT4),
    JS_CFUNC_MAGIC_DEF("SliderAngle", 5, js_imgui_functions, IMGUI_SLIDER_ANGLE),
    JS_CFUNC_MAGIC_DEF("SliderInt", 5, js_imgui_functions, IMGUI_SLIDER_INT),
    JS_CFUNC_MAGIC_DEF("SliderInt2", 5, js_imgui_functions, IMGUI_SLIDER_INT2),
    JS_CFUNC_MAGIC_DEF("SliderInt3", 5, js_imgui_functions, IMGUI_SLIDER_INT3),
    JS_CFUNC_MAGIC_DEF("SliderInt4", 5, js_imgui_functions, IMGUI_SLIDER_INT4),
    JS_CFUNC_MAGIC_DEF("SliderScalar", 7, js_imgui_functions, IMGUI_SLIDER_SCALAR),
    JS_CFUNC_MAGIC_DEF("SliderScalarN", 8, js_imgui_functions, IMGUI_SLIDER_SCALAR_N),
    JS_CFUNC_MAGIC_DEF("VSliderFloat", 7, js_imgui_functions, IMGUI_V_SLIDER_FLOAT),
    JS_CFUNC_MAGIC_DEF("VSliderInt", 6, js_imgui_functions, IMGUI_V_SLIDER_INT),
    JS_CFUNC_MAGIC_DEF("VSliderScalar", 8, js_imgui_functions, IMGUI_V_SLIDER_SCALAR),
    JS_CFUNC_MAGIC_DEF("InputText", 6, js_imgui_functions, IMGUI_INPUT_TEXT),
    JS_CFUNC_MAGIC_DEF("InputTextMultiline", 7, js_imgui_functions, IMGUI_INPUT_TEXT_MULTILINE),
    JS_CFUNC_MAGIC_DEF("InputTextWithHint", 7, js_imgui_functions, IMGUI_INPUT_TEXT_WITH_HINT),
    JS_CFUNC_MAGIC_DEF("InputFloat", 6, js_imgui_functions, IMGUI_INPUT_FLOAT),
    JS_CFUNC_MAGIC_DEF("InputFloat2", 4, js_imgui_functions, IMGUI_INPUT_FLOAT2),
    JS_CFUNC_MAGIC_DEF("InputFloat3", 4, js_imgui_functions, IMGUI_INPUT_FLOAT3),
    JS_CFUNC_MAGIC_DEF("InputFloat4", 4, js_imgui_functions, IMGUI_INPUT_FLOAT4),
    JS_CFUNC_MAGIC_DEF("InputInt", 5, js_imgui_functions, IMGUI_INPUT_INT),
    JS_CFUNC_MAGIC_DEF("InputInt2", 3, js_imgui_functions, IMGUI_INPUT_INT2),
    JS_CFUNC_MAGIC_DEF("InputInt3", 3, js_imgui_functions, IMGUI_INPUT_INT3),
    JS_CFUNC_MAGIC_DEF("InputInt4", 3, js_imgui_functions, IMGUI_INPUT_INT4),
    JS_CFUNC_MAGIC_DEF("InputDouble", 6, js_imgui_functions, IMGUI_INPUT_DOUBLE),
    JS_CFUNC_MAGIC_DEF("InputScalar", 7, js_imgui_functions, IMGUI_INPUT_SCALAR),
    JS_CFUNC_MAGIC_DEF("InputScalarN", 8, js_imgui_functions, IMGUI_INPUT_SCALAR_N),
    JS_CFUNC_MAGIC_DEF("ColorEdit3", 3, js_imgui_functions, IMGUI_COLOR_EDIT3),
    JS_CFUNC_MAGIC_DEF("ColorEdit4", 3, js_imgui_functions, IMGUI_COLOR_EDIT4),
    JS_CFUNC_MAGIC_DEF("ColorPicker3", 3, js_imgui_functions, IMGUI_COLOR_PICKER3),
    JS_CFUNC_MAGIC_DEF("ColorPicker4", 4, js_imgui_functions, IMGUI_COLOR_PICKER4),
    JS_CFUNC_MAGIC_DEF("ColorButton", 4, js_imgui_functions, IMGUI_COLOR_BUTTON),
    JS_CFUNC_MAGIC_DEF("SetColorEditOptions", 1, js_imgui_functions, IMGUI_SET_COLOR_EDIT_OPTIONS),
    JS_CFUNC_MAGIC_DEF("TreeNode", 2, js_imgui_functions, IMGUI_TREE_NODE),
    JS_CFUNC_MAGIC_DEF("TreeNodeEx", 3, js_imgui_functions, IMGUI_TREE_NODE_EX),
    JS_CFUNC_MAGIC_DEF("TreePush", 1, js_imgui_functions, IMGUI_TREE_PUSH),
    JS_CFUNC_MAGIC_DEF("TreePop", 0, js_imgui_functions, IMGUI_TREE_POP),
    JS_CFUNC_MAGIC_DEF("GetTreeNodeToLabelSpacing", 0, js_imgui_functions, IMGUI_GET_TREE_NODE_TO_LABEL_SPACING),
    JS_CFUNC_MAGIC_DEF("CollapsingHeader", 3, js_imgui_functions, IMGUI_COLLAPSING_HEADER),
    JS_CFUNC_MAGIC_DEF("Selectable", 4, js_imgui_functions, IMGUI_SELECTABLE),
    JS_CFUNC_MAGIC_DEF("ListBox", 6, js_imgui_functions, IMGUI_LIST_BOX),
    JS_CFUNC_MAGIC_DEF("ListBoxHeader", 3, js_imgui_functions, IMGUI_LIST_BOX_HEADER),
    JS_CFUNC_MAGIC_DEF("ListBoxFooter", 0, js_imgui_functions, IMGUI_LIST_BOX_FOOTER),
    JS_CFUNC_MAGIC_DEF("EndListBox", 0, js_imgui_functions, IMGUI_END_LIST_BOX),
    JS_CFUNC_MAGIC_DEF("PlotLines", 9, js_imgui_functions, IMGUI_PLOT_LINES),
    JS_CFUNC_MAGIC_DEF("PlotHistogram", 9, js_imgui_functions, IMGUI_PLOT_HISTOGRAM),
    JS_CFUNC_MAGIC_DEF("Value", 3, js_imgui_functions, IMGUI_VALUE),
    JS_CFUNC_MAGIC_DEF("BeginMainMenuBar", 0, js_imgui_functions, IMGUI_BEGIN_MAIN_MENU_BAR),
    JS_CFUNC_MAGIC_DEF("EndMainMenuBar", 0, js_imgui_functions, IMGUI_END_MAIN_MENU_BAR),
    JS_CFUNC_MAGIC_DEF("BeginMenuBar", 0, js_imgui_functions, IMGUI_BEGIN_MENU_BAR),
    JS_CFUNC_MAGIC_DEF("EndMenuBar", 0, js_imgui_functions, IMGUI_END_MENU_BAR),
    JS_CFUNC_MAGIC_DEF("BeginMenu", 2, js_imgui_functions, IMGUI_BEGIN_MENU),
    JS_CFUNC_MAGIC_DEF("EndMenu", 0, js_imgui_functions, IMGUI_END_MENU),
    JS_CFUNC_MAGIC_DEF("MenuItem", 4, js_imgui_functions, IMGUI_MENU_ITEM),
    JS_CFUNC_MAGIC_DEF("BeginTooltip", 0, js_imgui_functions, IMGUI_BEGIN_TOOLTIP),
    JS_CFUNC_MAGIC_DEF("EndTooltip", 0, js_imgui_functions, IMGUI_END_TOOLTIP),
    JS_CFUNC_MAGIC_DEF("SetTooltip", 1, js_imgui_functions, IMGUI_SET_TOOLTIP),
    JS_CFUNC_MAGIC_DEF("OpenPopup", 1, js_imgui_functions, IMGUI_OPEN_POPUP),
    JS_CFUNC_MAGIC_DEF("BeginPopup", 2, js_imgui_functions, IMGUI_BEGIN_POPUP),
    JS_CFUNC_MAGIC_DEF("BeginPopupContextItem", 2, js_imgui_functions, IMGUI_BEGIN_POPUP_CONTEXT_ITEM),
    JS_CFUNC_MAGIC_DEF("BeginPopupContextWindow", 3, js_imgui_functions, IMGUI_BEGIN_POPUP_CONTEXT_WINDOW),
    JS_CFUNC_MAGIC_DEF("BeginPopupContextVoid", 2, js_imgui_functions, IMGUI_BEGIN_POPUP_CONTEXT_VOID),
    JS_CFUNC_MAGIC_DEF("BeginPopupModal", 3, js_imgui_functions, IMGUI_BEGIN_POPUP_MODAL),
    JS_CFUNC_MAGIC_DEF("EndPopup", 0, js_imgui_functions, IMGUI_END_POPUP),
    JS_CFUNC_MAGIC_DEF("OpenPopupOnItemClick", 2, js_imgui_functions, IMGUI_OPEN_POPUP_ON_ITEM_CLICK),
    JS_CFUNC_MAGIC_DEF("IsPopupOpen", 1, js_imgui_functions, IMGUI_IS_POPUP_OPEN),
    JS_CFUNC_MAGIC_DEF("CloseCurrentPopup", 0, js_imgui_functions, IMGUI_CLOSE_CURRENT_POPUP),
    JS_CFUNC_MAGIC_DEF("Columns", 3, js_imgui_functions, IMGUI_COLUMNS),
    JS_CFUNC_MAGIC_DEF("NextColumn", 0, js_imgui_functions, IMGUI_NEXT_COLUMN),
    JS_CFUNC_MAGIC_DEF("GetColumnIndex", 0, js_imgui_functions, IMGUI_GET_COLUMN_INDEX),
    JS_CFUNC_MAGIC_DEF("GetColumnWidth", 1, js_imgui_functions, IMGUI_GET_COLUMN_WIDTH),
    JS_CFUNC_MAGIC_DEF("SetColumnWidth", 2, js_imgui_functions, IMGUI_SET_COLUMN_WIDTH),
    JS_CFUNC_MAGIC_DEF("GetColumnOffset", 1, js_imgui_functions, IMGUI_GET_COLUMN_OFFSET),
    JS_CFUNC_MAGIC_DEF("SetColumnOffset", 2, js_imgui_functions, IMGUI_SET_COLUMN_OFFSET),
    JS_CFUNC_MAGIC_DEF("GetColumnsCount", 0, js_imgui_functions, IMGUI_GET_COLUMNS_COUNT),
    JS_CFUNC_MAGIC_DEF("BeginTabBar", 2, js_imgui_functions, IMGUI_BEGIN_TAB_BAR),
    JS_CFUNC_MAGIC_DEF("EndTabBar", 0, js_imgui_functions, IMGUI_END_TAB_BAR),
    JS_CFUNC_MAGIC_DEF("BeginTabItem", 3, js_imgui_functions, IMGUI_BEGIN_TAB_ITEM),
    JS_CFUNC_MAGIC_DEF("EndTabItem", 0, js_imgui_functions, IMGUI_END_TAB_ITEM),
    JS_CFUNC_MAGIC_DEF("TabItemButton", 0, js_imgui_functions, IMGUI_TAB_ITEM_BUTTON),
    JS_CFUNC_MAGIC_DEF("SetTabItemClosed", 1, js_imgui_functions, IMGUI_SET_TAB_ITEM_CLOSED),
    JS_CFUNC_MAGIC_DEF("LogToTTY", 1, js_imgui_functions, IMGUI_LOG_TO_TTY),
    JS_CFUNC_MAGIC_DEF("LogToFile", 2, js_imgui_functions, IMGUI_LOG_TO_FILE),
    JS_CFUNC_MAGIC_DEF("LogToClipboard", 1, js_imgui_functions, IMGUI_LOG_TO_CLIPBOARD),
    JS_CFUNC_MAGIC_DEF("LogFinish", 0, js_imgui_functions, IMGUI_LOG_FINISH),
    JS_CFUNC_MAGIC_DEF("LogButtons", 0, js_imgui_functions, IMGUI_LOG_BUTTONS),
    JS_CFUNC_MAGIC_DEF("LogText", 1, js_imgui_functions, IMGUI_LOG_TEXT),
    JS_CFUNC_MAGIC_DEF("BeginDragDropSource", 1, js_imgui_functions, IMGUI_BEGIN_DRAG_DROP_SOURCE),
    JS_CFUNC_MAGIC_DEF("SetDragDropPayload", 4, js_imgui_functions, IMGUI_SET_DRAG_DROP_PAYLOAD),
    JS_CFUNC_MAGIC_DEF("EndDragDropSource", 0, js_imgui_functions, IMGUI_END_DRAG_DROP_SOURCE),
    JS_CFUNC_MAGIC_DEF("BeginDragDropTarget", 0, js_imgui_functions, IMGUI_BEGIN_DRAG_DROP_TARGET),
    JS_CFUNC_MAGIC_DEF("AcceptDragDropPayload", 2, js_imgui_functions, IMGUI_ACCEPT_DRAG_DROP_PAYLOAD),
    JS_CFUNC_MAGIC_DEF("EndDragDropTarget", 0, js_imgui_functions, IMGUI_END_DRAG_DROP_TARGET),
    JS_CFUNC_MAGIC_DEF("GetDragDropPayload", 0, js_imgui_functions, IMGUI_GET_DRAG_DROP_PAYLOAD),
    JS_CFUNC_MAGIC_DEF("PushClipRect", 3, js_imgui_functions, IMGUI_PUSH_CLIP_RECT),
    JS_CFUNC_MAGIC_DEF("PopClipRect", 0, js_imgui_functions, IMGUI_POP_CLIP_RECT),
    JS_CFUNC_MAGIC_DEF("SetItemDefaultFocus", 0, js_imgui_functions, IMGUI_SET_ITEM_DEFAULT_FOCUS),
    JS_CFUNC_MAGIC_DEF("SetKeyboardFocusHere", 1, js_imgui_functions, IMGUI_SET_KEYBOARD_FOCUS_HERE),
    JS_CFUNC_MAGIC_DEF("IsItemHovered", 1, js_imgui_functions, IMGUI_IS_ITEM_HOVERED),
    JS_CFUNC_MAGIC_DEF("IsItemActive", 0, js_imgui_functions, IMGUI_IS_ITEM_ACTIVE),
    JS_CFUNC_MAGIC_DEF("IsItemFocused", 0, js_imgui_functions, IMGUI_IS_ITEM_FOCUSED),
    JS_CFUNC_MAGIC_DEF("IsItemClicked", 1, js_imgui_functions, IMGUI_IS_ITEM_CLICKED),
    JS_CFUNC_MAGIC_DEF("IsItemVisible", 0, js_imgui_functions, IMGUI_IS_ITEM_VISIBLE),
    JS_CFUNC_MAGIC_DEF("IsItemEdited", 0, js_imgui_functions, IMGUI_IS_ITEM_EDITED),
    JS_CFUNC_MAGIC_DEF("IsItemActivated", 0, js_imgui_functions, IMGUI_IS_ITEM_ACTIVATED),
    JS_CFUNC_MAGIC_DEF("IsItemDeactivated", 0, js_imgui_functions, IMGUI_IS_ITEM_DEACTIVATED),
    JS_CFUNC_MAGIC_DEF("IsItemDeactivatedAfterEdit", 0, js_imgui_functions, IMGUI_IS_ITEM_DEACTIVATED_AFTER_EDIT),
    JS_CFUNC_MAGIC_DEF("IsAnyItemHovered", 0, js_imgui_functions, IMGUI_IS_ANY_ITEM_HOVERED),
    JS_CFUNC_MAGIC_DEF("IsAnyItemActive", 0, js_imgui_functions, IMGUI_IS_ANY_ITEM_ACTIVE),
    JS_CFUNC_MAGIC_DEF("IsAnyItemFocused", 0, js_imgui_functions, IMGUI_IS_ANY_ITEM_FOCUSED),
    JS_CFUNC_MAGIC_DEF("GetItemRectMin", 0, js_imgui_functions, IMGUI_GET_ITEM_RECT_MIN),
    JS_CFUNC_MAGIC_DEF("GetItemRectMax", 0, js_imgui_functions, IMGUI_GET_ITEM_RECT_MAX),
    JS_CFUNC_MAGIC_DEF("GetItemRectSize", 0, js_imgui_functions, IMGUI_GET_ITEM_RECT_SIZE),
    JS_CFUNC_MAGIC_DEF("SetItemAllowOverlap", 0, js_imgui_functions, IMGUI_SET_ITEM_ALLOW_OVERLAP),
    JS_CFUNC_MAGIC_DEF("IsRectVisible", 2, js_imgui_functions, IMGUI_IS_RECT_VISIBLE),
    JS_CFUNC_MAGIC_DEF("GetTime", 0, js_imgui_functions, IMGUI_GET_TIME),
    JS_CFUNC_MAGIC_DEF("GetFrameCount", 0, js_imgui_functions, IMGUI_GET_FRAME_COUNT),
    JS_CFUNC_MAGIC_DEF("GetBackgroundDrawList", 0, js_imgui_functions, IMGUI_GET_BACKGROUND_DRAW_LIST),
    JS_CFUNC_MAGIC_DEF("GetForegroundDrawList", 0, js_imgui_functions, IMGUI_GET_FOREGROUND_DRAW_LIST),
    JS_CFUNC_MAGIC_DEF("GetDrawListSharedData", 0, js_imgui_functions, IMGUI_GET_DRAW_LIST_SHARED_DATA),
    JS_CFUNC_MAGIC_DEF("GetStyleColorName", 1, js_imgui_functions, IMGUI_GET_STYLE_COLOR_NAME),
    JS_CFUNC_MAGIC_DEF("SetStateStorage", 1, js_imgui_functions, IMGUI_SET_STATE_STORAGE),
    JS_CFUNC_MAGIC_DEF("GetStateStorage", 0, js_imgui_functions, IMGUI_GET_STATE_STORAGE),
    JS_CFUNC_MAGIC_DEF("CalcTextSize", 4, js_imgui_functions, IMGUI_CALC_TEXT_SIZE),
    JS_CFUNC_MAGIC_DEF("CalcListClipping", 4, js_imgui_functions, IMGUI_CALC_LIST_CLIPPING),
    JS_CFUNC_MAGIC_DEF("BeginChildFrame", 3, js_imgui_functions, IMGUI_BEGIN_CHILD_FRAME),
    JS_CFUNC_MAGIC_DEF("EndChildFrame", 0, js_imgui_functions, IMGUI_END_CHILD_FRAME),
    JS_CFUNC_MAGIC_DEF("ColorConvertU32ToFloat4", 1, js_imgui_functions, IMGUI_COLOR_CONVERTU32_TO_FLOAT4),
    JS_CFUNC_MAGIC_DEF("ColorConvertFloat4ToU32", 1, js_imgui_functions, IMGUI_COLOR_CONVERT_FLOAT4_TOU32),
    JS_CFUNC_MAGIC_DEF("ColorConvertRGBtoHSV", 6, js_imgui_functions, IMGUI_COLOR_CONVERT_RGB_TO_HSV),
    JS_CFUNC_MAGIC_DEF("ColorConvertHSVtoRGB", 6, js_imgui_functions, IMGUI_COLOR_CONVERT_HSV_TO_RGB),
    JS_CFUNC_MAGIC_DEF("GetKeyIndex", 1, js_imgui_functions, IMGUI_GET_KEY_INDEX),
    JS_CFUNC_MAGIC_DEF("IsKeyDown", 1, js_imgui_functions, IMGUI_IS_KEY_DOWN),
    JS_CFUNC_MAGIC_DEF("IsKeyPressed", 2, js_imgui_functions, IMGUI_IS_KEY_PRESSED),
    JS_CFUNC_MAGIC_DEF("IsKeyReleased", 1, js_imgui_functions, IMGUI_IS_KEY_RELEASED),
    JS_CFUNC_MAGIC_DEF("GetKeyPressedAmount", 3, js_imgui_functions, IMGUI_GET_KEY_PRESSED_AMOUNT),
    JS_CFUNC_MAGIC_DEF("IsMouseDown", 1, js_imgui_functions, IMGUI_IS_MOUSE_DOWN),
    JS_CFUNC_MAGIC_DEF("IsAnyMouseDown", 0, js_imgui_functions, IMGUI_IS_ANY_MOUSE_DOWN),
    JS_CFUNC_MAGIC_DEF("IsMouseClicked", 2, js_imgui_functions, IMGUI_IS_MOUSE_CLICKED),
    JS_CFUNC_MAGIC_DEF("IsMouseDoubleClicked", 1, js_imgui_functions, IMGUI_IS_MOUSE_DOUBLE_CLICKED),
    JS_CFUNC_MAGIC_DEF("IsMouseReleased", 1, js_imgui_functions, IMGUI_IS_MOUSE_RELEASED),
    JS_CFUNC_MAGIC_DEF("IsMouseDragging", 2, js_imgui_functions, IMGUI_IS_MOUSE_DRAGGING),
    JS_CFUNC_MAGIC_DEF("IsMouseHoveringRect", 3, js_imgui_functions, IMGUI_IS_MOUSE_HOVERING_RECT),
    JS_CFUNC_MAGIC_DEF("IsMousePosValid", 1, js_imgui_functions, IMGUI_IS_MOUSE_POS_VALID),
    JS_CFUNC_MAGIC_DEF("GetMousePos", 0, js_imgui_functions, IMGUI_GET_MOUSE_POS),
    JS_CFUNC_MAGIC_DEF("GetMousePosOnOpeningCurrentPopup", 0, js_imgui_functions, IMGUI_GET_MOUSE_POS_ON_OPENING_CURRENT_POPUP),
    JS_CFUNC_MAGIC_DEF("GetMouseDragDelta", 2, js_imgui_functions, IMGUI_GET_MOUSE_DRAG_DELTA),
    JS_CFUNC_MAGIC_DEF("ResetMouseDragDelta", 1, js_imgui_functions, IMGUI_RESET_MOUSE_DRAG_DELTA),
    JS_CFUNC_MAGIC_DEF("GetMouseCursor", 0, js_imgui_functions, IMGUI_GET_MOUSE_CURSOR),
    JS_CFUNC_MAGIC_DEF("SetMouseCursor", 1, js_imgui_functions, IMGUI_SET_MOUSE_CURSOR),
    JS_CFUNC_MAGIC_DEF("CaptureKeyboardFromApp", 1, js_imgui_functions, IMGUI_CAPTURE_KEYBOARD_FROM_APP),
    JS_CFUNC_MAGIC_DEF("CaptureMouseFromApp", 1, js_imgui_functions, IMGUI_CAPTURE_MOUSE_FROM_APP),
    JS_CFUNC_MAGIC_DEF("GetClipboardText", 0, js_imgui_functions, IMGUI_GET_CLIPBOARD_TEXT),
    JS_CFUNC_MAGIC_DEF("SetClipboardText", 1, js_imgui_functions, IMGUI_SET_CLIPBOARD_TEXT),
    JS_CFUNC_MAGIC_DEF("LoadIniSettingsFromDisk", 1, js_imgui_functions, IMGUI_LOAD_INI_SETTINGS_FROM_DISK),
    JS_CFUNC_MAGIC_DEF("LoadIniSettingsFromMemory", 2, js_imgui_functions, IMGUI_LOAD_INI_SETTINGS_FROM_MEMORY),
    JS_CFUNC_MAGIC_DEF("SaveIniSettingsToDisk", 1, js_imgui_functions, IMGUI_SAVE_INI_SETTINGS_TO_DISK),
    JS_CFUNC_MAGIC_DEF("SaveIniSettingsToMemory", 1, js_imgui_functions, IMGUI_SAVE_INI_SETTINGS_TO_MEMORY),
    JS_CFUNC_MAGIC_DEF("SetAllocatorFunctions", 3, js_imgui_functions, IMGUI_SET_ALLOCATOR_FUNCTIONS),
    JS_CFUNC_MAGIC_DEF("MemAlloc", 1, js_imgui_functions, IMGUI_MEM_ALLOC),
    JS_CFUNC_MAGIC_DEF("MemFree", 1, js_imgui_functions, IMGUI_MEM_FREE),
    JS_PROP_STRING_DEF("IMGUI_VERSION", IMGUI_VERSION, JS_PROP_ENUMERABLE),
    JS_PROP_INT32_DEF("IMGUI_VERSION_NUM", IMGUI_VERSION_NUM, JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("WindowFlags", js_imgui_window_flags, countof(js_imgui_window_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("InputTextFlags", js_imgui_inputtext_flags, countof(js_imgui_inputtext_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("TreeNodeFlags", js_imgui_treenode_flags, countof(js_imgui_treenode_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("PopupFlags", js_imgui_popup_flags, countof(js_imgui_popup_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("SelectableFlags", js_imgui_selectable_flags, countof(js_imgui_selectable_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("ComboFlags", js_imgui_combo_flags, countof(js_imgui_combo_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("TabBarFlags", js_imgui_tabbar_flags, countof(js_imgui_tabbar_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("TabItemFlags", js_imgui_tabitem_flags, countof(js_imgui_tabitem_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("TableFlags", js_imgui_table_flags, countof(js_imgui_table_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("TableColumnFlags", js_imgui_tablecolumn_flags, countof(js_imgui_tablecolumn_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("TableRowFlags", js_imgui_tablerow_flags, countof(js_imgui_tablerow_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("TableBgTarget", js_imgui_tablebgtarget, countof(js_imgui_tablebgtarget), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("FocusedFlags", js_imgui_focused_flags, countof(js_imgui_focused_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("HoveredFlags", js_imgui_hovered_flags, countof(js_imgui_hovered_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("DragDropFlags", js_imgui_dragdrop_flags, countof(js_imgui_dragdrop_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("DataType", js_imgui_datatype, countof(js_imgui_datatype), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("Dir", js_imgui_dir, countof(js_imgui_dir), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("SortDirection", js_imgui_sortdirection, countof(js_imgui_sortdirection), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("Key", js_imgui_key, countof(js_imgui_key), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("KeyModFlags", js_imgui_keymod_flags, countof(js_imgui_keymod_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("NavInput", js_imgui_navinput, countof(js_imgui_navinput), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("ConfigFlags", js_imgui_config_flags, countof(js_imgui_config_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("BackendFlags", js_imgui_backend_flags, countof(js_imgui_backend_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("Col", js_imgui_col, countof(js_imgui_col), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("StyleVar", js_imgui_stylevar, countof(js_imgui_stylevar), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("ButtonFlags", js_imgui_button_flags, countof(js_imgui_button_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("ColorEditFlags", js_imgui_coloredit_flags, countof(js_imgui_coloredit_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("SliderFlags", js_imgui_slider_flags, countof(js_imgui_slider_flags), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("MouseButton", js_imgui_mousebutton, countof(js_imgui_mousebutton), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("MouseCursor", js_imgui_mousecursor, countof(js_imgui_mousecursor), JS_PROP_ENUMERABLE),
    JS_OBJECT_DEF("Cond", js_imgui_cond, countof(js_imgui_cond), JS_PROP_ENUMERABLE),

};

#include "quickjs-imgui-inputtextcallbackdata.hpp"

extern "C" {

int
js_imgui_init(JSContext* ctx, JSModuleDef* m) {

  JS_NewClassID(&js_imgui_io_class_id);
  JS_NewClass(JS_GetRuntime(ctx), js_imgui_io_class_id, &js_imgui_io_class);

  imgui_io_ctor = JS_NewCFunction2(ctx, js_imgui_io_constructor, "ImGuiIO", 1, JS_CFUNC_constructor, 0);
  imgui_io_proto = JS_NewObject(ctx);

  JS_SetPropertyFunctionList(ctx, imgui_io_proto, js_imgui_io_funcs, countof(js_imgui_io_funcs));
  JS_SetClassProto(ctx, js_imgui_io_class_id, imgui_io_proto);

  JS_NewClassID(&js_imgui_style_class_id);
  JS_NewClass(JS_GetRuntime(ctx), js_imgui_style_class_id, &js_imgui_style_class);

  imgui_style_ctor = JS_NewCFunction2(ctx, js_imgui_style_constructor, "ImGuiStyle", 1, JS_CFUNC_constructor, 0);
  imgui_style_proto = JS_NewObject(ctx);

  JS_SetPropertyFunctionList(ctx, imgui_style_proto, js_imgui_style_funcs, countof(js_imgui_style_funcs));
  JS_SetClassProto(ctx, js_imgui_style_class_id, imgui_style_proto);

  JS_NewClassID(&js_imgui_inputtextcallbackdata_class_id);
  JS_NewClass(JS_GetRuntime(ctx), js_imgui_inputtextcallbackdata_class_id, &js_imgui_inputtextcallbackdata_class);

  imgui_inputtextcallbackdata_ctor = JS_NewCFunction2(ctx, js_imgui_inputtextcallbackdata_constructor, "ImGuiPayload", 1, JS_CFUNC_constructor, 0);
  imgui_inputtextcallbackdata_proto = JS_NewObject(ctx);

  JS_SetPropertyFunctionList(ctx, imgui_inputtextcallbackdata_proto, js_imgui_inputtextcallbackdata_funcs, countof(js_imgui_inputtextcallbackdata_funcs));
  JS_SetClassProto(ctx, js_imgui_inputtextcallbackdata_class_id, imgui_inputtextcallbackdata_proto);

  JS_NewClassID(&js_imgui_payload_class_id);
  JS_NewClass(JS_GetRuntime(ctx), js_imgui_payload_class_id, &js_imgui_payload_class);

  imgui_payload_ctor = JS_NewCFunction2(ctx, js_imgui_payload_constructor, "ImGuiPayload", 1, JS_CFUNC_constructor, 0);
  imgui_payload_proto = JS_NewObject(ctx);

  JS_SetPropertyFunctionList(ctx, imgui_payload_proto, js_imgui_payload_funcs, countof(js_imgui_payload_funcs));
  JS_SetClassProto(ctx, js_imgui_payload_class_id, imgui_payload_proto);

  JS_NewClassID(&js_imfont_class_id);
  JS_NewClass(JS_GetRuntime(ctx), js_imfont_class_id, &js_imfont_class);

  imfont_ctor = JS_NewCFunction2(ctx, js_imfont_constructor, "ImFont", 1, JS_CFUNC_constructor, 0);
  imfont_proto = JS_NewObject(ctx);

  JS_SetPropertyFunctionList(ctx, imfont_proto, js_imfont_funcs, countof(js_imfont_funcs));
  JS_SetClassProto(ctx, js_imfont_class_id, imfont_proto);

  JS_NewClassID(&js_imfontatlas_class_id);
  JS_NewClass(JS_GetRuntime(ctx), js_imfontatlas_class_id, &js_imfontatlas_class);

  imfontatlas_ctor = JS_NewCFunction2(ctx, js_imfontatlas_constructor, "ImFontAtlas", 1, JS_CFUNC_constructor, 0);
  imfontatlas_proto = JS_NewObject(ctx);

  JS_SetPropertyFunctionList(ctx, imfontatlas_proto, js_imfontatlas_funcs, countof(js_imfontatlas_funcs));
  JS_SetClassProto(ctx, js_imfontatlas_class_id, imfontatlas_proto);

  if(m) {
    JS_SetModuleExport(ctx, m, "ImGuiIO", imgui_io_ctor);
    JS_SetModuleExport(ctx, m, "ImGuiStyle", imgui_style_ctor);
    JS_SetModuleExport(ctx, m, "ImGuiInputTextCallbackData", imgui_inputtextcallbackdata_ctor);
    JS_SetModuleExport(ctx, m, "ImGuiPayload", imgui_payload_ctor);
    JS_SetModuleExport(ctx, m, "ImFont", imfont_ctor);
    JS_SetModuleExport(ctx, m, "ImFontAtlas", imfontatlas_ctor);
    JS_SetModuleExportList(ctx, m, js_imgui_static_funcs, countof(js_imgui_static_funcs));
  }

  return 0;
}

VISIBLE JSModuleDef*
js_init_module(JSContext* ctx, const char* module_name) {
  JSModuleDef* m;
  if(!(m = JS_NewCModule(ctx, module_name, &js_imgui_init)))
    return m;
  JS_AddModuleExport(ctx, m, "ImGuiIO");
  JS_AddModuleExport(ctx, m, "ImGuiStyle");
  JS_AddModuleExport(ctx, m, "ImGuiInputTextCallbackData");
  JS_AddModuleExport(ctx, m, "ImGuiPayload");
  JS_AddModuleExport(ctx, m, "ImFont");
  JS_AddModuleExport(ctx, m, "ImFontAtlas");
  JS_AddModuleExportList(ctx, m, js_imgui_static_funcs, countof(js_imgui_static_funcs));
  return m;
}
}
