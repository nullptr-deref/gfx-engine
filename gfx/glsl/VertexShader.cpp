#include "include/VertexShader.hpp"

namespace glsl {
    VertexShader::VertexShader(const ShaderSource &src)
        : Shader(ShaderType::Vertex) {
        this->create();
        this->setSource(src);
        this->compile();
    }

    VertexShader::~VertexShader() {
        this->del();
    }

} // namespace glsl
