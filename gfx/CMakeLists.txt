cmake_minimum_required(VERSION 3.10)

project ("gfx")

set(PROJ_HEADERS
    "include/Buffer.hpp"
    "include/Object.hpp"
)
set(PROJ_SOURCES "gfx.cpp" "VertexArray.cpp")

add_library(gfx STATIC ${PROJ_HEADERS} ${PROJ_SOURCES})
set_target_properties("gfx"
    PROPERTIES
    CXX_STANDARD_REQUIRED TRUE
    CXX_STANDARD 20
)

add_subdirectory("glsl")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW 2.2.0 REQUIRED)

if(${OPENGL_FOUND})
    target_link_libraries(gfx PRIVATE
        glsl
        glfw
        # ${OPENGL_LIBRARIES} this method also works if placed instead of OpenGL::GL
        OpenGL::GL
        GLEW::GLEW
    )
endif()