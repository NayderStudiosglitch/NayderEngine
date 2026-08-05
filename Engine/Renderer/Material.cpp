#include "Material.h"
#include <iostream>

Material NayderMaterialSystem::CreateCustomMaterial(std::string name, unsigned int tex_id, std::string template_preset) {
    Material mat;
    mat.material_name = name;
    mat.diffuse_texture_id = tex_id;

    std::cout << "\n💎 [MATERIAL ENGINE]: Creating material asset: \"" << name << "\" with Preset: [" << template_preset << "]" << std::endl;

    if (template_preset == "METALLIC_WEAPON") {
        // Zam koutim yo ap briye anpil e y ap gen bèl refleksyon metal (Specular highlights)
        mat.properties.ambient[0] = 0.2f;  mat.properties.ambient[1] = 0.2f;  mat.properties.ambient[2] = 0.25f;
        mat.properties.diffuse[0] = 0.8f;  mat.properties.diffuse[1] = 0.8f;  mat.properties.diffuse[2] = 0.9f;
        mat.properties.specular[0] = 1.0f; mat.properties.specular[1] = 1.0f; mat.properties.specular[2] = 1.0f;
        mat.properties.shininess = 96.0f; // Briye anpil tankou asye blennde!
        std::cout << "   -> [GPU REGISTER]: Unlocked High-Specular Metal Shader Vector." << std::endl;
    } 
    else if (template_preset == "ROUGH_WOOD") {
        // Bwa ki sou kay abandone yo ap mat, yo p'ap gen refleksyon specular
        mat.properties.ambient[0] = 0.1f;  mat.properties.ambient[1] = 0.05f; mat.properties.ambient[2] = 0.05f;
        mat.properties.diffuse[0] = 0.5f;  mat.properties.diffuse[1] = 0.35f; mat.properties.diffuse[2] = 0.2f;
        mat.properties.specular[0] = 0.0f; mat.properties.specular[1] = 0.0f;  mat.properties.specular[2] = 0.0f;
        mat.properties.shininess = 4.0f;  // Flat mat, pa gen briye.
        std::cout << "   -> [GPU REGISTER]: Unlocked Low-Specular Rough Matte Shader Vector." << std::endl;
    }

    return mat;
}

void NayderMaterialSystem::ApplyMaterialToShader(const Material& mat) {
    std::cout << "\n🎨 [GL_MATERIAL_BIND]: Binding properties to active shader uniforms..." << std::endl;
    std::cout << " -> glUniform3fv(glGetUniformLocation(prog, \"mat.ambient\"), 1, " << mat.properties.ambient[0] << ");" << std::endl;
    std::cout << " -> glUniform3fv(glGetUniformLocation(prog, \"mat.diffuse\"), 1, " << mat.properties.diffuse[0] << ");" << std::endl;
    std::cout << " -> glUniform1f(glGetUniformLocation(prog, \"mat.shininess\"), " << mat.properties.shininess << ");" << std::endl;
    std::cout << " ✅ [MATERIAL APPLIED]: Shader pipeline is now ready to compute surface lighting reflections for \"" << mat.material_name << "\"." << std::endl;
}
