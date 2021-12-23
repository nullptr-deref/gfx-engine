#pragma once

#include <GL/glew.h>

#include "Object.hpp"
#include "Buffer.hpp"

#include "../glsl/include/Program.hpp"
#include "../glsl/include/Shader.hpp"

namespace gl {
    enum class Capability : GLenum {
        Blend = GL_BLEND,
        // ClipDistance = GL_CLIP_DISTANCE,
        ColorLogicOp = GL_COLOR_LOGIC_OP,
        CullFace = GL_CULL_FACE,
        DebugOutput = GL_DEBUG_OUTPUT,
        DebugOutputSync = GL_DEBUG_OUTPUT_SYNCHRONOUS,
        DepthClamp = GL_DEPTH_CLAMP,
        DepthTest = GL_DEPTH_TEST,
        Dither = GL_DITHER,
        FramebufferSRGB = GL_FRAMEBUFFER_SRGB,
        LineSmooth = GL_LINE_SMOOTH,
        Multisample = GL_MULTISAMPLE,
        PolygonOffsetFill = GL_POLYGON_OFFSET_FILL,
        PolygonOffsetLine = GL_POLYGON_OFFSET_LINE,
        PolygonOffsetPoint = GL_POLYGON_OFFSET_POINT,
        PolygonSmooth = GL_POLYGON_SMOOTH,
        PrimitiveRestart = GL_PRIMITIVE_RESTART
        // TODO: finish this section, right now too tired to just wrw
    };
    void enable(Capability cap);
}
