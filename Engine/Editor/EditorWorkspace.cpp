#include "EditorWorkspace.h"
#include <iostream>
#include <cmath>

NayderEditorWorkspace::NayderEditorWorkspace() {}

void NayderEditorWorkspace::SetEditorLayoutMatrix() {
    std::cout << "\n==========================================================================================" << std::endl;
    std::cout << " 🛠️  [NAYDER ENGINE EDITOR v0.2.3] │ File  Edit  View  Build  Play                        " << std::endl;
    std::cout << "==========================================================================================" << std::endl;
}

void NayderEditorWorkspace::DrawSceneHierarchyPanel() {
    std::cout << " 📁 [SCENE HIERARCHY]       │";
}

void NayderEditorWorkspace::DrawCentralViewportPanel() {
    std::cout << "        🎥 [3D REAL-TIME VIEWPORT]        │";
}

bool ProcessMousePickingRaycast(double mouse_x, double mouse_y, float zombie_x, float zombie_z, float radius) {
    float normalized_x = (2.0f * static_cast<float>(mouse_x)) / 1366.0f - 1.0f;
    float normalized_y = 1.0f - (2.0f * static_cast<float>(mouse_y)) / 768.0f;

    std::cout << "\n🎯 [MOUSE PICK]: Cursor Intercept: (" << mouse_x << ", " << mouse_y << ") │ NDC: (" << normalized_x << ", " << normalized_y << ")" << std::endl;
    
    float delta_x = zombie_x - (normalized_x * 20.0f); 
    if (std::abs(delta_x) < radius + 5.0f) {
        std::cout << " 🎉 [RAYCAST HIT]: Intersection confirmed with 'Zombie_01' Box Boundaries!" << std::endl;
        return true;
    }
    return false;
}

void NayderEditorWorkspace::DrawInspectorPanel(const SelectedEntityData& selected) {
    std::string play_mode_flag = (selected.mesh_source == "PLAY_MODE_ACTIVE") ? "🎮 [SIMULATION PLAY MODE ACTIVE]" : "[ EDITOR EDIT MODE ACTIVE ]";
    
    std::cout << " 🔍 [INSPECTOR PANEL]" << std::endl;
    std::cout << " ├── 🟢 Player              │                                         │  Selected Object: " << selected.name << std::endl;
    std::cout << " ├── 🧟 Zombie_01 " << (selected.name == "Zombie_01" ? "<-- SELECTED" : "            ") << "  │     " << play_mode_flag << "     │  ├── Position X: " << selected.pos_x << "  Y: " << selected.pos_y << "  Z: " << selected.pos_z << std::endl;
    std::cout << " ├── 🧟 Zombie_02           │                                         │  ├── Rotation X: " << selected.rot_x << "  Y: " << selected.rot_y << "  Z: " << selected.rot_z << std::endl;
    std::cout << " └── 🧱 sandbag_gate        │        [ Locked at 107 FPS ]            │  └── Scale   : " << selected.scale << std::endl;
    
    if (selected.name != "None" && selected.mesh_source != "PLAY_MODE_ACTIVE") {
        std::cout << "────────────────────────────┴─────────────────────────────────────────┼───────────────────────────" << std::endl;
        std::cout << "                                                                      │ 🏹 [ACTIVE TRANSFORM GIZMO]:" << std::endl;
        std::cout << "                                                                      │          ↑ Y              " << std::endl;
        std::cout << "                                                                      │          │                " << std::endl;
        std::cout << "                                                                      │   ←──────●──────→ X       " << std::endl;
        std::cout << "                                                                      │         /                 " << std::endl;
        std::cout << "                                                                      │        ↙ Z  (Tool active) " << std::endl;
    }
    std::cout << "──────────────────────────────────────────────────────────────────────┴===========================" << std::endl;
}

void NayderEditorWorkspace::DrawContentBrowserPanel() {
    std::cout << " 📦 [CONTENT BROWSER] │ 📁 Models/  📁 Textures/  📁 Audio/  📁 Maps/  📁 Scripts/  " << std::endl;
    std::cout << "==========================================================================================" << std::endl;
}
