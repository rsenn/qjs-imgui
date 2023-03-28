#ifndef QUICKJS_IMGUI_HPP
#define QUICKJS_IMGUI_HPP

#include <string>
#include <iostream>
#include <array>

struct imgui;

#include <quickjs.h>

extern "C" {
#include <cutils.h>
}

#if defined(_WIN32) || defined(__MINGW32__)
#define VISIBLE __declspec(dllexport)
#define HIDDEN
#else
#define VISIBLE __attribute__((visibility("default")))
#define HIDDEN __attribute__((visibility("hidden")))
#endif

#if defined(_Thread_local) || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201102L))
#define thread_local _Thread_local
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__SUNPRO_CC) || defined(__IBMCPP__)
#define thread_local __thread
#elif defined(_WIN32)
#define thread_local __declspec(thread)
#else
#error No TLS implementation found.
#endif

extern "C" JSModuleDef* js_init_module_imgui(JSContext*, const char* module_name);

template<typename T> struct JSVal {
  static T to(JSContext* ctx, JSValueConst jsval);
  static JSValue from(JSContext* ctx, T v);
};

template<> struct JSVal<std::string> {
  static std::string
  to(JSContext* ctx, JSValueConst jsval) {
    const char* s;
    size_t n;
    std::string ret;

    if((s = JS_ToCStringLen(ctx, &n, jsval))) {
      ret = std::move(std::string(s, n));
      JS_FreeCString(ctx, s);
    }
    return ret;
  }

  static JSValue
  from(JSContext* ctx, const std::string& s) {
    return JS_NewStringLen(ctx, s.c_str(), s.length());
  }
};

template<> struct JSVal<const char*> {
  static JSValue
  from(JSContext* ctx, const char* s) {
    return JS_NewString(ctx, s);
  }
  static JSValue
  from(JSContext* ctx, const char* s, size_t len) {
    return JS_NewStringLen(ctx, s, len);
  }
};

template<> struct JSVal<double> {
  static double
  to(JSContext* ctx, JSValueConst jsval) {
    double r;
    JS_ToFloat64(ctx, &r, jsval);
    return r;
  }

  static JSValue
  from(JSContext* ctx, double v) {
    return JS_NewFloat64(ctx, v);
  }
};

template<> struct JSVal<float> {
  static float
  to(JSContext* ctx, JSValueConst jsval) {
    return JSVal<double>::to(ctx, jsval);
  }

  static JSValue
  from(JSContext* ctx, float v) {
    return JSVal<double>::from(ctx, v);
  }
};

template<> struct JSVal<int64_t> {
  static int64_t
  to(JSContext* ctx, JSValueConst jsval) {
    int64_t r;
    JS_ToInt64(ctx, &r, jsval);
    return r;
  }

  static JSValue
  from(JSContext* ctx, int64_t v) {
    return JS_NewInt64(ctx, v);
  }
};

template<> struct JSVal<int32_t> {
  static int32_t
  to(JSContext* ctx, JSValueConst jsval) {
    int32_t r;
    JS_ToInt32(ctx, &r, jsval);
    return r;
  }

  static JSValue
  from(JSContext* ctx, int32_t v) {
    return JS_NewInt32(ctx, v);
  }
};

template<> struct JSVal<uint32_t> {
  static uint32_t
  to(JSContext* ctx, JSValueConst jsval) {
    uint32_t r;
    JS_ToUint32(ctx, &r, jsval);
    return r;
  }

  static JSValue
  from(JSContext* ctx, uint32_t v) {
    return JS_NewUint32(ctx, v);
  }
};

template<> struct JSVal<bool> {
  static bool
  to(JSContext* ctx, JSValueConst jsval) {
    return JS_ToBool(ctx, jsval);
  }

  static JSValue
  from(JSContext* ctx, bool v) {
    return JS_NewBool(ctx, v);
  }
};

template<typename T, size_t N> struct JSVal<std::array<T, N>> {
  static std::array<T, N>
  to(JSContext* ctx, JSValueConst jsval) {
    std::array<T, N> ret;
    for(size_t i = 0; i < N; ++i) {
      JSValue prop = JS_GetPropertyUint32(ctx, ret, i);
      ret[i] = JSVal<T>::to(ctx, jsval);
      JS_FreeValue(ctx, prop);
    }
    return ret;
  }

  static JSValue
  from(JSContext* ctx, std::array<float, N> v) {
    JSValue ret = JS_NewArray(ctx);
    for(size_t i = 0; i < N; ++i) JS_SetPropertyUint32(ctx, ret, i, JSVal<T>::from(ctx, v[i]));
    return ret;
  }
};

class JSRef {
public:
  JSValueConst param;

  JSRef(JSValueConst output) : param(output) {}

  JSValue
  get(JSContext* ctx) {
    JSValue ret = JS_UNDEFINED;
    if(JS_IsFunction(ctx, param)) {
      ret = JS_Call(ctx, param, JS_UNDEFINED, 0, 0);
    } else if(JS_IsObject(param)) {
      ret = JS_GetPropertyUint32(ctx, param, 0);
    }
    return ret;
  }

  void
  set(JSContext* ctx, JSValueConst value) {
    if(JS_IsFunction(ctx, param)) {
      JSValue ret;
      ret = JS_Call(ctx, param, JS_UNDEFINED, 1, &value);
      JS_FreeValue(ctx, ret);
    } else if(JS_IsObject(param) /*JS_IsArray(ctx, param)*/) {
      JS_SetPropertyUint32(ctx, param, 0, JS_DupValue(ctx, value));
    }
  }
};

template<typename T> class OutputArg {
public:
  bool is_null;
  T initially, value;
  JSRef param;
  JSContext* ctx;

  OutputArg(JSContext* _ctx, JSValueConst _arg) : param(_arg), ctx(_ctx) {
    is_null = JS_IsNull(_arg) || JS_IsUndefined(_arg);

    if(!is_null) {
      JSValue tmp = param.get(ctx);
      value = initially = JSVal<T>::to(ctx, tmp);
      JS_FreeValue(ctx, tmp);
    }
  }

  ~OutputArg() {
    if(!is_null) {
      JSValue tmp = JSVal<T>::from(ctx, value);

      if(value != initially)
        std::cerr << "value (" << value << ") != initially (" << initially << ")" << std::endl;

      param.set(ctx, tmp);
      JS_FreeValue(ctx, tmp);
    }
  }

  operator T*() { return is_null ? nullptr : &value; }
};

#endif /* defined(QUICKJS_IMGUI_HPP) */
