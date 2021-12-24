#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gfx/include/gfx.hpp"

int main() {
    if (!glfwInit()) {
        std::cerr << "Cannot initialize glfw.\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *wnd = glfwCreateWindow(640, 480, "App Test Window", nullptr, nullptr);
    if (!wnd) {
        glfwTerminate();
        std::cerr << "Cannot create window.\n";
        return -1;
    }
    glfwSwapInterval(1);
    glfwMakeContextCurrent(wnd);
    if (glewInit() != GLEW_OK) {
        std::cerr << "Could not load glew.\n";
        return -1;
    }

    gl::Buffer<gl::TargetBuffer::Array> vbo;
    vbo.gen();
    float vert[9] = {
        -0.5, -0.5, 0.0,
         0.5, -0.5, 0.0,
         0.0,  0.5, 0.0
    };
    vbo.bind();
    vbo.data(9*sizeof(float), vert, gl::BufferUsage::StaticDraw);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, true, 3*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Shaders
        gl::enable(gl::Capability::Blend);
        gl::blendFunc(gl::BlendFactor::SrcAlpha, gl::BlendFactor::OneMinusSrcAlpha);
        const std::string vertfp = std::string("C:/dev/GameEngine/GameEngine/resources/VertexDefault.shader");
        glsl::VertexShader vertex(glsl::ShaderSource::parseFromFile(vertfp));

        const std::string fragfp = std::string("C:/dev/GameEngine/GameEngine/resources/FragmentDefault.shader");
        glsl::FragmentShader fragment(glsl::ShaderSource::parseFromFile(fragfp));

        glsl::Program p;
        p.create();
        p.attachShader(vertex);
        p.attachShader(fragment);
        const bool linked = p.link();
        p.detachShader(vertex);
        p.detachShader(fragment);
        if (!linked) {
            std::clog << "Program did not link.\n";
            std::clog << p.getInfoLog() << '\n';
            std::exit(-1);
        }
    // Shaders end
    /*
        if (!(vCompiled && fragCompiled)) {
            std::cout << "Shaders did not compile.\n";
            std::cout << vertex.getInfoLog() << '\n';
            std::cout << frag.getInfoLog() << '\n';
            std::exit(-1);
        }
        else { */
            p.use();
            std::cout << "Loaded default shaders.\n";
//        }

    while (!glfwWindowShouldClose(wnd)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }

    glfwDestroyWindow(wnd);
    glfwTerminate();
    return 0;
}
