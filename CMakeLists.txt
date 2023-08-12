cmake_minimum_required (VERSION 3.10)

project("GameEngine")

add_subdirectory("gfx")

add_library(engine STATIC
    "engine.hpp"
    "WavefrontGeometry.cpp"
)
set_target_properties("engine"
    PROPERTIES
        CXX_STANDARD_REQUIRED TRUE
        CXX_STANDARD 20
)

set(CMAKE_BUILD_TYPE "Debug")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW 2.2.0 REQUIRED)

if(${OpenGL_FOUND})
    target_link_libraries("engine" PRIVATE
        "gfx"
        glfw
        # ${OPENGL_LIBRARIES} this method also works if placed instead of OpenGL::GL
        OpenGL::GL
        GLEW::GLEW
)
endif()
# if(WIN32)
#     message(STATUS "Copying glfw3.dll into executable folder...")
#     file(COPY "${GLFW_DIR}/bin/glfw3.dll" DESTINATION "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/")
#     file(COPY "${GLEW_DIR}/bin/glew32.dll" DESTINATION "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/")
# endif()
