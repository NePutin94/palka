
IF(NOT GLEW_ROOT_DIR AND NOT $ENV{GLEW_ROOT_DIR} STREQUAL "")
  SET(GLEW_ROOT_DIR $ENV{GLEW_ROOT_DIR})
ENDIF()

SET(_glew_SEARCH_DIRS
        ${GLEW_ROOT_DIR}
        )

FIND_PATH(GLEW_INCLUDE_DIR
        NAMES
        glew.h
        HINTS
        ${_glew_SEARCH_DIRS}
        PATH_SUFFIXES
        include/GL include GL
        )

FIND_LIBRARY(GLEW_LIBRARY
        NAMES
        glew32
        HINTS
        ${_glew_SEARCH_DIRS}
        PATH_SUFFIXES
        lib64 lib
        )

# handle the QUIETLY and REQUIRED arguments and set SDL2_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW DEFAULT_MSG
        GLEW_LIBRARY GLEW_INCLUDE_DIR)

IF(GLEW_FOUND)
  SET(GLEW_LIBRARIES ${GLEW_LIBRARY})
  SET(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
ENDIF()

MARK_AS_ADVANCED(
        GLEW_INCLUDE_DIR
        GLEW_LIBRARY
)