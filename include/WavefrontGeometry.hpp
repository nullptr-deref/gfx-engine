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
    WavefrontGeometry() = delete;
private:
    std::unique_ptr<Vertex<float>> vertices;
};

auto readWavefrontFromFile(const std::string_view &filename) -> std::shared_ptr<WavefrontGeometry>;
