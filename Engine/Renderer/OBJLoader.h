#pragma once
#include <string>
#include <vector>

struct Vertex3D {
    float x, y, z;
};

struct ColorRGB {
    float r, g, b;
};

struct UVCoord {
    float u, v;
};

struct NormalVector {
    float nx, ny, nz;
};

struct CompiledMesh {
    std::string model_name;
    std::vector<Vertex3D> vertices;
    std::vector<ColorRGB> colors; // Added for hardware coloring
    std::vector<unsigned int> indices; // Added for indexed elements
    std::vector<UVCoord> uvs;
    std::vector<NormalVector> normals;
    int total_indices = 0; // Added for indexed draw calls
    bool loaded_to_vram = false;
};

class NayderOBJLoader {
public:
    CompiledMesh ParseOBJFile(std::string file_path);
    // Fixed signature layout to receive hardware pipeline buffer handles
    void UploadMeshToGPU(CompiledMesh& mesh, unsigned int& out_vao, unsigned int& out_vbo, unsigned int& out_ebo);
};
