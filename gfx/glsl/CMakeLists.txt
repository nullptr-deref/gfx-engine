cmake_minimum_required(VERSION 3.1)

project(glsl)

set(GLSL_SOURCES
    "Program.cpp"
    "Shader.cpp"
    "ShaderSource.cpp"
    "VertexShader.cpp"
)
add_library(glsl STATIC ${GLSL_SOURCES})
target_include_directories(glsl PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_DIR}/include
)
target_link_libraries(glsl PRIVATE
    ${GLEW_LIB}
)
set_target_properties(glsl
    PROPERTIES
    CXX_STANDARD_REQUIRED TRUE
    CXX_STANDARD 20
)
