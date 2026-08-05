#pragma once
#include <string>
#include <vector>

enum class PlacementType { MESH_HOUSE, ZOMBIE_SPAWNER, AMMO_BOX, DEFENSIVE_WALL };

struct PlacedObjectNode {
    unsigned int unique_node_id;
    std::string asset_name;
    PlacementType type;
    float x, y, z;
    float scale;
};

class EditorSandboxTools {
private:
    std::vector<PlacedObjectNode> sandbox_scene_nodes;
    unsigned int global_node_id_counter = 5000;

public:
    EditorSandboxTools();
    void ExecuteGridRaycastSpawn(PlacementType asset_type, float spawn_x, float spawn_y, float spawn_z, float asset_scale);
    void ExportSandboxMapFile();
};
