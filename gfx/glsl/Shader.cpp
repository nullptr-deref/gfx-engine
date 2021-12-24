#include "include/Shader.hpp"

#include <iostream>
#include <fstream>

namespace glsl {
    auto Shader::create() -> void {
        this->id = glCreateShader(static_cast<GLenum>(type_));
    }
    auto Shader::del() -> void {
        glDeleteShader(this->id);
    }
    auto Shader::getInfoLog() -> gl::String {
        GLsizei actualLen;
        GLint logLen;
        glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &logLen);
        if (0 == logLen) {
            return "No log info provided.\n";
        }
        GLchar *info = new GLchar[logLen];
        glGetShaderInfoLog(this->id, logLen, &actualLen, info);

        const gl::String ret = gl::String(info);
        delete[] info;

        return ret;
    }
    auto Shader::setSource(const ShaderSource &src) const -> void {
        const char *rawSrc = src.c_string();
        glShaderSource(this->id, 1, &rawSrc, nullptr);
    }
    auto Shader::compile() -> CompileStatus {
        glCompileShader(this->id);
        GLint compStatus;
        glGetShaderiv(this->id, GL_COMPILE_STATUS, &compStatus);
        this->compiled_ = static_cast<CompileStatus>(compStatus);

        return this->compiled_;
    }
    auto Shader::compiled() const -> CompileStatus {
        return this->compiled_;
    }

    auto Shader::getID() const -> ObjectID {
        return this->id;
    }

    auto createShaderInstantly(ShaderType type, ShaderSource src) -> Shader {
        Shader shader(type);
        shader.create();
        shader.setSource(src);
        if (!shader.compile()) {
            std::cerr << "Shader was not compiled. Terminating process...\nError log:\n";
            std::cerr << shader.getInfoLog() << '\n';
            std::exit(-1);
        }

        return shader;
    }
} //namespace glsl
