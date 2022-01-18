#pragma once

#include "Object.hpp"

namespace gl {
    class VertexArray : public Object {
    public:
        VertexArray() = default;
        void gen() override;
        void del() override;
        void bind() override;
        void unbind() override;
        void setLabel() override;
        String getLabel() override;
    };
}
