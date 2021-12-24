#pragma once

#include "Shader.hpp"

namespace glsl {
    class VertexShader : public Shader {
    public:
        VertexShader(const ShaderSource &src);
        ~VertexShader();
    };
}
