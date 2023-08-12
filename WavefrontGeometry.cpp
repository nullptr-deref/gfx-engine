#include "include/WavefrontGeometry.hpp"

#include <fstream>
#include <map>
#include <sstream>
#include <string>

constexpr char COMMENT_MARKER = '#';

using DataTypeIdentifier = std::string;

struct Polygon;
struct TextureCoordinate;
struct VertexNormal;

namespace wavefront {
    auto parseVertex(const std::string_view &line) -> Vertex<float>;
    auto parseTextureCoordinate(const std::string_view &line) -> TextureCoordinate;
    auto parseVertexNormal(const std::string_view &line) -> VertexNormal;
    auto parsePolygon(const std::string_view &line) -> Polygon;
}

enum class DataType {
    Vertex,
    TextureCoordinate,
    VertexNormal,
    Polygon
};

const std::map<DataType, DataTypeIdentifier> identifiers {
    { DataType::Vertex, "v" },
    { DataType::TextureCoordinate, "vt" },
    { DataType::VertexNormal, "vn" },
    { DataType::Polygon, "f" },
};

auto readWavefrontFromFile(const std::string_view &filename) -> std::shared_ptr<WavefrontGeometry> {
    std::ifstream fileStream { filename.data() };
    std::string line;
    while (std::getline(fileStream, line)) {
        if (line.empty()) continue;
        if (line.front() == COMMENT_MARKER) continue;

        std::stringstream ss { line };

        DataTypeIdentifier identifier;
        ss >> identifier;
        if (identifier == identifiers.at(DataType::Vertex)) {
            const auto v = wavefront::parseVertex(line);
        }
        // TODO: Parsing logic here...
    }
}
