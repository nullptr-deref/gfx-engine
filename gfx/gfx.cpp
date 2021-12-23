#include "include/gfx.hpp"

namespace gl {
    void enable(gl::Capability cap) {
        glEnable(static_cast<GLenum>(cap));
    }
    void blendFunc(BlendFactor srcFactor, BlendFactor destFactor) {
        glBlendFunc(static_cast<GLenum>(srcFactor), static_cast<GLenum>(destFactor));
    }
}
