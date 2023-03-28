#ifndef QUICKJS_IMGUI_HPP
#define QUICKJS_IMGUI_HPP

#include <string>
#include <iostream>
#include <array>
//#include <variant>

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
      JSValue prop = JS_GetPropertyUint32(ctx, jsval, i);
      ret[i] = JSVal<T>::to(ctx, prop);
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

  static void
  from(JSContext* ctx, std::array<float, N> v, JSValueConst arr) {
    for(size_t i = 0; i < N; ++i) JS_SetPropertyUint32(ctx, arr, i, JSVal<T>::from(ctx, v[i]));
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

      /*if(value != initially)
        std::cerr << "value (" << value << ") != initially (" << initially << ")" << std::endl;*/

      param.set(ctx, tmp);
      JS_FreeValue(ctx, tmp);
    }
  }

  operator T*() { return is_null ? nullptr : &value; }
};

template<typename T, size_t N> class OutputArg<std::array<T, N>> {
public:
  bool is_null;
  std::array<T, N> value;
  JSRef param;
  JSContext* ctx;

  OutputArg(JSContext* _ctx, JSValueConst _arg) : param(_arg), ctx(_ctx) {
    is_null = JS_IsNull(_arg) || JS_IsUndefined(_arg);

    if(!is_null) {
      value = JSVal<std::array<T, N>>::to(ctx, _arg);
    }
  }

  ~OutputArg() {
    if(!is_null) {
      JSVal<std::array<T, N>>::from(ctx, value, param.param);
    }
  }

  // operator std::array<T,N>() { return is_null ? nullptr : &value; }
  operator T*() { return is_null ? nullptr : value.data(); }
};

template<enum ImGuiDataType_ type> struct ScalarType {};

template<> struct ScalarType<ImGuiDataType_S8> { typedef int8_t value_type; };
template<> struct ScalarType<ImGuiDataType_U8> { typedef uint8_t value_type; };
template<> struct ScalarType<ImGuiDataType_S16> { typedef int16_t value_type; };
template<> struct ScalarType<ImGuiDataType_U16> { typedef uint16_t value_type; };
template<> struct ScalarType<ImGuiDataType_S32> { typedef int32_t value_type; };
template<> struct ScalarType<ImGuiDataType_U32> { typedef uint32_t value_type; };
template<> struct ScalarType<ImGuiDataType_S64> { typedef int64_t value_type; };
template<> struct ScalarType<ImGuiDataType_U64> { typedef uint64_t value_type; };
template<> struct ScalarType<ImGuiDataType_Float> { typedef float value_type; };
template<> struct ScalarType<ImGuiDataType_Double> { typedef double value_type; };

union ImGuiDataTypeUnion {
  ScalarType<ImGuiDataType_S8>::value_type s8;
  ScalarType<ImGuiDataType_U8>::value_type u8;
  ScalarType<ImGuiDataType_S16>::value_type s16;
  ScalarType<ImGuiDataType_U16>::value_type u16;
  ScalarType<ImGuiDataType_S32>::value_type s32;
  ScalarType<ImGuiDataType_U32>::value_type u32;
  ScalarType<ImGuiDataType_S64>::value_type s64;
  ScalarType<ImGuiDataType_U64>::value_type u64;
  ScalarType<ImGuiDataType_Float>::value_type f32;
  ScalarType<ImGuiDataType_Double>::value_type f64;
};

template<enum ImGuiDataType_ type> void set_scalar(union ImGuiDataTypeUnion& data, typename ScalarType<type>::value_type value);
template<> void set_scalar<ImGuiDataType_S8>(union ImGuiDataTypeUnion& data, ScalarType<ImGuiDataType_S8>::value_type value) { data.s8 = value; }
template<> void set_scalar<ImGuiDataType_U8>(union ImGuiDataTypeUnion& data, ScalarType<ImGuiDataType_U8>::value_type value) { data.u8 = value; }
template<> void set_scalar<ImGuiDataType_S16>(union ImGuiDataTypeUnion& data, ScalarType<ImGuiDataType_S16>::value_type value) { data.s16 = value; }
template<> void set_scalar<ImGuiDataType_U16>(union ImGuiDataTypeUnion& data, ScalarType<ImGuiDataType_U16>::value_type value) { data.u16 = value; }
template<> void set_scalar<ImGuiDataType_S32>(union ImGuiDataTypeUnion& data, ScalarType<ImGuiDataType_S32>::value_type value) { data.s32 = value; }
template<> void set_scalar<ImGuiDataType_U32>(union ImGuiDataTypeUnion& data, ScalarType<ImGuiDataType_U32>::value_type value) { data.u32 = value; }
template<> void set_scalar<ImGuiDataType_S64>(union ImGuiDataTypeUnion& data, ScalarType<ImGuiDataType_S64>::value_type value) { data.s64 = value; }
template<> void set_scalar<ImGuiDataType_U64>(union ImGuiDataTypeUnion& data, ScalarType<ImGuiDataType_U64>::value_type value) { data.u64 = value; }
template<> void set_scalar<ImGuiDataType_Float>(union ImGuiDataTypeUnion& data, ScalarType<ImGuiDataType_Float>::value_type value) { data.f32 = value; }
template<> void set_scalar<ImGuiDataType_Double>(union ImGuiDataTypeUnion& data, ScalarType<ImGuiDataType_Double>::value_type value) { data.f64 = value; }
template<enum ImGuiDataType_ type> typename ScalarType<type>::value_type get_scalar(union ImGuiDataTypeUnion const& data);
template<> ScalarType<ImGuiDataType_S8>::value_type get_scalar<ImGuiDataType_S8>(union ImGuiDataTypeUnion const& data) { return data.s8; }
template<> ScalarType<ImGuiDataType_U8>::value_type get_scalar<ImGuiDataType_U8>(union ImGuiDataTypeUnion const& data) { return data.u8; }
template<> ScalarType<ImGuiDataType_S16>::value_type get_scalar<ImGuiDataType_S16>(union ImGuiDataTypeUnion const& data) { return data.s16; }
template<> ScalarType<ImGuiDataType_U16>::value_type get_scalar<ImGuiDataType_U16>(union ImGuiDataTypeUnion const& data) { return data.u16; }
template<> ScalarType<ImGuiDataType_S32>::value_type get_scalar<ImGuiDataType_S32>(union ImGuiDataTypeUnion const& data) { return data.s32; }
template<> ScalarType<ImGuiDataType_U32>::value_type get_scalar<ImGuiDataType_U32>(union ImGuiDataTypeUnion const& data) { return data.u32; }
template<> ScalarType<ImGuiDataType_S64>::value_type get_scalar<ImGuiDataType_S64>(union ImGuiDataTypeUnion const& data) { return data.s64; }
template<> ScalarType<ImGuiDataType_U64>::value_type get_scalar<ImGuiDataType_U64>(union ImGuiDataTypeUnion const& data) { return data.u64; }
template<> ScalarType<ImGuiDataType_Float>::value_type get_scalar<ImGuiDataType_Float>(union ImGuiDataTypeUnion const& data) { return data.f32; }
template<> ScalarType<ImGuiDataType_Double>::value_type get_scalar<ImGuiDataType_Double>(union ImGuiDataTypeUnion const& data) { return data.f64; }


// typedef std::variant<int64_t, uint64_t, float, double> ImGuiDataTypeVariant;

#endif /* defined(QUICKJS_IMGUI_HPP) */
