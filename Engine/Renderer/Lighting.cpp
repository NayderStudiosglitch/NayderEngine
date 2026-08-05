#include "Lighting.h"
#include <iostream>
#include <GLFW/glfw3.h>

typedef int (APIENTRY *PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar* name);
typedef void (APIENTRY *PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);

PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_p = nullptr;
PFNGLUNIFORM3FPROC          glUniform3f_p = nullptr;

void InitializeLightingGPUPointers() {
    glGetUniformLocation_p = (PFNGLGETUNIFORMLOCATIONPROC)glfwGetProcAddress("glGetUniformLocation");
    glUniform3f_p          = (PFNGLUNIFORM3FPROC)glfwGetProcAddress("glUniform3f");
}

NayderLightingRuntime::NayderLightingRuntime() {}

void NayderLightingRuntime::SetDirectionalSunUniforms(unsigned int shader_program_id, float dx, float dy, float dz, float r, float g, float b) {
    InitializeLightingGPUPointers();

    int lightDirLoc = glGetUniformLocation_p(shader_program_id, "lightDir");
    int lightColorLoc = glGetUniformLocation_p(shader_program_id, "lightColor");

    if (lightDirLoc != -1 && lightColorLoc != -1) {
        glUniform3f_p(lightDirLoc, dx, dy, dz);
        glUniform3f_p(lightColorLoc, r, g, b);
        std::cout << "\n☀️  [REAL LIGHTING SYSTEM ACTIVATED]:" << std::endl;
        std::cout << " -> Sun Direction Vector : (" << dx << ", " << dy << ", " << dz << ")" << std::endl;
        std::cout << " -> Illumination Color   : RGB(" << r << ", " << g << ", " << b << ")" << std::endl;
        std::cout << " -> STATUS               : ✅ Lighting state bounds updated inside shader registers!" << std::endl;
    }
}

void NayderLightingRuntime::UpdateCameraViewPositionUniform(unsigned int shader_program_id, float cx, float cy, float cz) {
    int viewPosLoc = glGetUniformLocation_p(shader_program_id, "viewPos");
    if (viewPosLoc != -1) {
        glUniform3f_p(viewPosLoc, cx, cy, cz);
    }
}
