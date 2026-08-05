#pragma once
#include <string>

struct SelectedEntityData {
    std::string name;
    float pos_x, pos_y, pos_z;
    float rot_x, rot_y, rot_z;
    float scale;
    std::string mesh_source;
};

class NayderEditorWorkspace {
private:
    int window_w = 1366;
    int window_h = 768;

public:
    NayderEditorWorkspace();
    void SetEditorLayoutMatrix();
    void DrawSceneHierarchyPanel();
    void DrawCentralViewportPanel();
    void DrawInspectorPanel(const SelectedEntityData& selected);
    void DrawContentBrowserPanel();
};
