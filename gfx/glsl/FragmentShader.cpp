#include "include/FragmentShader.hpp"

namespace glsl {
    FragmentShader::FragmentShader(const ShaderSource &src)
        : Shader(ShaderType::Fragment) {
        this->create();
        this->setSource(src);
        this->compile();
    }

    FragmentShader::~FragmentShader() {
        this->del();
    }

} // namespace glsl
