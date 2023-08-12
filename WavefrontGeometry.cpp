#include "include/WavefrontGeometry.hpp"

#include <fstream>
#include <map>
#include <sstream>
#include <string>

constexpr char COMMENT_MARKER = '#';
constexpr char VERTEX_DATA_MARKER = 'v';

using DataTypeIdentifier = std::string;

enum class FileReadState {
    GoodBit,
    BadBit,
    FailBit,
    Eof
};

class FileReadException {
public:
    explicit FileReadException(FileReadState &&s) noexcept : state_(std::move(s)) {}

    virtual const char *what() const noexcept {
        switch (state_) {
            case FileReadState::FailBit:
                return "Filestream reported fail bit.";
            case FileReadState::BadBit:
                return "Filestream faced irrecoverable error.";
            case FileReadState::Eof:
                return "End of file was reached.";
        }
    }

    virtual ~FileReadException();
private:
    const FileReadState state_;
};

class EofException : FileReadException {
public:
    explicit EofException() noexcept : FileReadException(FileReadState::Eof) {}
    const char *what() const noexcept override {
        return "Eof was reached.";
    }

    ~EofException() {}
};

struct Polygon;
struct TextureCoordinate;
struct VertexNormal;

namespace wavefront {
    auto parseVertex(const std::string_view &line) -> Vertex<float>;
    auto parseTextureCoordinate(const std::string_view &line) -> TextureCoordinate;
    auto parseVertexNormal(const std::string_view &line) -> VertexNormal;
    auto parsePolygon(const std::string_view &line) -> Polygon;
}

enum class DataTypeId {
    Vertex,
    TextureCoordinate,
    VertexNormal,
    Polygon
};

const std::map<DataTypeId, DataTypeIdentifier> identifiers {
    { DataTypeId::Vertex, "v" },
    { DataTypeId::TextureCoordinate, "vt" },
    { DataTypeId::VertexNormal, "vn" },
    { DataTypeId::Polygon, "f" }
};

// TODO: probably I should create some function which will initialize
// WavefrontGeometry's inner memory (like allocating enough space for
// vertices and so on), but will see.

auto readWavefrontFromFile(const std::string_view &filename) -> std::shared_ptr<WavefrontGeometry> {
    std::ifstream fileStream { filename.data() };
    if (fileStream.is_open()) {
        std::string line;
        while (std::getline(fileStream, line)) {
            if (line.empty()) continue;
            if (line.front() == COMMENT_MARKER) continue;

            std::istringstream ss { line };

            DataTypeIdentifier identifier;
            ss >> identifier;
            if (identifier == identifiers.at(DataTypeId::Vertex)) {
                const auto v = wavefront::parseVertex(line);
                // Need to somehow implement things around memory
                // management inside WavefrontGeometry class
            }
            // TODO: Parsing logic here...
        }
    }
    else if (fileStream.bad()) throw FileReadException(FileReadState::BadBit);
    else if (fileStream.fail()) throw FileReadException(FileReadState::FailBit);
    else throw EofException();
}

auto countGeometryVertices(const std::string_view &filename) -> size_t {
    std::ifstream countStream { filename.data() };
    size_t verticesCount = 0;
    if (countStream.is_open()) {
        std::string line;
        while (std::getline(countStream, line)) {
            if (line.empty()) continue;
            if (line.front() == COMMENT_MARKER
             || line.front() != VERTEX_DATA_MARKER) continue;

            std::istringstream ss { line };
            std::string identifier;
            ss >> identifier;
            if (identifier == identifiers.at(DataTypeId::Vertex)) {
                verticesCount++;
            }
        }
        countStream.close();
    }
    else if (countStream.bad()) throw FileReadException(FileReadState::BadBit);
    else if (countStream.fail()) throw FileReadException(FileReadState::FailBit);
    else throw EofException();

    return verticesCount;
}
