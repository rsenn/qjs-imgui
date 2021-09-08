#ifndef QUICKJS_IMGUI_H
#define QUICKJS_IMGUI_H

struct imgui;

#include <quickjs.h>
#include <cutils.h>

#if defined(_WIN32) || defined(__MINGW32__)
#define VISIBLE __declspec(dllexport)
#define HIDDEN
#else
#define VISIBLE __attribute__((visibility("default")))
#define HIDDEN __attribute__((visibility("hidden")))
#endif

JSModuleDef* js_init_module_imgui(JSContext*, const char* module_name);

#endif /* defined(QUICKJS_IMGUI_H) */
