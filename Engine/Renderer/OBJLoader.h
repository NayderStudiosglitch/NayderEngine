#pragma once
#include <string>
#include <vector>

struct Vertex3D {
    float x, y, z;
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
    std::vector<UVCoord> uvs;
    std::vector<NormalVector> normals;
    int total_triangles = 0;
    bool loaded_to_vram = false;
};

class NayderOBJLoader {
public:
    CompiledMesh ParseOBJFile(std::string file_path);
    void UploadMeshToGPU(CompiledMesh& mesh);
};
