#pragma once

#include <vector>

#include "GLSLObject.hpp"

#include "Shader.hpp"

namespace glsl {
    using LinkStatus = bool;
    using ValidationStatus = bool;
    class Program : public Object {
    private:
        std::vector<ObjectID> linkedShaders_;
    public:
        void create() override;
        void del() override;
        gl::String getInfoLog() override;
        auto setParameter() -> void;
        auto attachShader(const Shader &sh) -> void;
        auto detachShader(const Shader &sh) -> void;
        auto link() const -> LinkStatus;
        auto validate() const -> ValidationStatus;
        auto use() const -> void;
        auto getID() const -> GLuint {
            return this->id;
        }
    };
}
