#ifndef QUICKJS_IMGUI_H
#define QUICKJS_IMGUI_H

struct imgui;

#include <quickjs.h>
#include <cutils.h>

struct imgui* js_imgui_data(JSContext*, JSValue value);
struct imgui_entry* js_imguientry_data(JSContext*, JSValue value);
int js_imgui_init(JSContext*, JSModuleDef* m);
JSModuleDef* js_init_module_imgui(JSContext*, const char* module_name);

#endif /* defined(QUICKJS_IMGUI_H) */
