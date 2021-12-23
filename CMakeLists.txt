cmake_minimum_required (VERSION 3.10)

project("GameEngine")

add_subdirectory("gfx")

add_executable(app "main.cpp")
set_target_properties( "app"
    PROPERTIES
        CXX_STANDARD_REQUIRED TRUE
        CXX_STANDARD 20
)

set(CMAKE_BUILD_TYPE "Debug")
set(GLFW_DIR
    "C:/Program Files/glfw"
    CACHE STRING
    "Path to glfw root dir"
)
set(GLEW_DIR
    "C:/Program Files/glew"
    CACHE STRING
    "Path to glew root dir"
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

set(GLEW_LIB "${GLEW_DIR}/lib/glew32.lib")

if(${OPENGL_FOUND})
    target_link_libraries(app PRIVATE
        "gfx"
        glfw
        # ${OPENGL_LIBRARIES} this method also works if placed instead of OpenGL::GL
        OpenGL::GL
        ${GLEW_LIB}
    )
    target_include_directories(app PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_DIR}/include
    )
endif()
if(WIN32)
    message(STATUS "Copying glfw3.dll into executable folder...")
    file(COPY "${GLFW_DIR}/bin/glfw3.dll" DESTINATION "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/")
    file(COPY "${GLEW_DIR}/bin/glew32.dll" DESTINATION "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/")
endif()