#pragma once

#include "Shader.hpp"

namespace glsl {
    class FragmentShader : public Shader {
    public:
        FragmentShader(const ShaderSource &src);
        ~FragmentShader();
    };
}
