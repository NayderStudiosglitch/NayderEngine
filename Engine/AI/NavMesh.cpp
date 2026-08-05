#include "NavMesh.h"
#include <iostream>

NayderNavMeshEngine::NayderNavMeshEngine() {
    // Navigation cells map buffer allocated
}

void NayderNavMeshEngine::BakeNavMeshFromHeightmap(int grid_size, float spacing) {
    std::cout << "\n🧠 [NAVMESH BAKING SYSTEM]: Scanning tridimensional terrain node arrays..." << std::endl;
    std::cout << " -> Filtering slope angle deltas across " << grid_size << "x" << grid_size << " environment coordinates..." << std::endl;

    int baked_poly_count = 0;
    int blocked_cliff_count = 0;

    for (int z = 0; z < grid_size; ++z) {
        for (int x = 0; x < grid_size; ++x) {
            NavPolygonNode node;
            node.poly_id = baked_poly_count++;
            node.center_x = (float)x * spacing;
            node.center_z = (float)z * spacing;
            
            // Simulate slope steepness calculation for different mountain zones
            if (x > 10 && x < 20 && z > 10 && z < 20) {
                node.slope_angle = 55.0f; // Steep cliff face zones
                node.is_walkable = false;
                blocked_cliff_count++;
            } else {
                node.slope_angle = 12.5f; // Gentle plain roads/valleys
                node.is_walkable = true;
            }
            compiled_nav_mesh.push_back(node);
        }
    }

    std::cout << "   ┌── [BAKE COMPLETE]: 3D Navigation Graph generated cleanly!" << std::endl;
    std::cout << "   ├── Total Baked Walkable Nodes: " << (baked_poly_count - blocked_cliff_count) << " Polygons" << std::endl;
    std::cout << "   └── 🚫 [STATIC RESTRAINTS]: Isolated " << blocked_cliff_count << " steep nodes marked as impassable bounds." << std::endl;
}

bool NayderNavMeshEngine::QueryPathNodeConstraints(float current_x, float current_z, float target_y_height, float target_slope, float& speed_out) {
    std::cout << "\n🔎 [NAVMESH RUNTIME QUERY]: Evaluating agent positions at coordinate: (" << current_x << ", " << current_z << ") ..." << std::endl;

    if (target_slope > max_walkable_slope) {
        speed_out = 0.0f;
        std::cout << "   🚫 [IMPASSABLE CLAMP]: Angle " << target_slope << "° exceeds constraint limits (" << max_walkable_slope << "° max)!" << std::endl;
        std::cout << "      [VELOCITY BLOCK]: Agent path routing aborted at cliff edge face node." << std::endl;
        return false;
    }

    // Apply speed deduction penalty if running up gentle hill slopes
    if (target_slope > 20.0f) {
        speed_out *= 0.65f; // Reduce velocity to 65% when ascending slopes
        std::cout << "   📉 [SLOPE SPEED PENALTY]: Ascending " << target_slope << "° hill slope. Scaling speed down to: " << speed_out << " m/s." << std::endl;
    } else {
        std::cout << "   ✅ [NODE VALiD]: Surface node level is clear. Speed maintained at " << speed_out << " m/s across flat valley." << std::endl;
    }
    return true;
}
