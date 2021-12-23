#pragma once

#include <string>

namespace gl {
    using String = std::string;
}

namespace glsl {
    class ShaderSource {
    private:
        gl::String raw_;
    public:
        ShaderSource() = delete;
        ShaderSource(const gl::String &raw) : raw_(raw) {}
        static auto parseFromFile(const gl::String &filepath) -> ShaderSource;
        auto c_string() const -> const char *;
    };
}
