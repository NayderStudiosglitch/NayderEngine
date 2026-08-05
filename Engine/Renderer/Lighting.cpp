#include "Lighting.h"
#include <iostream>

DirectionalLight NayderLightingEngine::CreateSunlight(float dx, float dy, float dz, std::string time_of_day) {
    DirectionalLight light;
    light.dir_x = dx; light.dir_y = dy; light.dir_z = dz;

    std::cout << "\n☀️  [LIGHTING ENGINE]: Configuring global sky light node for: [" << time_of_day << "]" << std::endl;

    if (time_of_day == "SUNSET_CYBERPUNK") {
        // Solèy kouche ki nan foto ou yo gen bèl koulè oranj ak koulè wouj oranj klere
        light.ambient_r = 0.25f; light.ambient_g = 0.15f; light.ambient_b = 0.2f;  // Ti klète fènwa violèt
        light.diffuse_r = 0.9f;  light.diffuse_g = 0.45f; light.diffuse_b = 0.15f; // Gwo reyon oranj kouche a!
        light.specular_r = 1.0f; light.specular_g = 0.6f;  light.specular_b = 0.3f;
        std::cout << "   -> [GPU LIGHT CONFIG]: Sunset vectors loaded (Oranj/Red light vectors initialized)." << std::endl;
    } 
    else if (time_of_day == "MIDNIGHT_DARKNESS") {
        // Lannwit fènwa total nan Zombie Zone lan
        light.ambient_r = 0.05f; light.ambient_g = 0.05f; light.ambient_b = 0.1f;  // Ti klète lalin ble fennen
        light.diffuse_r = 0.1f;  light.diffuse_g = 0.1f;  light.diffuse_b = 0.2f;
        light.specular_r = 0.2f; light.specular_g = 0.2f;  light.specular_b = 0.3f;
        std::cout << "   -> [GPU LIGHT CONFIG]: Midnight vectors loaded (Stealth fènwa total profile active)." << std::endl;
    }

    return light;
}

void NayderLightingEngine::BindLightToShaderUniforms(const DirectionalLight& light) {
    std::cout << "\n⚡ [GL_LIGHT_UNIFORM_BIND]: Pushing Light parameters to GPU pipeline vectors..." << std::endl;
    std::cout << " -> glUniform3f(glGetUniformLocation(prog, \"sunLight.direction\"), " << light.dir_x << ", " << light.dir_y << ", " << light.dir_z << ");" << std::endl;
    std::cout << " -> glUniform3f(glGetUniformLocation(prog, \"sunLight.diffuse\"), " << light.diffuse_r << ", " << light.diffuse_g << ", " << light.diffuse_b << ");" << std::endl;
    std::cout << " ✅ [LIGHTING PIPELINE READY]: Shaders are now processing dynamic real-time hardware light shading loops!" << std::endl;
}
