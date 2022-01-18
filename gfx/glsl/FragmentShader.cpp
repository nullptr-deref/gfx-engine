#include "include/FragmentShader.hpp"

#include <iostream>

namespace glsl {
    FragmentShader::FragmentShader(const ShaderSource &src)
        : Shader(ShaderType::Fragment) {
        this->create();
        this->setSource(src);
        const CompileStatus compiled = this->compile();
        if (!compiled) {
            std::cerr << this->getInfoLog();
        }
    }

    FragmentShader::~FragmentShader() {
        this->del();
    }

} // namespace glsl
