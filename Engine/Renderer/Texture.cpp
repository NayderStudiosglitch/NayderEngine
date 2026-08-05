#include "Texture.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <GLFW/glfw3.h>

// Declare modern texture mapping function pointers natively
typedef void (APIENTRY *PFNGLACTIVETEXTUREPROC) (GLenum texture);
PFNGLACTIVETEXTUREPROC glActiveTexture_p = nullptr;

NayderTextureRuntime::NayderTextureRuntime() {
    TextureID = 0;
}

bool NayderTextureRuntime::LoadRealBMPTexture(const std::string& file_path) {
    glActiveTexture_p = (PFNGLACTIVETEXTUREPROC)glfwGetProcAddress("glActiveTexture");

    // 1. Open loose raw image data array blocks from local workspace disk
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        std::cerr << " 🚫 [TEXTURE FILE ERROR]: Cannot open image path: \"" << file_path << "\"" << std::endl;
        return false;
    }

    unsigned char header[54];
    file.read((char*)header, 54); // Parse standard 54-byte BMP header
    if (header[0] != 'B' || header[1] != 'M') {
        std::cerr << " 🚫 [FORMAT ERROR]: Invallid BMP texture format file constraint match!" << std::endl;
        return false;
    }

    // Extract dimension data directly from raw byte tokens
    int width = *(int*)&(header[18]);
    int height = *(int*)&(header[22]);
    int dataOffset = *(int*)&(header[10]);

    std::vector<unsigned char> data(width * height * 3);
    file.seekg(dataOffset);
    file.read((char*)data.data(), data.size());
    file.close();

    // 2. Generate and upload pixel arrays directly onto hardware VRAM channels
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    // Apply strict filtering parameters directly over driver context states
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Pass the raw RGB pointer straight to the hardware driver allocation routines
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data.data());

    std::cout << "\n🖼️  [REAL TEXTURE ENGINE ACTIVE]:" << std::endl;
    std::cout << " -> Image Decoded  : \"" << file_path << "\" | Dimensions: " << width << "x" << height << " pixels." << std::endl;
    std::cout << " -> STATUS         : ✅ Texture ID (" << TextureID << ") bound into active GPU sampling caches!" << std::endl;

    return true;
}

void NayderTextureRuntime::BindTextureUnit(unsigned int slot_id) {
    if (glActiveTexture_p && TextureID != 0) {
        glActiveTexture_p(0x84C0 + slot_id); // GL_TEXTURE0 + slot_id
        glBindTexture(GL_TEXTURE_2D, TextureID);
    }
}
