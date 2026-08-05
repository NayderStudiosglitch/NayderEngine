#include "EditorWorkspace.h"
#include <iostream>
#include <vector>
#include <cmath>

NayderEditorWorkspace::NayderEditorWorkspace() {}

void NayderEditorWorkspace::SetEditorLayoutMatrix() {
    std::cout << "\n==========================================================================================" << std::endl;
    std::cout << " 🏗️  [NAYDER MASTER ENGINE EDITOR v0.3.0] │ File  Edit  View  Build  Play                  " << std::endl;
    std::cout << "==========================================================================================" << std::endl;
}

void NayderEditorWorkspace::DrawSceneHierarchyPanel() {
    std::cout << " 📁 [SCENE HIERARCHY]       │";
}

void NayderEditorWorkspace::DrawCentralViewportPanel() {
    std::cout << "        🎥 [3D REAL-TIME VIEWPORT]        │";
}

// 🌍 UPGRADED MULTI-NODE UNIVERSAL MOUSE PICKER (v0.3.0)
int EvaluateUniversalScenePicking(double mouse_x, double mouse_y, const std::vector<SelectedEntityData>& scene_graph) {
    float normalized_x = (2.0f * static_cast<float>(mouse_x)) / 1366.0f - 1.0f;
    float normalized_y = 1.0f - (2.0f * static_cast<float>(mouse_y)) / 768.0f;

    std::cout << "\n🎯 [UNIVERSAL RAYCAST INTERCEPT]: Cursor Position: (" << mouse_x << ", " << mouse_y << ") │ NDC: (" << normalized_x << ", " << normalized_y << ")" << std::endl;
    std::cout << " └── 🏹 Running intersection checks across active Scene Graph slots..." << std::endl;

    // Loop through the entire scene registry to check ray intersections
    for (size_t i = 0; i < scene_graph.size(); ++i) {
        float delta_x = scene_graph[i].pos_x - (normalized_x * 20.0f);
        if (std::abs(delta_x) < 4.0f) { // Intersection radius padding
            std::cout << "   🎉 [RAYCAST SELECTION PASS]: Hit confirmed with Node Index [" << i << "] -> \"" << scene_graph[i].name << "\"" << std::endl;
            return static_cast<int>(i);
        }
    }
    return -1; // Clicked on empty open world grid space
}

void NayderEditorWorkspace::DrawInspectorPanel(const SelectedEntityData& selected) {
    std::string active_view_flag = (selected.mesh_source == "PLAY_MODE_ACTIVE") ? "🎮 [SIMULATION RUNNING]" : "[ EDITOR WORKSPACE EDITING ]";
    
    std::cout << " 🔍 [INSPECTOR PANEL]" << std::endl;
    std::cout << " ├── 🟢 Player              │                                         │  Focused Entity: " << selected.name << std::endl;
    std::cout << " ├── 🧱 sandbag_gate        │     " << active_view_flag << "     │  ├── Position X: " << selected.pos_x << "  Y: " << selected.pos_y << "  Z: " << selected.pos_z << std::endl;
    std::cout << " ├── 💡 Directional_Sun     │                                         │  ├── Rotation X: " << selected.rot_x << "  Y: " << selected.rot_y << "  Z: " << selected.rot_z << std::endl;
    std::cout << " └── ⛰️  Desert_Ghost_City   │        [ Frame Locked at 107 FPS ]       │  └── Scale Unit: " << selected.scale << std::endl;
    
    // Draw the contextual 3D Gizmo axis mapping overlays (v0.2.1)
    if (selected.name != "None" && selected.mesh_source != "PLAY_MODE_ACTIVE") {
        std::cout << "────────────────────────────┴─────────────────────────────────────────┼───────────────────────────" << std::endl;
        std::cout << "                                                                      │ 🏹 [ACTIVE TRANSFORM GIZMO]:" << std::endl;
        std::cout << "                                                                      │          ↑ Y              " << std::endl;
        std::cout << "                                                                      │          │   (Handles ready)" << std::endl;
        std::cout << "                                                                      │   ←──────●──────→ X       " << std::endl;
        std::cout << "                                                                      │         /                 " << std::endl;
        std::cout << "                                                                      │        ↙ Z  [Object Mesh: " << selected.mesh_source << "]" << std::endl;
    }
    std::cout << "──────────────────────────────────────────────────────────────────────┴===========================" << std::endl;
}

void NayderEditorWorkspace::DrawContentBrowserPanel() {
    std::cout << " 📦 [CONTENT BROWSER] │ 📁 Models/ (soldier.obj, house.obj)  📁 Textures/  📁 Audio/  📁 Maps/  📁 Scripts/  " << std::endl;
    std::cout << " └── ➕ [ASSET ACTION]: Drag-and-drop protocol listener operational. Ready to import loose asset file streams." << std::endl;
    std::cout << "==========================================================================================" << std::endl;
}
