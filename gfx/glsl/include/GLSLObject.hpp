#pragma once

#include <string>

#include <GL/glew.h>

namespace gl {
    using String = std::string;
}

namespace glsl {
    using ObjectID = GLuint;
    using ParameterValue = GLint;
    class Object {
    protected:
        ObjectID id;
    public:
        virtual void create() = 0;
        virtual void del() = 0;
        virtual gl::String getInfoLog() = 0;
        virtual ~Object() { }
    };
}
