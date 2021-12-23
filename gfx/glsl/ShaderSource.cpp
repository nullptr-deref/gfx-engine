#include "include/ShaderSource.hpp"

#include <fstream>
#include <sstream>

namespace glsl {
    auto ShaderSource::parseFromFile(const gl::String &filepath) -> ShaderSource {
        std::ifstream inp(filepath);
        gl::String buf;
        std::stringstream ss;

        while(std::getline(inp, buf))
            ss << buf << '\n';

        return ShaderSource(ss.str());
    }
    auto ShaderSource::c_string() const -> const char * {
        return raw_.c_str();
    }
}
