#include "EditorWorkspace.h"
#include <iostream>

NayderEditorWorkspace::NayderEditorWorkspace() {}

void NayderEditorWorkspace::SetEditorLayoutMatrix() {
    // Simulated 2D orthographic rasterizer split commands
    std::cout << "\n==========================================================================================" << std::endl;
    std::cout << " 🛠️  [NAYDER ENGINE EDITOR v0.2.0] │ File  Edit  View  Build  Play                        " << std::endl;
    std::cout << "==========================================================================================" << std::endl;
}

void NayderEditorWorkspace::DrawSceneHierarchyPanel() {
    std::cout << " 📁 [SCENE HIERARCHY]       │";
}

void NayderEditorWorkspace::DrawCentralViewportPanel() {
    std::cout << "        🎥 [3D REAL-TIME VIEWPORT]        │";
}

void NayderEditorWorkspace::DrawInspectorPanel(const SelectedEntityData& selected) {
    std::cout << " 🔍 [INSPECTOR PANEL]" << std::endl;
    std::cout << " ├── 🟢 Player              │        [ Desert Ghost City Live ]       │  Selected: " << selected.name << std::endl;
    std::cout << " ├── 🧟 Zombie_01           │                                         │  ├── Position : (" << selected.pos_x << ", " << selected.pos_y << ", " << selected.pos_z << ")" << std::endl;
    std::cout << " ├── 🧟 Zombie_02           │        glViewport(250, 200, 850, 400)   │  ├── Rotation : (" << selected.rot_x << ", " << selected.rot_y << ", " << selected.rot_z << ")" << std::endl;
    std::cout << " ├── 🧱 sandbag_gate        │                                         │  ├── Scale    : x" << selected.scale << std::endl;
    std::cout << " └── ⛰️  Terrain_Mesh       │        [ Locked at 107 FPS ]            │  └── Mesh File: " << selected.mesh_source << std::endl;
    std::cout << "────────────────────────────┴─────────────────────────────────────────┴───────────────────────────" << std::endl;
}

void NayderEditorWorkspace::DrawContentBrowserPanel() {
    std::cout << " 📦 [CONTENT BROWSER] │ 📁 Models/  📁 Textures/  📁 Audio/  📁 Maps/  📁 Scripts/  " << std::endl;
    std::cout << "==========================================================================================" << std::endl;
}
