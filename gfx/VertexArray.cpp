#include "include/VertexArray.hpp"

#include <iostream>

namespace gl {
    auto VertexArray::gen() -> void {
        glGenVertexArrays(1, &this->id);
    }
    auto VertexArray::del() -> void {
        glDeleteVertexArrays(1, &this->id);
    }
    auto VertexArray::bind() -> void {
        glBindVertexArray(this->id);
    }
    auto VertexArray::unbind() -> void {
        glBindVertexArray(0);
    }
    auto VertexArray::setLabel() -> void { std::clog << "Not implemented.\n"; }
    auto VertexArray::getLabel() -> String { return "Not implemented.\n"; }
}
