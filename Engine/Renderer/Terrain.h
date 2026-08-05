#pragma once
#include <string>
#include <vector>

struct TerrainVertex {
    float x, y, z;
    float u, v; // UV coordinate mapping pou tekstire zèb/sabl
};

struct TerrainMesh {
    std::string heightmap_source;
    int grid_width = 0;
    int grid_height = 0;
    std::vector<TerrainVertex> vertex_buffer;
    unsigned int vao_id = 0;
    bool is_buffered_to_gpu = false;
};

class NayderTerrainRenderer {
private:
    TerrainMesh world_terrain;
public:
    TerrainMesh GenerateTerrainFromHeightmap(std::string image_path, int width, int height);
    void UploadTerrainToVRAM(TerrainMesh& terrain);
    void RenderTerrainMesh();
};
