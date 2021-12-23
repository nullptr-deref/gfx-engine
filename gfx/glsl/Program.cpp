#include "include/Program.hpp"

#include <iostream>

namespace glsl {
    void Program::create() {
        this->id = glCreateProgram();
    }

    void Program::del() {
        glDeleteProgram(this->id);
    }

    void Program::attachShader(const Shader &sh) {
        glAttachShader(this->id, sh.getID());
        linkedShaders_.push_back(sh.getID());
    }
    void Program::detachShader(const Shader &sh) {
        glDetachShader(this->id, sh.getID());
    }
    gl::String Program::getInfoLog() {
        GLsizei actualLen;
        GLint logLen;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &logLen);
        if (0 == logLen) {
            return "No log info provided.\n";
        }
        GLchar *info = new GLchar[logLen];
        glGetProgramInfoLog(this->id, logLen, &actualLen, info);

        const gl::String ret = gl::String(info);
        delete[] info;

        return ret;
    }

    auto Program::link() const -> LinkStatus {
        glLinkProgram(this->id);
        int status;
        glGetProgramiv(this->id, GL_LINK_STATUS, &status);

        return status;
    }

    auto Program::use() const -> void {
        glUseProgram(this->id);
    }

    auto Program::validate() const -> ValidationStatus {
        glValidateProgram(this->id);
        int status;
        glGetProgramiv(this->id, GL_VALIDATE_STATUS, &status);

        return status;
    }
}
