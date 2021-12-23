#include "include/gfx.hpp"

namespace gl {
    void enable(gl::Capability cap) {
        glEnable(static_cast<GLenum>(cap));
    }
}
