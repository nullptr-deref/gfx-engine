#pragma once

#include <cstddef>
#include <malloc.h>

template <typename T>
class DynamicArray {
    T *data_ = nullptr;
public:
    size_t size;

    DynamicArray() = delete;
    explicit DynamicArray(size_t size) : size(size) {
        data_ = malloc(size * sizeof(T));
    }

    auto operator[](size_t idx) -> T & {
        return *(data_ + idx);
    }

    auto at(size_t idx) -> T & {
        if (0 <= idx && idx <= size)
            return *(data_ + idx);
    }

    auto data() -> T * {
        return data_;
    }

    ~DynamicArray() {
        if (data_)
            free(data_);
    }
};