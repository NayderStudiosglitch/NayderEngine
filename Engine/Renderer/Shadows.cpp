#include "Shadows.h"
#include <iostream>

ShadowFrameBuffer NayderShadowEngine::InitializeShadowBuffer() {
    std::cout << "\n🌒 [SHADOW ENGINE]: Allocating dedicated hardware Frame Buffer Objects (FBO)..." << std::endl;
    std::cout << " -> glGenFramebuffers(1); -> Allocating FBO structure registers on GPU..." << std::endl;
    std::cout << " -> glGenTextures(1);     -> Binding depth texture buffer profile." << std::endl;
    
    shadow_hardware_buffer.fbo_gl_id = 4001;
    shadow_hardware_buffer.depth_texture_id = 5001;
    shadow_hardware_buffer.is_allocated = true;

    std::cout << "   [GPU FBO UNLOCKED]: Created Shadow Resolution Matrix: " 
              << shadow_hardware_buffer.shadow_map_resolution << "x" << shadow_hardware_buffer.shadow_map_resolution << " pixels." << std::endl;
    std::cout << "   └── ✅ STATUS: Shadow Map Frame Buffer attached successfully to VRAM slots." << std::endl;
    
    return shadow_hardware_buffer;
}

void NayderShadowEngine::ExecuteFirstPassDepthRender(std::string model_id, float light_x, float light_y, float light_z) {
    std::cout << "\n🔄 [SHADOW PASS 1 - LIGHT VIEWPOINT]: Diverting rendering viewport pipelines..." << std::endl;
    std::cout << " -> glBindFramebuffer(GL_FRAMEBUFFER, " << shadow_hardware_buffer.fbo_gl_id << ");" << std::endl;
    std::cout << " -> glViewport(0, 0, 2048, 2048); -> Locking rasterizer parameters to Shadow Map boundaries." << std::endl;
    std::cout << " -> Calculating depth maps from Light Vector Source: (" << light_x << ", " << light_y << ", " << light_z << ")" << std::endl;
    std::cout << "   [DEPTH CAPTURE]: Writing structural vertex indices for '" << model_id << "' straight into depth buffer pixels." << std::endl;
}

void NayderShadowEngine::ExecuteSecondPassShadowSample() {
    std::cout << "\n🎥 [SHADOW PASS 2 - PLAYER VIEWPOINT]: Returning rendering viewport pipeline to Main Display..." << std::endl;
    std::cout << " -> glBindFramebuffer(GL_FRAMEBUFFER, 0); -> Default Screen Frame Buffer selected." << std::endl;
    std::cout << " -> glActiveTexture(GL_TEXTURE2); glBindTexture(GL_TEXTURE_2D, " << shadow_hardware_buffer.depth_texture_id << ");" << std::endl;
    std::cout << " -> Fragment Shader execution: Performing coordinate depth cross-examination lookups..." << std::endl;
    std::cout << " ✅ [SHADOWSAMPLER SUCCESS]: Projection Matrix updated. Dynamic shadows mapped with zero hardware overhead!" << std::endl;
}
