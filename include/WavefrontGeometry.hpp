#pragma once

#include <concepts>
#include <memory>
#include <string_view>

template <std::floating_point CoordinateType>
struct Vertex {
    CoordinateType x;
    CoordinateType y;
    CoordinateType z;
    CoordinateType w;
};

class WavefrontGeometry {
public:
    using VertexType = Vertex<float>;
    WavefrontGeometry(size_t vertCount)
    : vertices(std::make_unique<VertexType>(vertCount)) {}
private:
    std::unique_ptr<VertexType> vertices;
};

auto readWavefrontFromFile(const std::string_view &filename) -> std::shared_ptr<WavefrontGeometry>;
