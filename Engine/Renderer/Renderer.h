#pragma once
#include <string>
#include <vector>

struct GLContext {
    std::string gl_version = "OpenGL 4.3 Core Profile";
    bool is_active = false;
    unsigned int active_vbo_id = 0;
};

struct ShaderProgram {
    std::string vertex_source;
    std::string fragment_source;
    bool compiled_successfully = false;
};

class NayderOpenGLRenderer {
private:
    GLContext hardware_context;
    ShaderProgram active_shaders;

public:
    NayderOpenGLRenderer();
    void CreateRenderWindow(int width, int height, std::string title);
    void CompileShaderPipeline(std::string vert_path, std::string frag_path);
    void SetCameraMatrixUniform(float cam_x, float cam_y, float cam_z);
    void DrawPrimitiveTriangle();
    void SwapFrameBuffers();
};
