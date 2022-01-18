#include "include/VertexShader.hpp"

#include <iostream>

namespace glsl {
    VertexShader::VertexShader(const ShaderSource &src)
        : Shader(ShaderType::Vertex) {
        this->create();
        this->setSource(src);
        const CompileStatus compiled = this->compile();
        if (!compiled) {
            std::cerr << this->getInfoLog();
        }
    }

    VertexShader::~VertexShader() {
        this->del();
    }

} // namespace glsl
