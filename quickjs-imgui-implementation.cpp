

#ifdef USE_GLEW
#include <GL/glew.h>
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#elif defined(USE_GL3W)
#include <GL/glcorearb.h>
#include <GL/gl3w.h>
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#else
#endif

#include <GLFW/glfw3.h>

#undef IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include "imgui/backends/imgui_impl_glfw.cpp"
#include "imgui/backends/imgui_impl_opengl2.cpp"
#include "imgui/backends/imgui_impl_opengl3.cpp"
