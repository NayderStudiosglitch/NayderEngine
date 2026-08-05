#pragma once
#include <string>
#include <vector>

struct NavPolygonNode {
    int poly_id;
    float center_x;
    float center_y; // Height metric mapped from the terrain heightmap
    float center_z;
    float slope_angle;
    bool is_walkable;
};

class NayderNavMeshEngine {
private:
    std::vector<NavPolygonNode> compiled_nav_mesh;
    float max_walkable_slope = 45.0f; // Max angle restriction in degrees

public:
    NayderNavMeshEngine();
    void BakeNavMeshFromHeightmap(int grid_size, float spacing);
    bool QueryPathNodeConstraints(float current_x, float current_z, float target_y_height, float target_slope, float& speed_out);
};
