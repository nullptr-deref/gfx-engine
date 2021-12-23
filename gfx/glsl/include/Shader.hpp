#pragma once

#include "GLSLObject.hpp"
#include "ShaderSource.hpp"

namespace glsl {
    enum class ShaderType : GLenum {
        Vertex = GL_VERTEX_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEvaluation = GL_TESS_EVALUATION_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Compute = GL_COMPUTE_SHADER
    };
    using CompileStatus = bool;

    class Program;
    class Shader : public Object {
    public:
        friend class Program;
    private:
        ShaderType type_;
        auto getID() const -> ObjectID;
    public:
        Shader(ShaderType type) : type_(type) {}
        void create() override;
        void del() override;
        gl::String getInfoLog() override;
        auto setSource(const ShaderSource &src) -> void;
        auto compile() -> CompileStatus;
    };

    auto createShaderInstantly(ShaderType type, ShaderSource src) -> Shader;
}
