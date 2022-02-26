# Find GLFW library and include paths for CMU462 This defines the following:
#
# GLFW_FOUND             If GLFW is found GLFW_LIBRARY           GLFW libraries
# GLFW_INCLUDE_DIR GLFW include directories GLFW_LIBRARY_DIR       GLFW library
# directories
macro(find_glfw)
  if(UNIX)
    set(GLFW_INC_NAMES glfw3.h glfw.h)
    set(GLFW_LIB_NAMES libglfw.so libglfw.a)
    if(APPLE)
      set(GLFW_LIB_NAMES libglfw_osx.a)
    endif(APPLE)
  endif(UNIX)

  # GLFW static library
  find_library(GLFW_LIBRARY NAMES ${GLFW_LIB_NAMES} DOC "GLFW library" CMAKE_FIND_ROOT_PATH_BOTH)

  if(NOT GLFW_LIBRARY)
    include(FindPkgConfig)

    pkg_search_module(GLFW glfw3)
  endif(NOT GLFW_LIBRARY)

  # GLFW library dir
  if(NOT GLFW_LIBRARY_DIR)
    if(GLFW_LIBRARY)
      get_filename_component(GLFW_LIBRARY_DIR "${GLFW_LIBRARY}" DIRECTORY)
    else(GLFW_LIBRARY)
      find_path(GLFW_LIBRARY_DIR NAMES ${GLFW_LIB_NAMES}
                DOC "GLFW library directory")
    endif(GLFW_LIBRARY)
  endif(NOT GLFW_LIBRARY_DIR)

  # GLFW include dir
  if(NOT GLFW_INCLUDE_DIR)
    if(GLFW_LIBRARY_DIR)
      string(REGEX REPLACE "/lib/?.*" "/include" GLFW_INCLUDE_DIR
                           "${GLFW_LIBRARY_DIR}")
    else(GLFW_LIBRARY_DIR)
      find_path(GLFW_INCLUDE_DIR NAMES ${GLFW_INC_NAMES}
                DOC "GLFW include directory")
    endif(GLFW_LIBRARY_DIR)
  endif(NOT GLFW_INCLUDE_DIR)

  # Version
  set(GLFW_VERSION 3.1.1)

  set(GLFW_LIBRARY "${GLFW_LIBRARY}" CACHE FILEPATH "GLFW library")
  set(GLFW_LIBRARY_DIR "${GLFW_LIBRARY_DIR}" CACHE FILEPATH "GLFW library directory")
  set(GLFW_INCLUDE_DIR "${GLFW_INCLUDE_DIR}" CACHE FILEPATH "GLFW include directory")

  if(NOT GLFW_CONFIGURATION_SHOWN)
    message(STATUS "GLFW library: ${GLFW_LIBRARY}")
    message(STATUS "GLFW library directory: ${GLFW_LIBRARY_DIR}")
    message(STATUS "GLFW include directory: ${GLFW_INCLUDE_DIR}")
    set(GLFW_CONFIGURATION_SHOWN TRUE)
  endif(NOT GLFW_CONFIGURATION_SHOWN)

  # Set package standard args include(FindPackageHandleStandardArgs)
  # FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW REQUIRED_VARS GLFW_LIBRARY
  # GLFW_INCLUDE_DIR GLFW_LIBRARY_DIR VERSION_VAR GLFW_VERSION)
endmacro(find_glfw)
