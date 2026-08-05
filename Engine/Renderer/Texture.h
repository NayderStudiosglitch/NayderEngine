#pragma once
#include <string>

class NayderTextureRuntime {
public:
    unsigned int TextureID;

    NayderTextureRuntime();
    bool LoadRealBMPTexture(const std::string& file_path);
    void BindTextureUnit(unsigned int slot_id);
};
