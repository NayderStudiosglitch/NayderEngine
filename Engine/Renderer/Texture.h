#pragma once
#include <string>

struct TextureData {
    std::string file_path;
    int width = 0;
    int height = 0;
    unsigned int texture_gl_id = 0;
    bool has_alpha_channel = false; // Checks for true transparent backgrounds (.png)
};

class NayderTextureSystem {
public:
    TextureData LoadTextureFromFile(std::string path);
    void BindTextureToGPUUnit(const TextureData& texture, unsigned int slot_id);
};
