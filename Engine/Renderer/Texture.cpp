#include "Texture.h"
#include <iostream>

TextureData NayderTextureSystem::LoadTextureFromFile(std::string path) {
    TextureData new_texture;
    new_texture.file_path = path;
    
    std::cout << "\n🖼️  [TEXTURE ENGINE]: Loading texture image array from: \"" << path << "\" ..." << std::endl;
    std::cout << " -> Image Decoder: Decompressing pixel buffers into raw RGBA data..." << std::endl;

    // Simulate different asset configurations depending on file extension and purpose
    if (path.find(".png") != std::string::npos) {
        new_texture.width = 2048;
        new_texture.height = 2048;
        new_texture.has_alpha_channel = true; // Alpha transparency tracking loop
        std::cout << "   [FORMAT]: Detected 2K PNG with Alpha Channel. Unlocking transparency transparency passes." << std::endl;
    } else {
        new_texture.width = 1024;
        new_texture.height = 1024;
        new_texture.has_alpha_channel = false;
        std::cout << "   [FORMAT]: Detected 1K JPG Standard Color Map Profile." << std::endl;
    }

    std::cout << "   └── Resolution Matrix Decoded: " << new_texture.width << "x" << new_texture.height << " pixels." << std::endl;
    return new_texture;
}

void NayderTextureSystem::BindTextureToGPUUnit(const TextureData& texture, unsigned int slot_id) {
    std::cout << "\n🎮 [GL_TEXTURE_BIND]: Mapping Texture ID into active GPU texture state registers..." << std::endl;
    std::cout << " -> glActiveTexture(GL_TEXTURE0 + " << slot_id << ") allocated." << std::endl;
    
    // Simulating true hardware clamping and wrapping parameter controls
    std::cout << " -> glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);" << std::endl;
    std::cout << " -> glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);" << std::endl;
    
    std::cout << " ✅ [SAMPLER UNLOCKED]: Surface linked! Fragment Shaders can now sample textures from Unit " << slot_id << "." << std::endl;
}
