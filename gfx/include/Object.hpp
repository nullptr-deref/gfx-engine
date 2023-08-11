#pragma once

#include <string>
#include <cstdint>

#include <GL/glew.h>

using u32 = uint32_t;

namespace gl {
    template <typename T>
    concept ObjectImplementation = requires { typename T::id; };
}

namespace gl {
    using String = std::string;
    using ObjectID = GLuint;

    class Object {
    protected:
        ObjectID id;
    public:
        Object() = default;
        virtual auto gen() -> void = 0;
        virtual auto del() -> void = 0;
        virtual auto bind() -> void = 0;
        virtual auto unbind() -> void = 0;
        virtual auto setLabel() -> void = 0;
        virtual auto getLabel() -> String = 0;
    };

    class ObjectArray {
    protected:
        ObjectID *ids;
    public:
        ObjectArray() = default;
        virtual auto gen(u32 count = 1) -> void = 0;
        virtual auto del(u32 count = 1) -> void = 0;

        template <ObjectImplementation ObjType>
        auto get(size_t idx) -> ObjType;
    };
}

namespace gl {
    template <ObjectImplementation ObjType>
    auto ObjectArray::get(size_t idx) -> ObjType {
        ObjType obj;
        obj.id = ids[idx];

        return obj;
    }
}

// namespace gl {
//     class BufferArray : ObjectArray {};
// }
//
// int f {
//     gl::BufferArray<Array> arr;
//     arr.gen(3);
//     float coord[9] = { 1, 2 ,3, 5 , 6, 7, 1, 2, 3 };
//     arr.data(coord);
//     float coordsep[3][3] = { { 1, 2, 3 }, { 2, 3, 4 }, { 5, 6, 7} };
//     // arr.elementData(size_t idx, GLsizeiptr size, const GLvoid *data);
//     arr.elementData(0, 3 * sizeof(float), coordsep[1]);
//
//     arr.get<Buffer<GL_ARRAY_BUFFER>>(2);
// }