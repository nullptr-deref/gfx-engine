#pragma once

#include <iostream>

#include <GL/glew.h>

#include "Object.hpp"

namespace gl {
    enum class BufferUsage : GLenum {
        StaticDraw = GL_STATIC_DRAW,
        DynamicDraw = GL_DYNAMIC_DRAW,
        StreamDraw = GL_STREAM_DRAW,
        StaticRead = GL_STATIC_READ,
        DynamicRead = GL_DYNAMIC_READ,
        StreamRead = GL_STREAM_READ,
        StaticCopy = GL_STATIC_COPY,
        DynamicCopy = GL_DYNAMIC_COPY,
        StreamCopy = GL_STREAM_COPY
    };

    enum class MappedBufferAccessFlags : GLbitfield {
        Read = GL_MAP_READ_BIT,
        Write = GL_MAP_WRITE_BIT
    };


    enum class BufferFormat : GLenum {
        RGBA8 = GL_RGBA8,
        RGBA16 = GL_RGBA16
    };

    enum class Type : GLenum {
        Byte = GL_BYTE,
        Ubyte = GL_UNSIGNED_BYTE,
        Short = GL_SHORT,
        Ushort = GL_UNSIGNED_SHORT,
        Int = GL_INT,
        Uint = GL_UNSIGNED_INT,
        Fixed = GL_FIXED,
        Float = GL_FLOAT,
        Double = GL_DOUBLE
    };
}

namespace gl {
    enum class TargetBuffer : GLenum {
        Array = GL_ARRAY_BUFFER,
        AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
        CopyRead = GL_COPY_READ_BUFFER,
        CopyWrite = GL_COPY_WRITE_BUFFER,
        DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,
        DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
        ElementArray = GL_ELEMENT_ARRAY_BUFFER,
        PixelPack = GL_PIXEL_PACK_BUFFER,
        PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
        Query = GL_QUERY_BUFFER,
        ShaderStorage = GL_SHADER_STORAGE_BUFFER,
        Texture = GL_TEXTURE_BUFFER,
        TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
        Uniform = GL_UNIFORM_BUFFER
    };

    template <TargetBuffer Target>
    class BasicBuffer : public Object {
    protected:
        TargetBuffer target_;
    public:
        BasicBuffer() : target_(Target) {}
        void gen() override;
        void del() override;
        void bind() override;
        void unbind() override;

        //TODO: implement it somehow
        void setLabel() override { std::cout << "Not implemented.\n"; }
        String getLabel() override { return "Not implemented.\n"; }

        auto subData(GLintptr offset, GLsizeiptr size, const GLvoid *data) -> void;
        auto clearData(BufferFormat internalfmt, BufferFormat fmt, Type type, const GLvoid *data) -> void;
        auto clearSubData(BufferFormat internalfmt, GLintptr offset, GLsizeiptr size, BufferFormat fmt, Type type, const GLvoid *data) -> void;
        auto mapRange(GLintptr offset, GLsizeiptr length, MappedBufferAccessFlags accessflags) -> GLvoid *;
    };

    template <TargetBuffer Target>
    class Buffer : public BasicBuffer<Target> {
    public:
        Buffer() : BasicBuffer<Target>() {}

        auto data(GLsizeiptr size, const GLvoid *data, BufferUsage usage) -> void;
    };

    // Buffer for immutable data
    template <TargetBuffer Target>
    class StorageBuffer : public BasicBuffer<Target> {
    public:
        // More info about this section on https://www.khronos.org/opengl/wiki/Buffer_Object#Immutable_access_methods
        enum class AccessFlags : GLbitfield {
            // Allows the user to read the buffer via mapping the buffer.
            // Without this flag, attempting to map the buffer for reading will fail.
            MapRead = GL_MAP_READ_BIT,
            
            // Allows the user to map the buffer for writing.
            // Without this flag, attempting to map the buffer for writing will fail.
            MapWrite = GL_MAP_WRITE_BIT,
            
            // Allows the user to modify the contents of the storage with glBufferSubData.
            // Without this flag, attempting to call that function on this buffer will fail.
            DynamicStorage = GL_DYNAMIC_STORAGE_BIT,
            
            // Allows the buffer object to be mapped in such a way that it can be used while it is mapped.
            // Without this flag, attempting to perform any operation on the buffer while it is mapped will fail.
            // You must use one of the mapping bits when using this bit.
            MapPersistent = GL_MAP_PERSISTENT_BIT,
            
            // Allows reads from andwrites to a persistent buffer to be coherent with OpenGL, without an explicit barrier.
            // Without this flag, you must use an explicit barrier to achieve coherency.You must use GL_PERSISTENT_BIT when using this bit.
            MapCoherent = GL_MAP_COHERENT_BIT,
            
            // A hint that suggests to the implementation that the storage for the buffer should come from "client" memory.
            ClientStorage = GL_CLIENT_STORAGE_BIT
        };
        StorageBuffer() : BasicBuffer() {}

        auto store(GLsizeiptr size, const GLvoid *data, AccessFlags accessflags) -> void;
    };
}

// ========== BasicBuffer definitions ========== //
namespace gl {
    template <TargetBuffer Target>
    auto BasicBuffer<Target>::gen() -> void {
        glGenBuffers(1, &id);
    }

    template <TargetBuffer Target>
    auto BasicBuffer<Target>::del() -> void {
        glDeleteBuffers(1, &id);
    }

    template <TargetBuffer Target>
    auto BasicBuffer<Target>::bind() -> void {
        glBindBuffer(static_cast<GLenum>(this->target_), id);
    }

    template <TargetBuffer Target>
    auto BasicBuffer<Target>::unbind() -> void {
        glBindBuffer(static_cast<GLenum>(this->target_), 0);
    }

    // TODO: replace GLvoid * with some Array structure wrapping access to raw memory
    // (does it worth it?)
    template <TargetBuffer Target>
    auto BasicBuffer<Target>::subData(GLintptr offset, GLsizeiptr size, const GLvoid *data) -> void {
        glBufferSubData(static_cast<GLenum>(this->target_), offset, size, data);
    }

    // TODO: replace GLvoid * with some Array structure wrapping access to raw memory
    // (does it worth it?)
    template <TargetBuffer Target>
    auto BasicBuffer<Target>::clearData(BufferFormat internalfmt, BufferFormat fmt, Type type, const GLvoid *data) -> void {
        glClearBufferData(static_cast<GLenum>(this->target_), static_cast<GLenum>(internalfmt), static_cast<GLenum>(fmt), static_cast<GLenum>(type), data);
    }

    // TODO: replace GLvoid * with some Array structure wrapping access to raw memory
    template <TargetBuffer Target>
    auto BasicBuffer<Target>::clearSubData(BufferFormat internalfmt, GLintptr offset, GLsizeiptr size, BufferFormat fmt, Type type, const GLvoid *data) -> void {
        glClearBufferSubData(
            static_cast<GLenum>(this->target_),
            static_cast<GLenum>(internalfmt),
            offset,
            size,
            static_cast<GLenum>(fmt),
            static_cast<GLenum>(type),
            data
        );
    }
}

namespace gl {
    template <TargetBuffer Target>
    auto Buffer<Target>::data(GLsizeiptr size, const GLvoid *data, BufferUsage usage) -> void {
        glBufferData(static_cast<GLenum>(this->target_), size, data, static_cast<GLenum>(usage));
    }
}