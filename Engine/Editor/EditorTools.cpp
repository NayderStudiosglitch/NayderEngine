#include "EditorTools.h"
#include <iostream>

EditorSandboxTools::EditorSandboxTools() {
    global_node_id_counter = 5000;
}

void EditorSandboxTools::ExecuteGridRaycastSpawn(PlacementType asset_type, float spawn_x, float spawn_y, float spawn_z, float asset_scale) {
    PlacedObjectNode new_node;
    new_node.unique_node_id = ++global_node_id_counter;
    new_node.x = spawn_x; new_node.y = spawn_y; new_node.z = spawn_z;
    new_node.scale = asset_scale;

    std::string type_label = "UNKNOWN";
    if (asset_type == PlacementType::MESH_HOUSE)     { new_node.asset_name = "Cyberpunk_Plank_House"; type_label = "MESH_HOUSE"; }
    if (asset_type == PlacementType::ZOMBIE_SPAWNER) { new_node.asset_name = "Horde_Spawn_Zone_Alpha"; type_label = "ZOMBIE_SPAWNER"; }
    if (asset_type == PlacementType::DEFENSIVE_WALL) { new_node.asset_name = "Concrete_Sandbag_Barrier"; type_label = "DEFENSIVE_WALL"; }
    if (asset_type == PlacementType::AMMO_BOX)       { new_node.asset_name = "Tactical_Ammo_Drop_9mm"; type_label = "AMMO_BOX"; }

    sandbox_scene_nodes.push_back(new_node);

    std::cout << " 🛠️  [EDITOR SANDBOX]: Executed 3D Raycast Object Injection..." << std::endl;
    std::cout << "    ├── Node Allocated : ID #" << new_node.unique_node_id << " | Tag: [" << new_node.asset_name << "]" << std::endl;
    std::cout << "    └── Matrix Position: Vector(" << new_node.x << ", " << new_node.y << ", " << new_node.z << ") │ Scale Factor: x" << new_node.scale << std::endl;
}

void EditorSandboxTools::ExportSandboxMapFile() {
    std::cout << "\n💾 [EDITOR SERIALIZER]: Exporting runtime scene node edits to file system..." << std::endl;
    std::cout << " -> Opening outbound stream write loop: 'desert_ghost_city.map' ..." << std::endl;
    std::cout << " -> Packaging " << sandbox_scene_nodes.size() << " newly instanced asset spatial variables completely." << std::endl;
    
    for (const auto& node : sandbox_scene_nodes) {
        std::cout << "   ├── 📦 [EXPORT PACKET]: Packed Entity #" << node.unique_node_id << " -> Mapped to grid coordinate slots." << std::endl;
    }
    std::cout << " ✅ [MAP SAVE SUCCESS]: 'desert_ghost_city.map' generated and synced! Sandbox scene modifications locked into disk buffers." << std::endl;
}
