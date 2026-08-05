#pragma once
#include <string>

enum class GizmoMode { MOVE_TRANSLATE, ROTATE_DEG, SCALE_UNIFORM };

class NayderGizmoEngine {
private:
    GizmoMode current_tool;

public:
    NayderGizmoEngine();
    void SetActiveGizmoMode(GizmoMode mode);
    void RenderActiveGizmoHandles(float x, float y, float z);
    void ApplyGizmoTransformDelta(GizmoMode tool, float input_axis, float& px, float& ry, float& scale, float dt);
    std::string GetCurrentToolLabel() const;
};
