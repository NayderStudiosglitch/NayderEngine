#pragma once
#include <string>

struct DirectionalLight {
    float dir_x, dir_y, dir_z; // Vektè direksyon reyon solèy la
    float ambient_r, ambient_g, ambient_b; // Koulè limyè anbyant la
    float diffuse_r, diffuse_g, diffuse_b; // Koulè limyè dirèk la
    float specular_r, specular_g, specular_b; // Koulè refleksyon briye a
};

class NayderLightingEngine {
public:
    DirectionalLight CreateSunlight(float dx, float dy, float dz, std::string time_of_day);
    void BindLightToShaderUniforms(const DirectionalLight& light);
};
