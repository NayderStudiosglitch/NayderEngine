#pragma once
#include <string>

class NayderLightingRuntime {
public:
    NayderLightingRuntime();
    void SetDirectionalSunUniforms(unsigned int shader_program_id, float dx, float dy, float dz, float r, float g, float b);
    void UpdateCameraViewPositionUniform(unsigned int shader_program_id, float cx, float cy, float cz);
};
