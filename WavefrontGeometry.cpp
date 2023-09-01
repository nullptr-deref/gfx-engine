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
                return "Filestream reached eof.";
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
        return "Filestream reached eof.";
    }

    ~EofException() {}
};

struct Polygon;
struct TextureCoordinate;
struct VertexNormal;

namespace wavefront {
    auto parseVertex(const std::string_view &line) -> Vertex<float> {
        Vertex<float> v;

        std::string mutableLine { line.data() };
        std::istringstream ss { mutableLine };
        ss >> v.x >> v.y >> v.z;
        // TODO: implement parsing of 'w' vertex component.
        // It's a bit complicatd because it's an arbitrary component
        // and doesn't always appear.

        return v;
    }
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

auto prepareWavefrontGeometry(const std::string_view &filename) -> WavefrontGeometry;
auto trimEndlineComment(const std::string_view &line) -> std::string_view;
auto openFileForReadSafely(const std::string_view &filename) -> std::ifstream;

auto readWavefrontFromFile(const std::string_view &filename) -> std::shared_ptr<WavefrontGeometry> {
    auto wavefront = prepareWavefrontGeometry(filename);

    auto fileStream = openFileForReadSafely(filename);
    std::string line;
    while (std::getline(fileStream, line)) {
        if (line.empty()) continue;
        if (line.front() == COMMENT_MARKER) continue;

        line = trimEndlineComment(line);

        std::istringstream ss { line };

        DataTypeIdentifier identifier;
        ss >> identifier;
        if (identifier == identifiers.at(DataTypeId::Vertex)) {
            const auto v = wavefront::parseVertex(ss.str());
            // Need to somehow implement things around memory
            // management inside WavefrontGeometry class
        }
        // TODO: Parsing logic here...
    }

    return std::make_shared<WavefrontGeometry>(std::move(wavefront));
}

auto trimEndlineComment(const std::string_view &line) -> std::string_view {
    return line.substr(0, line.find(COMMENT_MARKER));
}

auto countGeometryVertices(const std::string_view &filename) -> size_t {
    auto countStream = openFileForReadSafely(filename);
    size_t verticesCount = 0;
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

    return verticesCount;
}

// Prepares Wavefront geometry for reading it's data from the specified file.
auto prepareWavefrontGeometry(const std::string_view &filename) -> WavefrontGeometry {
    return WavefrontGeometry(countGeometryVertices(filename));
}

auto openFileForReadSafely(const std::string_view &filename) -> std::ifstream {
    std::ifstream filestream { filename.data() };
    if (!filestream) {
        if (filestream.bad()) throw FileReadException(FileReadState::BadBit);
        else if (filestream.fail()) throw FileReadException(FileReadState::FailBit);
        else throw EofException();
    }

    return filestream;
}
