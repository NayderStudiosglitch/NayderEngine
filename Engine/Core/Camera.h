#pragma once
#include <string>

enum class CameraMode { FIRST_PERSON, THIRD_PERSON, FREE_EDITOR };

struct Vector3D {
    float x;
    float y;
    float z;
};

class NayderCameraSystem {
private:
    Vector3D position;
    float yaw;   // Horizontal rotation angle
    float pitch; // Vertical rotation angle
    CameraMode current_mode;

public:
    NayderCameraSystem();
    void SetCameraMode(CameraMode mode);
    void ProcessKeyboardInput(char key, float speed);
    void ProcessMouseLook(float delta_x, float delta_y);
    void RenderViewMatrix();
};
