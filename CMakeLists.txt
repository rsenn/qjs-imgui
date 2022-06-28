project(qjs-imgui C CXX)

message("Building project [1;31m${PROJECT_NAME}[0m")

option(USE_GL3W OFF "Use GL3W instead of GLEW")

cmake_minimum_required(VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/UseMultiArch.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/functions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/check-flags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindQuickJS.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/QuickJSModule.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindGLEW.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindGLFW.cmake)
if(USE_GL3W)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildGL3W.cmake)
endif(USE_GL3W)

find_glew()
find_glfw()

if(USE_GL3W)
  build_gl3w()

  add_definitions(-DUSE_GL3W)
endif(USE_GL3W)

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
  ${QUICKJS_INCLUDE_DIR})

link_directories(${QUICKJS_LIBRARY_DIR})

if(USE_GL3W)
  if(NOT TARGET gl3w_gen)
    add_subdirectory(gl3w EXCLUDE_FROM_ALL)
  endif(NOT TARGET gl3w_gen)
endif(USE_GL3W)

set(imgui_LIBRARIES ${GLFW_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_gl_LIBRARY})
#set(imgui_DEPS gl3w)

set(IMGUI_SOURCES
    imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp imgui/imgui_demo.cpp
    imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)

option(IMGUI_DEMO "Build IMGUI demo" ON)

if(IMGUI_DEMO)
  add_executable(imgui_demo imgui/examples/example_glfw_opengl3/main.cpp
                            imgui/imgui_demo.cpp ${IMGUI_SOURCES})
  target_link_libraries(imgui_demo ${imgui_LIBRARIES} ${imgui_DEPS} dl)
endif(IMGUI_DEMO)

make_module(imgui quickjs-imgui.cpp quickjs-imgui.hpp ${IMGUI_SOURCES})
