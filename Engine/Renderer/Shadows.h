#pragma once
#include <string>

struct ShadowFrameBuffer {
    unsigned int fbo_gl_id = 0;
    unsigned int depth_texture_id = 0;
    int shadow_map_resolution = 2048; // Crisp 2K Next-Gen Shadow Resolution
    bool is_allocated = false;
};

class NayderShadowEngine {
private:
    ShadowFrameBuffer shadow_hardware_buffer;

public:
    ShadowFrameBuffer InitializeShadowBuffer();
    void ExecuteFirstPassDepthRender(std::string model_id, float light_x, float light_y, float light_z);
    void ExecuteSecondPassShadowSample();
};
