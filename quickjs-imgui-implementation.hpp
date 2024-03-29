#ifndef QUICKJS_IMGUI_IMPLEMENTATION_HPP
#define QUICKJS_IMGUI_IMPLEMENTATION_HPP

#include "imgui/backends/imgui_impl_opengl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"

static bool glfw_initialized = false;

static const char*
get_glsl_version(void) {
  // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100
  const char* glsl_version = "#version 100";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
  // GL 3.2 + GLSL 150
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
  return glsl_version;
}

namespace ImGui {
class Exception : public std::exception {
  const char* file;
  int line;
  const char *expr, *func;
  std::string msg;

public:
  Exception(const char* expr_, const char* file_, int line_, const char* func_) : std::exception(), expr(expr_), file(file_), line(line_), func(func_) {
    const char* s;

    if((s = strstr(expr, " && \"")))
      msg = std::string(s + 5, strlen(s + 5) - 1);
    else
      msg = expr;
  }

  const char*
  get_file() const {
    return file;
  }
  int
  get_line() const {
    return line;
  }
  const char*
  get_func() const {
    return func;
  }

  const char*
  what() const throw() {
    return msg.c_str();
  }

  JSValue
  throw_js(JSContext* ctx) const noexcept {
    return JS_ThrowInternalError(ctx, "ImGui::Exception [%s] in %s() at %s:%d", what(), get_func(), get_file(), get_line());
  }
};
} // namespace ImGui

static std::string
imgui_impl_type(const std::string& str) {
  std::string::size_type pos, pos2;

  pos = str.find("Impl");
  const auto start = str.begin() + (pos == std::string::npos ? 0 : pos + 4);

  pos2 = str.find_first_of("0123456789");
  const auto end = pos2 == std::string::npos ? str.end() : str.begin() + pos2;

  return std::string(start, end);
}

enum {
  IMPL_GLFW_CREATE_WINDOW,
  IMPL_GLFW_INIT_FOR_OPEN_GL,
  IMPL_GLFW_INIT_FOR_VULKAN,
  IMPL_GLFW_INIT_FOR_OTHER,
  IMPL_GLFW_SHUTDOWN,
  IMPL_GLFW_NEW_FRAME,
  IMPL_GLFW_WINDOW_FOCUS_CALLBACK,
  IMPL_GLFW_CURSOR_ENTER_CALLBACK,
  IMPL_GLFW_MOUSE_BUTTON_CALLBACK,
  IMPL_GLFW_SCROLL_CALLBACK,
  IMPL_GLFW_KEY_CALLBACK,
  IMPL_GLFW_CHAR_CALLBACK,
  IMPL_GLFW_MONITOR_CALLBACK,
};

static JSValue
js_imgui_impl_glfw_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  JSValue ret = JS_UNDEFINED;
  GLFWwindow* window = 0;
  GLFWmonitor* monitor = 0;

  if(!glfw_initialized) {
    glfwInit();
    glfw_initialized = true;
  }

  switch(magic) {
    case IMPL_GLFW_CREATE_WINDOW:
    case IMPL_GLFW_NEW_FRAME:
    case IMPL_GLFW_SHUTDOWN: break;
    case IMPL_GLFW_MONITOR_CALLBACK: {
      monitor = js_imgui_getobj<GLFWmonitor>(ctx, argv[0]);
      assert(monitor);
      break;
    }
    default: {
      if(!(window = js_imgui_getobj<GLFWwindow>(ctx, argv[0]))) {
        if((magic >= IMPL_GLFW_INIT_FOR_OPEN_GL && magic <= IMPL_GLFW_INIT_FOR_OTHER)) {
          if(JS_IsArray(ctx, argv[0])) {
            ImVec2 vec = js_imgui_getimvec2(ctx, argv[0]);
            const char* str = argc > 1 ? JS_ToCString(ctx, argv[1]) : 0;

            get_glsl_version();

            window = glfwCreateWindow(vec.x, vec.y, str ? str : "ImGui_ImplGlfw", 0, 0);
          }
        }
      }
      assert(window);
      break;
    }
  }

  try {
    switch(magic) {
      case IMPL_GLFW_CREATE_WINDOW: {
        uint32_t w, h;
        const char* str = 0;
        JS_ToUint32(ctx, &w, argv[0]);
        JS_ToUint32(ctx, &h, argv[1]);
        if(argc > 2)
          str = JS_ToCString(ctx, argv[2]);

        get_glsl_version();

        window = glfwCreateWindow(w, h, str ? str : "ImGui_ImplGlfw", 0, 0);

        ret = js_imgui_newptr(ctx, window);

        break;
      }
      case IMPL_GLFW_INIT_FOR_OPEN_GL: {
        ImGui_ImplGlfw_InitForOpenGL(window, argc > 1 ? JS_ToBool(ctx, argv[1]) : true);
        break;
      }
      case IMPL_GLFW_INIT_FOR_VULKAN: {
        ImGui_ImplGlfw_InitForVulkan(window, argc > 1 ? JS_ToBool(ctx, argv[1]) : true);
        break;
      }
      case IMPL_GLFW_INIT_FOR_OTHER: {
        ImGui_ImplGlfw_InitForOther(window, argc > 1 ? JS_ToBool(ctx, argv[1]) : true);
        break;
      }
      case IMPL_GLFW_SHUTDOWN: {
        ImGui_ImplGlfw_Shutdown();
        break;
      }
      case IMPL_GLFW_NEW_FRAME: {
        ImGui_ImplGlfw_NewFrame();
        break;
      }
      case IMPL_GLFW_WINDOW_FOCUS_CALLBACK: {
        int32_t focused;
        JS_ToInt32(ctx, &focused, argv[1]);
        ImGui_ImplGlfw_WindowFocusCallback(window, focused);
        break;
      }
      case IMPL_GLFW_CURSOR_ENTER_CALLBACK: {
        int32_t entered;
        JS_ToInt32(ctx, &entered, argv[1]);
        ImGui_ImplGlfw_CursorEnterCallback(window, entered);
        break;
      }
      case IMPL_GLFW_MOUSE_BUTTON_CALLBACK: {
        int32_t button, action, mods;

        JS_ToInt32(ctx, &button, argv[1]);
        JS_ToInt32(ctx, &action, argv[2]);
        JS_ToInt32(ctx, &mods, argv[3]);

        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
        break;
      }
      case IMPL_GLFW_SCROLL_CALLBACK: {
        double x, y;
        JS_ToFloat64(ctx, &x, argv[1]);
        JS_ToFloat64(ctx, &y, argv[2]);
        ImGui_ImplGlfw_ScrollCallback(window, x, y);
        break;
      }
      case IMPL_GLFW_KEY_CALLBACK: {
        int32_t key, scancode, action, mods;

        JS_ToInt32(ctx, &key, argv[1]);
        JS_ToInt32(ctx, &scancode, argv[2]);
        JS_ToInt32(ctx, &action, argv[3]);
        JS_ToInt32(ctx, &mods, argv[4]);
        ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
        break;
      }
      case IMPL_GLFW_CHAR_CALLBACK: {
        uint32_t c;

        JS_ToUint32(ctx, &c, argv[1]);
        ImGui_ImplGlfw_CharCallback(window, c);
        break;
      }
      case IMPL_GLFW_MONITOR_CALLBACK: {
        int32_t event;
        JS_ToInt32(ctx, &event, argv[1]);
        ImGui_ImplGlfw_MonitorCallback(monitor, event);
        break;
      }
    }
  } catch(const ImGui::Exception& exception) { return exception.throw_js(ctx); }

  return ret;
}

static const JSCFunctionListEntry js_imgui_impl_glfw[] = {
    JS_CFUNC_MAGIC_DEF("CreateWindow", 2, js_imgui_impl_glfw_functions, IMPL_GLFW_CREATE_WINDOW),
    JS_CFUNC_MAGIC_DEF("InitForOpenGL", 2, js_imgui_impl_glfw_functions, IMPL_GLFW_INIT_FOR_OPEN_GL),
    JS_CFUNC_MAGIC_DEF("InitForVulkan", 2, js_imgui_impl_glfw_functions, IMPL_GLFW_INIT_FOR_VULKAN),
    JS_CFUNC_MAGIC_DEF("InitForOther", 2, js_imgui_impl_glfw_functions, IMPL_GLFW_INIT_FOR_OTHER),
    JS_CFUNC_MAGIC_DEF("Shutdown", 0, js_imgui_impl_glfw_functions, IMPL_GLFW_SHUTDOWN),
    JS_CFUNC_MAGIC_DEF("NewFrame", 0, js_imgui_impl_glfw_functions, IMPL_GLFW_NEW_FRAME),
    JS_CFUNC_MAGIC_DEF("WindowFocusCallback", 2, js_imgui_impl_glfw_functions, IMPL_GLFW_WINDOW_FOCUS_CALLBACK),
    JS_CFUNC_MAGIC_DEF("CursorEnterCallback", 2, js_imgui_impl_glfw_functions, IMPL_GLFW_CURSOR_ENTER_CALLBACK),
    JS_CFUNC_MAGIC_DEF("MouseButtonCallback", 4, js_imgui_impl_glfw_functions, IMPL_GLFW_MOUSE_BUTTON_CALLBACK),
    JS_CFUNC_MAGIC_DEF("ScrollCallback", 3, js_imgui_impl_glfw_functions, IMPL_GLFW_SCROLL_CALLBACK),
    JS_CFUNC_MAGIC_DEF("KeyCallback", 5, js_imgui_impl_glfw_functions, IMPL_GLFW_KEY_CALLBACK),
    JS_CFUNC_MAGIC_DEF("CharCallback", 2, js_imgui_impl_glfw_functions, IMPL_GLFW_CHAR_CALLBACK),
    JS_CFUNC_MAGIC_DEF("MonitorCallback", 2, js_imgui_impl_glfw_functions, IMPL_GLFW_MONITOR_CALLBACK),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "ImGui.ImplGlfw", JS_PROP_CONFIGURABLE),
};

enum {
  IMPL_OPENGL_INIT,
  IMPL_OPENGL_SHUTDOWN,
  IMPL_OPENGL_NEW_FRAME,
  IMPL_OPENGL_RENDER_DRAW_DATA,
  IMPL_OPENGL_CREATE_FONTS_TEXTURE,
  IMPL_OPENGL_DESTROY_FONTS_TEXTURE,
  IMPL_OPENGL_CREATE_DEVICE_OBJECTS,
  IMPL_OPENGL_DESTROY_DEVICE_OBJECTS,
};

static JSValue
js_imgui_impl_opengl2_call(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  JSValue ret = JS_UNDEFINED;

  try {
    switch(magic) {
      case IMPL_OPENGL_INIT: ret = JS_NewBool(ctx, ImGui_ImplOpenGL2_Init()); break;
      case IMPL_OPENGL_SHUTDOWN: ImGui_ImplOpenGL2_Shutdown(); break;
      case IMPL_OPENGL_NEW_FRAME: ImGui_ImplOpenGL2_NewFrame(); break;
      case IMPL_OPENGL_RENDER_DRAW_DATA: ImGui_ImplOpenGL2_RenderDrawData(argc > 0 ? js_imgui_getobj<ImDrawData>(ctx, argv[0]) : ImGui::GetDrawData()); break;
      case IMPL_OPENGL_CREATE_FONTS_TEXTURE: ret = JS_NewBool(ctx, ImGui_ImplOpenGL2_CreateFontsTexture()); break;
      case IMPL_OPENGL_DESTROY_FONTS_TEXTURE: ImGui_ImplOpenGL2_DestroyFontsTexture(); break;
      case IMPL_OPENGL_CREATE_DEVICE_OBJECTS: ret = JS_NewBool(ctx, ImGui_ImplOpenGL2_CreateDeviceObjects()); break;
      case IMPL_OPENGL_DESTROY_DEVICE_OBJECTS: ImGui_ImplOpenGL2_DestroyDeviceObjects(); break;
    }
  } catch(const ImGui::Exception& exception) { return exception.throw_js(ctx); }

  return ret;
}

static const JSCFunctionListEntry js_imgui_impl_opengl2[] = {
    JS_CFUNC_MAGIC_DEF("Init", 0, js_imgui_impl_opengl2_call, IMPL_OPENGL_INIT),
    JS_CFUNC_MAGIC_DEF("Shutdown", 0, js_imgui_impl_opengl2_call, IMPL_OPENGL_SHUTDOWN),
    JS_CFUNC_MAGIC_DEF("NewFrame", 0, js_imgui_impl_opengl2_call, IMPL_OPENGL_NEW_FRAME),
    JS_CFUNC_MAGIC_DEF("RenderDrawData", 1, js_imgui_impl_opengl2_call, IMPL_OPENGL_RENDER_DRAW_DATA),
    JS_CFUNC_MAGIC_DEF("CreateFontsTexture", 0, js_imgui_impl_opengl2_call, IMPL_OPENGL_CREATE_FONTS_TEXTURE),
    JS_CFUNC_MAGIC_DEF("DestroyFontsTexture", 0, js_imgui_impl_opengl2_call, IMPL_OPENGL_DESTROY_FONTS_TEXTURE),
    JS_CFUNC_MAGIC_DEF("CreateDeviceObjects", 0, js_imgui_impl_opengl2_call, IMPL_OPENGL_CREATE_DEVICE_OBJECTS),
    JS_CFUNC_MAGIC_DEF("DestroyDeviceObjects", 0, js_imgui_impl_opengl2_call, IMPL_OPENGL_DESTROY_DEVICE_OBJECTS),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "ImGui.ImplOpenGL2", JS_PROP_CONFIGURABLE),
};

static JSValue
js_imgui_impl_opengl3_call(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  JSValue ret = JS_UNDEFINED;

  try {
    switch(magic) {
      case IMPL_OPENGL_INIT: {
        const char* glsl_version = 0;

        for(int i = 0; i < argc; ++i) {
          if(JS_IsString(argv[i]))
            glsl_version = JS_ToCString(ctx, argv[i]);
        }

        ret = JS_NewBool(ctx, ImGui_ImplOpenGL3_Init(glsl_version ? glsl_version : get_glsl_version()));

        if(glsl_version)
          JS_FreeCString(ctx, glsl_version);
        break;
      }
      case IMPL_OPENGL_SHUTDOWN: ImGui_ImplOpenGL3_Shutdown(); break;
      case IMPL_OPENGL_NEW_FRAME: ImGui_ImplOpenGL3_NewFrame(); break;
      case IMPL_OPENGL_RENDER_DRAW_DATA: ImGui_ImplOpenGL3_RenderDrawData(argc > 0 ? js_imgui_getobj<ImDrawData>(ctx, argv[0]) : ImGui::GetDrawData()); break;
      case IMPL_OPENGL_CREATE_FONTS_TEXTURE: ret = JS_NewBool(ctx, ImGui_ImplOpenGL3_CreateFontsTexture()); break;
      case IMPL_OPENGL_DESTROY_FONTS_TEXTURE: ImGui_ImplOpenGL3_DestroyFontsTexture(); break;
      case IMPL_OPENGL_CREATE_DEVICE_OBJECTS: ret = JS_NewBool(ctx, ImGui_ImplOpenGL3_CreateDeviceObjects()); break;
      case IMPL_OPENGL_DESTROY_DEVICE_OBJECTS: ImGui_ImplOpenGL3_DestroyDeviceObjects(); break;
    }
  } catch(const ImGui::Exception& exception) { return exception.throw_js(ctx); }

  return ret;
}

static const JSCFunctionListEntry js_imgui_impl_opengl3[] = {
    JS_CFUNC_MAGIC_DEF("Init", 0, js_imgui_impl_opengl3_call, IMPL_OPENGL_INIT),
    JS_CFUNC_MAGIC_DEF("Shutdown", 0, js_imgui_impl_opengl3_call, IMPL_OPENGL_SHUTDOWN),
    JS_CFUNC_MAGIC_DEF("NewFrame", 0, js_imgui_impl_opengl3_call, IMPL_OPENGL_NEW_FRAME),
    JS_CFUNC_MAGIC_DEF("RenderDrawData", 1, js_imgui_impl_opengl3_call, IMPL_OPENGL_RENDER_DRAW_DATA),
    JS_CFUNC_MAGIC_DEF("CreateFontsTexture", 0, js_imgui_impl_opengl3_call, IMPL_OPENGL_CREATE_FONTS_TEXTURE),
    JS_CFUNC_MAGIC_DEF("DestroyFontsTexture", 0, js_imgui_impl_opengl3_call, IMPL_OPENGL_DESTROY_FONTS_TEXTURE),
    JS_CFUNC_MAGIC_DEF("CreateDeviceObjects", 0, js_imgui_impl_opengl3_call, IMPL_OPENGL_CREATE_DEVICE_OBJECTS),
    JS_CFUNC_MAGIC_DEF("DestroyDeviceObjects", 0, js_imgui_impl_opengl3_call, IMPL_OPENGL_DESTROY_DEVICE_OBJECTS),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "ImGui.ImplOpenGL3", JS_PROP_CONFIGURABLE),
};

#endif // defined(QUICKJS_IMGUI_IMPLEMENTATION_HPP)
