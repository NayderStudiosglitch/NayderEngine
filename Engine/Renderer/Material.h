#pragma once
#include <string>

struct MaterialCoefficients {
    float ambient[3];  // R, G, B Ambient reflection
    float diffuse[3];  // R, G, B Diffuse reflection
    float specular[3]; // R, G, B Specular highlights
    float shininess;   // Kijan l ap briye (0.0 flat -> 128.0 metal solid)
};

struct Material {
    std::string material_name;
    unsigned int diffuse_texture_id;
    MaterialCoefficients properties;
};

class NayderMaterialSystem {
public:
    Material CreateCustomMaterial(std::string name, unsigned int tex_id, std::string template_preset);
    void ApplyMaterialToShader(const Material& mat);
};
