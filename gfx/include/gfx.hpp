#pragma once

#include <GL/glew.h>

#include "Object.hpp"
#include "Buffer.hpp"

#include "../glsl/include/Program.hpp"
#include "../glsl/include/Shader.hpp"
#include "../glsl/include/VertexShader.hpp"

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
        // TODO: finish this section, right now too tired to just copy-paste this from documentation
    };

    enum class BlendFactor : GLenum {
        Zero = GL_ZERO,
        One = GL_ONE,
        SrcColor = GL_SRC_COLOR,
        OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
        DstColor = GL_DST_COLOR,
        OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,
        SrcAlpha = GL_SRC_ALPHA,
        OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
        DstAlpha = GL_DST_ALPHA,
        OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,
        ConstantColor = GL_CONSTANT_COLOR,
        OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
        ConstantAlpha = GL_CONSTANT_ALPHA,
        OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
        SrcAlphaSaturate = GL_SRC_ALPHA_SATURATE,
        Src1Color = GL_SRC1_COLOR,
        OneMinusSrc1Color = GL_ONE_MINUS_SRC1_COLOR,
        Src1Alpha = GL_SRC1_ALPHA,
        OneMinusSrc1Alpha = GL_ONE_MINUS_SRC1_ALPHA
    };

    void enable(Capability cap);
    void blendFunc(BlendFactor srcFactor, BlendFactor destFactor);
}
