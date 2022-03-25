macro(build_gl3w)
  message("-- Building libgl3w from source")

  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gl3w")

    if(NOT TARGET gl3w_gen)
      add_subdirectory(gl3w)
    endif(NOT TARGET gl3w_gen)

  else(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gl3w")

    include(ExternalProject)

    ExternalProject_Add(
      libgl3w
      SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gl3w
      BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/gl3w
      GIT_REPOSITORY https://github.com/skaslev/gl3w.git
      PATCH_COMMAND patch -p1 -f -N -i ${CMAKE_CURRENT_SOURCE_DIR}/gl3w-cmake.patch || true
      INSTALL_COMMAND true
      PREFIX gl3w
      CMAKE_ARGS -DBUILD_SHARED_LIBS:BOOL=OFF "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}" "-DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=${CMAKE_POSITION_INDEPENDENT_CODE}" "-DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}"
                 "-DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS} ${MODULE_COMPILE_FLAGS}" -DGL3W_BUILD_DOCS:BOOL=OFF -DGL3W_BUILD_EXAMPLES:BOOL=OFF -DGL3W_BUILD_TESTS:BOOL=ON
      CMAKE_GENERATOR ${CMAKE_GENERATOR}
      CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
      # INSTALL_COMMAND ""
      USES_TERMINAL_DOWNLOAD ON
      LOG_CONFIGURE ON
      USES_TERMINAL_BUILD ON)

    ExternalProject_Get_Property(libgl3w SOURCE_DIR BINARY_DIR)

    add_library(gl3w-static STATIC IMPORTED GLOBAL)
    add_dependencies(gl3w-static libgl3w)

    if(MSVC)
      set_target_properties(gl3w-static PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/gl3w.lib)
    else()
      set_target_properties(gl3w-static PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/libgl3w.a)
    endif()

    get_target_property(GL3W_LIBRARY_FILE gl3w-static IMPORTED_LOCATION)
    # dump(GL3W_LIBRARY_FILE)

    set(GL3W_INCLUDE_DIR "${BINARY_DIR}/include" CACHE PATH "libgl3w include directory" FORCE)
    set(GL3W_LIBRARY_DIR "${BINARY_DIR}" CACHE PATH "libgl3w library directory" FORCE)
    set(GL3W_LIBRARY gl3w-static CACHE STRING "libgl3w library" FORCE)

    link_directories(${GL3W_LIBRARY_DIR})
  endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gl3w")

endmacro(build_gl3w)
