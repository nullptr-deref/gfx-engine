cmake_minimum_required(VERSION 3.10)

project ("gfx")

set(PROJ_HEADERS
    "include/Buffer.hpp"
    "include/Object.hpp"
)
set(PROJ_SOURCES "gfx.cpp" "VertexArray.cpp")

add_library(gfx STATIC ${PROJ_HEADERS} ${PROJ_SOURCES})
set_target_properties( "gfx"
    PROPERTIES
    CXX_STANDARD_REQUIRED TRUE
    CXX_STANDARD 20
)

set(GLEW_DIR
    "C:/Program Files/glew"
    CACHE STRING
    "Path to glew root dir"
)

add_subdirectory("glsl")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

set(GLEW_LIB "${GLEW_DIR}/lib/glew32.lib")

if(${OPENGL_FOUND})
    target_link_libraries(gfx PRIVATE
        glsl
        glfw
        # ${OPENGL_LIBRARIES} this method also works if placed instead of OpenGL::GL
        OpenGL::GL
        ${GLEW_LIB}
    )
target_include_directories(gfx PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_DIR}/include
    )
endif()

if(${glfw3_FOUND})
    message (STATUS "GLFW found.")
endif()