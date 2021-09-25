IF(NOT GLEW_ROOT_DIR AND NOT $ENV{GLEW_ROOT_DIR} STREQUAL "")
    SET(GLEW_ROOT_DIR $ENV{GLEW_ROOT_DIR})
ENDIF()

SET(_glm_SEARCH_DIRS
        ${GLM_ROOT_DIR}
        )

FIND_PATH(GLM_INCLUDE_DIR
        NAMES
        vec2.hpp
        HINTS
        ${_glm_SEARCH_DIRS}
        PATH_SUFFIXES
        include/glm include glm
        )

FIND_LIBRARY(GLM_LIBRARY
        NAMES
        glm_shared
        HINTS
        ${_glm_SEARCH_DIRS}
        PATH_SUFFIXES
        lib64 lib
        )

# handle the QUIETLY and REQUIRED arguments and set SDL2_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLM DEFAULT_MSG
        GLM_LIBRARY GLM_INCLUDE_DIR)

IF(GLM_FOUND)
    SET(GLM_LIBRARIES ${GLM_LIBRARY})
    SET(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
ENDIF()

MARK_AS_ADVANCED(
        GLM_INCLUDE_DIR
        GLM_LIBRARY
)