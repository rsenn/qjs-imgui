# Find GLEW library and include paths for CMU462 This defines the following:
#
# GLEW_FOUND             If GLEW is found GLEW_LIBRARY           GLEW libraries GLEW_INCLUDE_DIR GLEW include directories GLEW_LIBRARY_DIR       GLEW library directories
macro(find_glew)
  if(UNIX)
    set(GLEW_INC_NAMES glew.h)
    set(GLEW_LIB_NAMES libGLEW.so libGLEW.a)
    if(APPLE)
      set(GLEW_LIB_NAMES libglew_osx.a)
    endif(APPLE)
  endif(UNIX)

  # GLEW static library
  find_library(GLEW_LIBRARY NAMES ${GLEW_LIB_NAMES} DOC "GLEW library" CMAKE_FIND_ROOT_PATH_BOTH)

  if(NOT GLEW_LIBRARY)
    if(NOT PKG_CONFIG_FOUND)
      include(FindPkgConfig)
    endif(NOT PKG_CONFIG_FOUND)

    pkg_search_module(GLEW glew)

    set(GLEW_LIBRARY "${GLEW_LINK_LIBRARIES}")
    set(GLEW_INCLUDE_DIR "${GLEW_INCLUDE_DIRS}")
  endif(NOT GLEW_LIBRARY)

  # GLEW library dir
  if(NOT GLEW_LIBRARY_DIR)
    if(GLEW_LIBRARY)
      get_filename_component(GLEW_LIBRARY_DIR "${GLEW_LIBRARY}" DIRECTORY)
    else(GLEW_LIBRARY)
      find_path(GLEW_LIBRARY_DIR NAMES ${GLEW_LIB_NAMES} DOC "GLEW library directory")
    endif(GLEW_LIBRARY)
  endif(NOT GLEW_LIBRARY_DIR)

  # GLEW include dir
  if(NOT GLEW_INCLUDE_DIR)
    if(GLEW_LIBRARY_DIR)
      string(REGEX REPLACE "/lib/?.*" "/include" GLEW_INCLUDE_DIR "${GLEW_LIBRARY_DIR}")
    else(GLEW_LIBRARY_DIR)
      find_path(GLEW_INCLUDE_DIR NAMES ${GLEW_INC_NAMES} DOC "GLEW include directory")
    endif(GLEW_LIBRARY_DIR)
  endif(NOT GLEW_INCLUDE_DIR)

  # Version
  set(GLEW_VERSION 1.13.0)

  set(GLEW_LIBRARY "${GLEW_LIBRARY}" CACHE FILEPATH "GLEW library")
  set(GLEW_LIBRARY_DIR "${GLEW_LIBRARY_DIR}" CACHE FILEPATH "GLEW library directory")
  set(GLEW_INCLUDE_DIR "${GLEW_INCLUDE_DIR}" CACHE FILEPATH "GLEW include directory")

  if(NOT GLEW_CONFIGURATION_SHOWN)
    message(STATUS "GLEW library: ${GLEW_LIBRARY}")
    message(STATUS "GLEW library directory: ${GLEW_LIBRARY_DIR}")
    message(STATUS "GLEW include directory: ${GLEW_INCLUDE_DIR}")
    set(GLEW_CONFIGURATION_SHOWN TRUE)
  endif(NOT GLEW_CONFIGURATION_SHOWN)

  # Set package standard args include(FindPackageHandleStandardArgs) FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW REQUIRED_VARS GLEW_LIBRARY GLEW_INCLUDE_DIR GLEW_LIBRARY_DIR VERSION_VAR GLEW_VERSION)
endmacro(find_glew)
