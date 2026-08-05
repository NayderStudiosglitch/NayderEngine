#include "GizmoEngine.h"
#include <iostream>

NayderGizmoEngine::NayderGizmoEngine() {
    current_tool = GizmoMode::MOVE_TRANSLATE; // Default tool selection
}

void NayderGizmoEngine::SetActiveGizmoMode(GizmoMode mode) {
    current_tool = mode;
    std::cout << "\n🛠️  [GIZMO ENGINE CHANNELS]: Swapping active transformation handle to: ";
    if (mode == GizmoMode::MOVE_TRANSLATE) std::cout << "MOVE (X/Y/Z Translation Vectors)" << std::endl;
    if (mode == GizmoMode::ROTATE_DEG)     std::cout << "ROTATE (Euler Angular Degrees)" << std::endl;
    if (mode == GizmoMode::SCALE_UNIFORM)  std::cout << "SCALE (Uniform Dimension Modifiers)" << std::endl;
}

void NayderGizmoEngine::RenderActiveGizmoHandles(float x, float y, float z) {
    // Simulated vertex drawing pass projecting 3D viewport handles over selected coordinates
    std::cout << "   📐 [GL_GIZMO_RENDER]: Projecting overlay handles at target vector location: (" << x << ", " << y << ", " << z << ")" << std::endl;
    if (current_tool == GizmoMode::MOVE_TRANSLATE) {
        std::cout << "      └── 🔴 DrawLine(X-Axis Arrow) │ 🟢 DrawLine(Y-Axis Arrow) │ 🔵 DrawLine(Z-Axis Arrow)" << std::endl;
    } else if (current_tool == GizmoMode::ROTATE_DEG) {
        std::cout << "      └── 🔴 DrawCircle(Pitch Rings) │ 🟢 DrawCircle(Yaw Rings) │ 🔵 DrawCircle(Roll Rings)" << std::endl;
    } else if (current_tool == GizmoMode::SCALE_UNIFORM) {
        std::cout << "      └── 🟨 DrawCube(Center Anchor Handle) │ Scaling multipliers bound." << std::endl;
    }
}

void NayderGizmoEngine::ApplyGizmoTransformDelta(GizmoMode tool, float input_axis, float& px, float& ry, float& scale, float dt) {
    float tool_sensitivity = 4.0f;
    if (tool == GizmoMode::MOVE_TRANSLATE) {
        px += input_axis * tool_sensitivity * dt;
    } else if (tool == GizmoMode::ROTATE_DEG) {
        ry += input_axis * 45.0f * tool_sensitivity * dt; // Faster angular rotation changes
    } else if (tool == GizmoMode::SCALE_UNIFORM) {
        scale += input_axis * 1.5f * dt;
        if (scale < 0.1f) scale = 0.1f; // Prevent reverse inverse mesh geometry collapses
    }
}

std::string NayderGizmoEngine::GetCurrentToolLabel() const {
    if (current_tool == GizmoMode::MOVE_TRANSLATE) return "MOVE_TOOL";
    if (current_tool == GizmoMode::ROTATE_DEG)     return "ROTATE_TOOL";
    if (current_tool == GizmoMode::SCALE_UNIFORM)  return "SCALE_TOOL";
    return "UNKNOWN";
}
