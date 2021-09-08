project(qjs-imgui C CXX)

cmake_minimum_required(VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/functions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/check-flags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/QuickJSModule.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindQuickJS.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/JSBindings.cmake)

find_quickjs()

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/imgui
  ${CMAKE_CURRENT_BINARY_DIR}/gl3w/include
  ${QUICKJS_INCLUDE_DIR}
)

link_directories(${QUICKJS_LIBRARY_DIR})

add_subdirectory(gl3w)

make_shared_module(
  imgui
  quickjs-imgui.cpp quickjs-imgui.hpp
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp
  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl3.cpp
)
target_link_libraries(quickjs-imgui glfw quickjs)