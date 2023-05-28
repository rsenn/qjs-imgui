project(qjs-imgui C CXX)

message("Building project [1;31m${PROJECT_NAME}[0m")

option(BUILD_GLFW OFF "Build GLFW from sources")
option(USE_GL3W OFF "Use GL3W instead of internal loader")
option(USE_GLEW OFF "Use GLEW instead of internal loader")
option(IMPL_OPENGL_ES2 OFF "Use OpenGL ES2")

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD c++20)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/UseMultiArch.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/functions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/check-flags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindQuickJS.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/QuickJSModule.cmake)

if(USE_GL3W)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildGL3W.cmake)
endif(USE_GL3W)

if(USE_GLEW)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindGLEW.cmake)
  find_glew()

  add_definitions(-DUSE_GLEW)
  include_directories(${GLEW_INCLUDE_DIR})
  link_directories(${GLEW_LIBRARY_DIR})
  link_libraries(${GLEW_LIBRARY})
endif(USE_GLEW)

if(BUILD_GLFW)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildGLFW.cmake)

  build_glfw(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

  add_definitions(
    -DHAVE_GLFW_GET_ERROR
    -DHAVE_GLFW_GET_MONITOR_CONTENT_SCALE
    -DHAVE_GLFW_GET_MONITOR_WORKAREA
    -DHAVE_GLFW_GET_WINDOW_OPACITY
    -DHAVE_GLFW_REQUEST_WINDOW_ATTENTION
    -DHAVE_GLFW_SET_WINDOW_CONTENT_SCALE_CALLBACK
    -DHAVE_GLFW_SET_WINDOW_MAXIMIZE_CALLBACK
    -DHAVE_GLFW_SET_WINDOW_OPACITY
    -DHAVE_GLFW_WINDOW_HINT_STRING)
else(BUILD_GLFW)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindGLFW.cmake)
  find_glfw()
endif(BUILD_GLFW)

if(USE_GL3W)
  build_gl3w()

  include_directories(${CMAKE_CURRENT_BINARY_DIR}/gl3w/include)

  add_definitions(-DUSE_GL3W)
endif(USE_GL3W)

if(NOT USE_GLEW AND NOT USE_GL3W)
  if(IMPL_OPENGL_ES2)
    add_definitions(-DIMGUI_IMPL_OPENGL_ES2)
  endif(IMPL_OPENGL_ES2)
endif(NOT USE_GLEW AND NOT USE_GL3W)

#message(STATUS "GLEW_LIBRARY: ${GLEW_LIBRARY}")
#message(STATUS "GLFW_LIBRARY: ${GLFW_LIBRARY}")

find_quickjs()
configure_quickjs()

#find_package(glfw3 3.1 REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui ${CMAKE_CURRENT_BINARY_DIR}/gl3w/include
  ${GLFW_INCLUDE_DIR} ${QUICKJS_INCLUDE_DIR})

link_directories(${QUICKJS_LIBRARY_DIR})

if(USE_GL3W)
  if(NOT TARGET gl3w_gen)
    add_subdirectory(gl3w EXCLUDE_FROM_ALL)
  endif(NOT TARGET gl3w_gen)
endif(USE_GL3W)

set(imgui_LIBRARIES ${GLFW_LIBRARY} ${OPENGL_gl_LIBRARY})
#set(imgui_DEPS gl3w)

set(IMGUI_SOURCES
    imgui/imgui.cpp imgui/imgui.h imgui/imgui_draw.cpp imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp imgui/imgui_demo.cpp)

if(USE_GL3W)
  list(APPEND IMGUI_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/gl3w/src/gl3w.c)
endif(USE_GL3W)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)

option(IMGUI_DEMO "Build IMGUI demo" OFF)

if(IMGUI_DEMO)
  add_executable(
    imgui_demo
    imgui/examples/example_glfw_opengl3/main.cpp imgui/imgui_demo.cpp
    ${IMGUI_SOURCES} imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp)
  target_link_libraries(imgui_demo ${imgui_LIBRARIES} ${imgui_DEPS} pthread dl)
endif(IMGUI_DEMO)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#add_definitions(-DIMGUI_USER_CONFIG=\"quickjs-imconfig.hpp\")

file(GLOB QJS_IMGUI_SOURCES quickjs-imgui.cpp *.hpp ${IMGUI_SOURCES}
     imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_glfw.h
     imgui/backends/imgui_impl_opengl*.cpp imgui/backends/imgui_impl_opengl*.h)

make_module(imgui ${QJS_IMGUI_SOURCES})
