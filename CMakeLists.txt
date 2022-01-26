project(qjs-imgui C CXX)

cmake_minimum_required(VERSION 3.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/UseMultiArch.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/functions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/check-flags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindQuickJS.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/QuickJSModule.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindGLEW.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindGLFW.cmake)

find_glew()
find_glfw()

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

add_subdirectory(gl3w EXCLUDE_FROM_ALL)

set(imgui_LIBRARIES ${GLFW_LIBRARY} ${GLEW_LIBRARY})
set(imgui_DEPS gl3w)
make_module(
  imgui
  quickjs-imgui.cpp
  quickjs-imgui.hpp
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_demo.cpp
  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl3.cpp)
#make_shared_module(imgui quickjs-imgui.cpp quickjs-imgui.hpp imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui_demo.cpp imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp)

#target_link_libraries(qjs-imgui ${GLFW_LIBRARY} ${QUICKJS_LIBRARY})
#add_dependencies(qjs-imgui gl3w)

#if(NOT CMAKE_INSTALL_LIBDIR)
#  set(CMAKE_INSTALL_LIBDIR lib)
#endif(NOT CMAKE_INSTALL_LIBDIR)
#if(NOT QUICKJS_C_MODULE_DIR)
#  set(QUICKJS_C_MODULE_DIR "${CMAKE_INSTALL_LIBDIR}/quickjs")
#endif(NOT QUICKJS_C_MODULE_DIR)

#install(TARGETS qjs-imgui DESTINATION "${QUICKJS_C_MODULE_DIR}" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
