#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <imgui.h>
#include "quickjs-imgui.hpp"

#define max(a, b) ((a) > (b) ? (a) : (b))

enum {
  IMGUI_CREATE_CONTEXT,
  IMGUI_DESTROY_CONTEXT,
  IMGUI_GET_CURRENT_CONTEXT,
  IMGUI_SET_CURRENT_CONTEXT,
  IMGUI_DEBUG_CHECK_VERSION_AND_DATA_LAYOUT,
  IMGUI_GET_IO,
  IMGUI_GET_STYLE,
  IMGUI_NEW_FRAME,
  IMGUI_END_FRAME,
  IMGUI_RENDER,
  IMGUI_GET_DRAW_DATA,
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
  IMGUI_GET_CONTENT_REGION_AVAIL_WIDTH,
  IMGUI_GET_WINDOW_CONTENT_REGION_MIN,
  IMGUI_GET_WINDOW_CONTENT_REGION_MAX,
  IMGUI_GET_WINDOW_CONTENT_REGION_WIDTH,
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
  IMGUI_SET_SCROLL_HERE_Y,
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
  IMGUI_TEXT_V,
  IMGUI_TEXT_COLORED,
  IMGUI_TEXT_COLORED_V,
  IMGUI_TEXT_DISABLED,
  IMGUI_TEXT_DISABLED_V,
  IMGUI_TEXT_WRAPPED,
  IMGUI_TEXT_WRAPPED_V,
  IMGUI_LABEL_TEXT,
  IMGUI_LABEL_TEXT_V,
  IMGUI_BULLET_TEXT,
  IMGUI_BULLET_TEXT_V,
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
  IMGUI_TREE_NODE_V,
  IMGUI_TREE_NODE_EX,
  IMGUI_TREE_NODE_EX_V,
  IMGUI_TREE_PUSH,
  IMGUI_TREE_POP,
  IMGUI_TREE_ADVANCE_TO_LABEL_POS,
  IMGUI_GET_TREE_NODE_TO_LABEL_SPACING,
  IMGUI_SET_NEXT_TREE_NODE_OPEN,
  IMGUI_COLLAPSING_HEADER,
  IMGUI_SELECTABLE,
  IMGUI_LIST_BOX,
  IMGUI_LIST_BOX_HEADER,
  IMGUI_LIST_BOX_FOOTER,
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
  IMGUI_SET_TOOLTIP_V,
  IMGUI_OPEN_POPUP,
  IMGUI_BEGIN_POPUP,
  IMGUI_BEGIN_POPUP_CONTEXT_ITEM,
  IMGUI_BEGIN_POPUP_CONTEXT_WINDOW,
  IMGUI_BEGIN_POPUP_CONTEXT_VOID,
  IMGUI_BEGIN_POPUP_MODAL,
  IMGUI_END_POPUP,
  IMGUI_OPEN_POPUP_ON_ITEM_CLICK,
  IMGUI_IS_POPUP_OPEN,
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
  IMGUI_COLOR_CONVERTRG_BTO_HSV,
  IMGUI_COLOR_CONVERTHS_VTO_RGB,
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

static JSValue
js_imgui_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  JSValue ret = JS_UNDEFINED;

  switch(magic) {
    case IMGUI_CREATE_CONTEXT: break;
    case IMGUI_DESTROY_CONTEXT: break;
    case IMGUI_GET_CURRENT_CONTEXT: break;
    case IMGUI_SET_CURRENT_CONTEXT: break;
    case IMGUI_DEBUG_CHECK_VERSION_AND_DATA_LAYOUT: break;
    case IMGUI_GET_IO: break;
    case IMGUI_GET_STYLE: break;
    case IMGUI_NEW_FRAME: break;
    case IMGUI_END_FRAME: break;
    case IMGUI_RENDER: break;
    case IMGUI_GET_DRAW_DATA: break;
    case IMGUI_SHOW_DEMO_WINDOW: break;
    case IMGUI_SHOW_ABOUT_WINDOW: break;
    case IMGUI_SHOW_METRICS_WINDOW: break;
    case IMGUI_SHOW_STYLE_EDITOR: break;
    case IMGUI_SHOW_STYLE_SELECTOR: break;
    case IMGUI_SHOW_FONT_SELECTOR: break;
    case IMGUI_SHOW_USER_GUIDE: break;
    case IMGUI_GET_VERSION: break;
    case IMGUI_STYLE_COLORS_DARK: break;
    case IMGUI_STYLE_COLORS_CLASSIC: break;
    case IMGUI_STYLE_COLORS_LIGHT: break;
    case IMGUI_BEGIN: break;
    case IMGUI_END: break;
    case IMGUI_BEGIN_CHILD: break;
    case IMGUI_END_CHILD: break;
    case IMGUI_IS_WINDOW_APPEARING: break;
    case IMGUI_IS_WINDOW_COLLAPSED: break;
    case IMGUI_IS_WINDOW_FOCUSED: break;
    case IMGUI_IS_WINDOW_HOVERED: break;
    case IMGUI_GET_WINDOW_DRAW_LIST: break;
    case IMGUI_GET_WINDOW_POS: break;
    case IMGUI_GET_WINDOW_SIZE: break;
    case IMGUI_GET_WINDOW_WIDTH: break;
    case IMGUI_GET_WINDOW_HEIGHT: break;
    case IMGUI_GET_CONTENT_REGION_MAX: break;
    case IMGUI_GET_CONTENT_REGION_AVAIL: break;
    case IMGUI_GET_CONTENT_REGION_AVAIL_WIDTH: break;
    case IMGUI_GET_WINDOW_CONTENT_REGION_MIN: break;
    case IMGUI_GET_WINDOW_CONTENT_REGION_MAX: break;
    case IMGUI_GET_WINDOW_CONTENT_REGION_WIDTH: break;
    case IMGUI_SET_NEXT_WINDOW_POS: break;
    case IMGUI_SET_NEXT_WINDOW_SIZE: break;
    case IMGUI_SET_NEXT_WINDOW_SIZE_CONSTRAINTS: break;
    case IMGUI_SET_NEXT_WINDOW_CONTENT_SIZE: break;
    case IMGUI_SET_NEXT_WINDOW_COLLAPSED: break;
    case IMGUI_SET_NEXT_WINDOW_FOCUS: break;
    case IMGUI_SET_NEXT_WINDOW_BG_ALPHA: break;
    case IMGUI_SET_WINDOW_POS: break;
    case IMGUI_SET_WINDOW_SIZE: break;
    case IMGUI_SET_WINDOW_COLLAPSED: break;
    case IMGUI_SET_WINDOW_FOCUS: break;
    case IMGUI_SET_WINDOW_FONT_SCALE: break;
    case IMGUI_GET_SCROLL_X: break;
    case IMGUI_GET_SCROLL_Y: break;
    case IMGUI_GET_SCROLL_MAX_X: break;
    case IMGUI_GET_SCROLL_MAX_Y: break;
    case IMGUI_SET_SCROLL_X: break;
    case IMGUI_SET_SCROLL_Y: break;
    case IMGUI_SET_SCROLL_HERE_Y: break;
    case IMGUI_SET_SCROLL_FROM_POS_Y: break;
    case IMGUI_PUSH_FONT: break;
    case IMGUI_POP_FONT: break;
    case IMGUI_PUSH_STYLE_COLOR: break;
    case IMGUI_POP_STYLE_COLOR: break;
    case IMGUI_PUSH_STYLE_VAR: break;
    case IMGUI_POP_STYLE_VAR: break;
    case IMGUI_GET_STYLE_COLOR_VEC4: break;
    case IMGUI_GET_FONT: break;
    case IMGUI_GET_FONT_SIZE: break;
    case IMGUI_GET_FONT_TEX_UV_WHITE_PIXEL: break;
    case IMGUI_GET_COLORU32: break;
    case IMGUI_PUSH_ITEM_WIDTH: break;
    case IMGUI_POP_ITEM_WIDTH: break;
    case IMGUI_CALC_ITEM_WIDTH: break;
    case IMGUI_PUSH_TEXT_WRAP_POS: break;
    case IMGUI_POP_TEXT_WRAP_POS: break;
    case IMGUI_PUSH_ALLOW_KEYBOARD_FOCUS: break;
    case IMGUI_POP_ALLOW_KEYBOARD_FOCUS: break;
    case IMGUI_PUSH_BUTTON_REPEAT: break;
    case IMGUI_POP_BUTTON_REPEAT: break;
    case IMGUI_SEPARATOR: break;
    case IMGUI_SAME_LINE: break;
    case IMGUI_NEW_LINE: break;
    case IMGUI_SPACING: break;
    case IMGUI_DUMMY: break;
    case IMGUI_INDENT: break;
    case IMGUI_UNINDENT: break;
    case IMGUI_BEGIN_GROUP: break;
    case IMGUI_END_GROUP: break;
    case IMGUI_GET_CURSOR_POS: break;
    case IMGUI_GET_CURSOR_POS_X: break;
    case IMGUI_GET_CURSOR_POS_Y: break;
    case IMGUI_SET_CURSOR_POS: break;
    case IMGUI_SET_CURSOR_POS_X: break;
    case IMGUI_SET_CURSOR_POS_Y: break;
    case IMGUI_GET_CURSOR_START_POS: break;
    case IMGUI_GET_CURSOR_SCREEN_POS: break;
    case IMGUI_SET_CURSOR_SCREEN_POS: break;
    case IMGUI_ALIGN_TEXT_TO_FRAME_PADDING: break;
    case IMGUI_GET_TEXT_LINE_HEIGHT: break;
    case IMGUI_GET_TEXT_LINE_HEIGHT_WITH_SPACING: break;
    case IMGUI_GET_FRAME_HEIGHT: break;
    case IMGUI_GET_FRAME_HEIGHT_WITH_SPACING: break;
    case IMGUI_PUSH_ID: break;
    case IMGUI_POP_ID: break;
    case IMGUI_GET_ID: break;
    case IMGUI_TEXT_UNFORMATTED: break;
    case IMGUI_TEXT: break;
    case IMGUI_TEXT_V: break;
    case IMGUI_TEXT_COLORED: break;
    case IMGUI_TEXT_COLORED_V: break;
    case IMGUI_TEXT_DISABLED: break;
    case IMGUI_TEXT_DISABLED_V: break;
    case IMGUI_TEXT_WRAPPED: break;
    case IMGUI_TEXT_WRAPPED_V: break;
    case IMGUI_LABEL_TEXT: break;
    case IMGUI_LABEL_TEXT_V: break;
    case IMGUI_BULLET_TEXT: break;
    case IMGUI_BULLET_TEXT_V: break;
    case IMGUI_BUTTON: break;
    case IMGUI_SMALL_BUTTON: break;
    case IMGUI_INVISIBLE_BUTTON: break;
    case IMGUI_ARROW_BUTTON: break;
    case IMGUI_IMAGE: break;
    case IMGUI_IMAGE_BUTTON: break;
    case IMGUI_CHECKBOX: break;
    case IMGUI_CHECKBOX_FLAGS: break;
    case IMGUI_RADIO_BUTTON: break;
    case IMGUI_PROGRESS_BAR: break;
    case IMGUI_BULLET: break;
    case IMGUI_BEGIN_COMBO: break;
    case IMGUI_END_COMBO: break;
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
    case IMGUI_SET_COLOR_EDIT_OPTIONS: break;
    case IMGUI_TREE_NODE: break;
    case IMGUI_TREE_NODE_V: break;
    case IMGUI_TREE_NODE_EX: break;
    case IMGUI_TREE_NODE_EX_V: break;
    case IMGUI_TREE_PUSH: break;
    case IMGUI_TREE_POP: break;
    case IMGUI_TREE_ADVANCE_TO_LABEL_POS: break;
    case IMGUI_GET_TREE_NODE_TO_LABEL_SPACING: break;
    case IMGUI_SET_NEXT_TREE_NODE_OPEN: break;
    case IMGUI_COLLAPSING_HEADER: break;
    case IMGUI_SELECTABLE: break;
    case IMGUI_LIST_BOX: break;
    case IMGUI_LIST_BOX_HEADER: break;
    case IMGUI_LIST_BOX_FOOTER: break;
    case IMGUI_PLOT_LINES: break;
    case IMGUI_PLOT_HISTOGRAM: break;
    case IMGUI_VALUE: break;
    case IMGUI_BEGIN_MAIN_MENU_BAR: break;
    case IMGUI_END_MAIN_MENU_BAR: break;
    case IMGUI_BEGIN_MENU_BAR: break;
    case IMGUI_END_MENU_BAR: break;
    case IMGUI_BEGIN_MENU: break;
    case IMGUI_END_MENU: break;
    case IMGUI_MENU_ITEM: break;
    case IMGUI_BEGIN_TOOLTIP: break;
    case IMGUI_END_TOOLTIP: break;
    case IMGUI_SET_TOOLTIP: break;
    case IMGUI_SET_TOOLTIP_V: break;
    case IMGUI_OPEN_POPUP: break;
    case IMGUI_BEGIN_POPUP: break;
    case IMGUI_BEGIN_POPUP_CONTEXT_ITEM: break;
    case IMGUI_BEGIN_POPUP_CONTEXT_WINDOW: break;
    case IMGUI_BEGIN_POPUP_CONTEXT_VOID: break;
    case IMGUI_BEGIN_POPUP_MODAL: break;
    case IMGUI_END_POPUP: break;
    case IMGUI_OPEN_POPUP_ON_ITEM_CLICK: break;
    case IMGUI_IS_POPUP_OPEN: break;
    case IMGUI_CLOSE_CURRENT_POPUP: break;
    case IMGUI_COLUMNS: break;
    case IMGUI_NEXT_COLUMN: break;
    case IMGUI_GET_COLUMN_INDEX: break;
    case IMGUI_GET_COLUMN_WIDTH: break;
    case IMGUI_SET_COLUMN_WIDTH: break;
    case IMGUI_GET_COLUMN_OFFSET: break;
    case IMGUI_SET_COLUMN_OFFSET: break;
    case IMGUI_GET_COLUMNS_COUNT: break;
    case IMGUI_BEGIN_TAB_BAR: break;
    case IMGUI_END_TAB_BAR: break;
    case IMGUI_BEGIN_TAB_ITEM: break;
    case IMGUI_END_TAB_ITEM: break;
    case IMGUI_SET_TAB_ITEM_CLOSED: break;
    case IMGUI_LOG_TO_TTY: break;
    case IMGUI_LOG_TO_FILE: break;
    case IMGUI_LOG_TO_CLIPBOARD: break;
    case IMGUI_LOG_FINISH: break;
    case IMGUI_LOG_BUTTONS: break;
    case IMGUI_LOG_TEXT: break;
    case IMGUI_BEGIN_DRAG_DROP_SOURCE: break;
    case IMGUI_SET_DRAG_DROP_PAYLOAD: break;
    case IMGUI_END_DRAG_DROP_SOURCE: break;
    case IMGUI_BEGIN_DRAG_DROP_TARGET: break;
    case IMGUI_ACCEPT_DRAG_DROP_PAYLOAD: break;
    case IMGUI_END_DRAG_DROP_TARGET: break;
    case IMGUI_GET_DRAG_DROP_PAYLOAD: break;
    case IMGUI_PUSH_CLIP_RECT: break;
    case IMGUI_POP_CLIP_RECT: break;
    case IMGUI_SET_ITEM_DEFAULT_FOCUS: break;
    case IMGUI_SET_KEYBOARD_FOCUS_HERE: break;
    case IMGUI_IS_ITEM_HOVERED: break;
    case IMGUI_IS_ITEM_ACTIVE: break;
    case IMGUI_IS_ITEM_FOCUSED: break;
    case IMGUI_IS_ITEM_CLICKED: break;
    case IMGUI_IS_ITEM_VISIBLE: break;
    case IMGUI_IS_ITEM_EDITED: break;
    case IMGUI_IS_ITEM_ACTIVATED: break;
    case IMGUI_IS_ITEM_DEACTIVATED: break;
    case IMGUI_IS_ITEM_DEACTIVATED_AFTER_EDIT: break;
    case IMGUI_IS_ANY_ITEM_HOVERED: break;
    case IMGUI_IS_ANY_ITEM_ACTIVE: break;
    case IMGUI_IS_ANY_ITEM_FOCUSED: break;
    case IMGUI_GET_ITEM_RECT_MIN: break;
    case IMGUI_GET_ITEM_RECT_MAX: break;
    case IMGUI_GET_ITEM_RECT_SIZE: break;
    case IMGUI_SET_ITEM_ALLOW_OVERLAP: break;
    case IMGUI_IS_RECT_VISIBLE: break;
    case IMGUI_GET_TIME: break;
    case IMGUI_GET_FRAME_COUNT: break;
    case IMGUI_GET_BACKGROUND_DRAW_LIST: break;
    case IMGUI_GET_FOREGROUND_DRAW_LIST: break;
    case IMGUI_GET_DRAW_LIST_SHARED_DATA: break;
    case IMGUI_GET_STYLE_COLOR_NAME: break;
    case IMGUI_SET_STATE_STORAGE: break;
    case IMGUI_GET_STATE_STORAGE: break;
    case IMGUI_CALC_TEXT_SIZE: break;
    case IMGUI_CALC_LIST_CLIPPING: break;
    case IMGUI_BEGIN_CHILD_FRAME: break;
    case IMGUI_END_CHILD_FRAME: break;
    case IMGUI_COLOR_CONVERTU32_TO_FLOAT4: break;
    case IMGUI_COLOR_CONVERT_FLOAT4_TOU32: break;
    case IMGUI_COLOR_CONVERTRG_BTO_HSV: break;
    case IMGUI_COLOR_CONVERTHS_VTO_RGB: break;
    case IMGUI_GET_KEY_INDEX: break;
    case IMGUI_IS_KEY_DOWN: break;
    case IMGUI_IS_KEY_PRESSED: break;
    case IMGUI_IS_KEY_RELEASED: break;
    case IMGUI_GET_KEY_PRESSED_AMOUNT: break;
    case IMGUI_IS_MOUSE_DOWN: break;
    case IMGUI_IS_ANY_MOUSE_DOWN: break;
    case IMGUI_IS_MOUSE_CLICKED: break;
    case IMGUI_IS_MOUSE_DOUBLE_CLICKED: break;
    case IMGUI_IS_MOUSE_RELEASED: break;
    case IMGUI_IS_MOUSE_DRAGGING: break;
    case IMGUI_IS_MOUSE_HOVERING_RECT: break;
    case IMGUI_IS_MOUSE_POS_VALID: break;
    case IMGUI_GET_MOUSE_POS: break;
    case IMGUI_GET_MOUSE_POS_ON_OPENING_CURRENT_POPUP: break;
    case IMGUI_GET_MOUSE_DRAG_DELTA: break;
    case IMGUI_RESET_MOUSE_DRAG_DELTA: break;
    case IMGUI_GET_MOUSE_CURSOR: break;
    case IMGUI_SET_MOUSE_CURSOR: break;
    case IMGUI_CAPTURE_KEYBOARD_FROM_APP: break;
    case IMGUI_CAPTURE_MOUSE_FROM_APP: break;
    case IMGUI_GET_CLIPBOARD_TEXT: break;
    case IMGUI_SET_CLIPBOARD_TEXT: break;
    case IMGUI_LOAD_INI_SETTINGS_FROM_DISK: break;
    case IMGUI_LOAD_INI_SETTINGS_FROM_MEMORY: break;
    case IMGUI_SAVE_INI_SETTINGS_TO_DISK: break;
    case IMGUI_SAVE_INI_SETTINGS_TO_MEMORY: break;
    case IMGUI_SET_ALLOCATOR_FUNCTIONS: break;
    case IMGUI_MEM_ALLOC: break;
    case IMGUI_MEM_FREE: break;
  }

  return ret;
}
static const JSCFunctionListEntry js_imgui_static_funcs[] = {
    JS_CFUNC_MAGIC_DEF("CreateContext", 1, js_imgui_functions, IMGUI_CREATE_CONTEXT),
    JS_CFUNC_MAGIC_DEF("DestroyContext", 1, js_imgui_functions, IMGUI_DESTROY_CONTEXT),
    JS_CFUNC_MAGIC_DEF("GetCurrentContext", 0, js_imgui_functions, IMGUI_GET_CURRENT_CONTEXT),
    JS_CFUNC_MAGIC_DEF("SetCurrentContext", 1, js_imgui_functions, IMGUI_SET_CURRENT_CONTEXT),
    JS_CFUNC_MAGIC_DEF("DebugCheckVersionAndDataLayout", 6, js_imgui_functions, IMGUI_DEBUG_CHECK_VERSION_AND_DATA_LAYOUT),
    JS_CFUNC_MAGIC_DEF("GetIO", 0, js_imgui_functions, IMGUI_GET_IO),
    JS_CFUNC_MAGIC_DEF("GetStyle", 0, js_imgui_functions, IMGUI_GET_STYLE),
    JS_CFUNC_MAGIC_DEF("NewFrame", 0, js_imgui_functions, IMGUI_NEW_FRAME),
    JS_CFUNC_MAGIC_DEF("EndFrame", 0, js_imgui_functions, IMGUI_END_FRAME),
    JS_CFUNC_MAGIC_DEF("Render", 0, js_imgui_functions, IMGUI_RENDER),
    JS_CFUNC_MAGIC_DEF("GetDrawData", 0, js_imgui_functions, IMGUI_GET_DRAW_DATA),
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
    JS_CFUNC_MAGIC_DEF("GetContentRegionAvailWidth", 0, js_imgui_functions, IMGUI_GET_CONTENT_REGION_AVAIL_WIDTH),
    JS_CFUNC_MAGIC_DEF("GetWindowContentRegionMin", 0, js_imgui_functions, IMGUI_GET_WINDOW_CONTENT_REGION_MIN),
    JS_CFUNC_MAGIC_DEF("GetWindowContentRegionMax", 0, js_imgui_functions, IMGUI_GET_WINDOW_CONTENT_REGION_MAX),
    JS_CFUNC_MAGIC_DEF("GetWindowContentRegionWidth", 0, js_imgui_functions, IMGUI_GET_WINDOW_CONTENT_REGION_WIDTH),
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
    JS_CFUNC_MAGIC_DEF("TextV", 2, js_imgui_functions, IMGUI_TEXT_V),
    JS_CFUNC_MAGIC_DEF("TextColored", 2, js_imgui_functions, IMGUI_TEXT_COLORED),
    JS_CFUNC_MAGIC_DEF("TextColoredV", 3, js_imgui_functions, IMGUI_TEXT_COLORED_V),
    JS_CFUNC_MAGIC_DEF("TextDisabled", 1, js_imgui_functions, IMGUI_TEXT_DISABLED),
    JS_CFUNC_MAGIC_DEF("TextDisabledV", 2, js_imgui_functions, IMGUI_TEXT_DISABLED_V),
    JS_CFUNC_MAGIC_DEF("TextWrapped", 1, js_imgui_functions, IMGUI_TEXT_WRAPPED),
    JS_CFUNC_MAGIC_DEF("TextWrappedV", 2, js_imgui_functions, IMGUI_TEXT_WRAPPED_V),
    JS_CFUNC_MAGIC_DEF("LabelText", 2, js_imgui_functions, IMGUI_LABEL_TEXT),
    JS_CFUNC_MAGIC_DEF("LabelTextV", 3, js_imgui_functions, IMGUI_LABEL_TEXT_V),
    JS_CFUNC_MAGIC_DEF("BulletText", 1, js_imgui_functions, IMGUI_BULLET_TEXT),
    JS_CFUNC_MAGIC_DEF("BulletTextV", 2, js_imgui_functions, IMGUI_BULLET_TEXT_V),
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
    JS_CFUNC_MAGIC_DEF("TreeNodeV", 3, js_imgui_functions, IMGUI_TREE_NODE_V),
    JS_CFUNC_MAGIC_DEF("TreeNodeEx", 3, js_imgui_functions, IMGUI_TREE_NODE_EX),
    JS_CFUNC_MAGIC_DEF("TreeNodeExV", 4, js_imgui_functions, IMGUI_TREE_NODE_EX_V),
    JS_CFUNC_MAGIC_DEF("TreePush", 1, js_imgui_functions, IMGUI_TREE_PUSH),
    JS_CFUNC_MAGIC_DEF("TreePop", 0, js_imgui_functions, IMGUI_TREE_POP),
    JS_CFUNC_MAGIC_DEF("TreeAdvanceToLabelPos", 0, js_imgui_functions, IMGUI_TREE_ADVANCE_TO_LABEL_POS),
    JS_CFUNC_MAGIC_DEF("GetTreeNodeToLabelSpacing", 0, js_imgui_functions, IMGUI_GET_TREE_NODE_TO_LABEL_SPACING),
    JS_CFUNC_MAGIC_DEF("SetNextTreeNodeOpen", 2, js_imgui_functions, IMGUI_SET_NEXT_TREE_NODE_OPEN),
    JS_CFUNC_MAGIC_DEF("CollapsingHeader", 3, js_imgui_functions, IMGUI_COLLAPSING_HEADER),
    JS_CFUNC_MAGIC_DEF("Selectable", 4, js_imgui_functions, IMGUI_SELECTABLE),
    JS_CFUNC_MAGIC_DEF("ListBox", 6, js_imgui_functions, IMGUI_LIST_BOX),
    JS_CFUNC_MAGIC_DEF("ListBoxHeader", 3, js_imgui_functions, IMGUI_LIST_BOX_HEADER),
    JS_CFUNC_MAGIC_DEF("ListBoxFooter", 0, js_imgui_functions, IMGUI_LIST_BOX_FOOTER),
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
    JS_CFUNC_MAGIC_DEF("SetTooltipV", 2, js_imgui_functions, IMGUI_SET_TOOLTIP_V),
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
    JS_CFUNC_MAGIC_DEF("ColorConvertRGBtoHSV", 6, js_imgui_functions, IMGUI_COLOR_CONVERTRG_BTO_HSV),
    JS_CFUNC_MAGIC_DEF("ColorConvertHSVtoRGB", 6, js_imgui_functions, IMGUI_COLOR_CONVERTHS_VTO_RGB),
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

};

int
js_imgui_init(JSContext* ctx, JSModuleDef* m) {

  if(m) {
    JS_SetModuleExportList(ctx, m, js_imgui_static_funcs, countof(js_imgui_static_funcs));
  }

  return 0;
}

#ifdef JS_SHARED_LIBRARY
#define JS_INIT_MODULE js_init_module
#else
#define JS_INIT_MODULE js_init_module_imgui
#endif

VISIBLE JSModuleDef*
JS_INIT_MODULE(JSContext* ctx, const char* module_name) {
  JSModuleDef* m;
  if(!(m = JS_NewCModule(ctx, module_name, &js_imgui_init)))
    return m;
  JS_AddModuleExportList(ctx, m, js_imgui_static_funcs, countof(js_imgui_static_funcs));
  return m;
}
