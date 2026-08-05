#include "Renderer.h"
#include <iostream>

typedef void (APIENTRY *PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint* arrays);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRY *PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
typedef void (APIENTRY *PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY *PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (APIENTRY *PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRY *PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

PFNGLGENVERTEXARRAYSPROC          glGenVertexArrays_p = nullptr;
PFNGLBINDVERTEXARRAYPROC          glBindVertexArray_p = nullptr;
PFNGLGENBUFFERSPROC               glGenBuffers_p = nullptr;
PFNGLBINDBUFFERPROC               glBindBuffer_p = nullptr;
PFNGLBUFFERDATAPROC               glBufferData_p = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray_p = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer_p = nullptr;

NayderOpenGLRenderer::NayderOpenGLRenderer() { window = nullptr; }

bool NayderOpenGLRenderer::InitializeWindowContext(int width, int height, std::string title) {
    screen_width = width; screen_height = height; window_title = title;
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screen_width, screen_height, window_title.c_str(), nullptr, nullptr);
    if (!window) { glfwTerminate(); return false; }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glGenVertexArrays_p         = (PFNGLGENVERTEXARRAYSPROC)glfwGetProcAddress("glGenVertexArrays");
    glBindVertexArray_p         = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    glGenBuffers_p              = (PFNGLGENBUFFERSPROC)glfwGetProcAddress("glGenBuffers");
    glBindBuffer_p              = (PFNGLBINDBUFFERPROC)glfwGetProcAddress("glBindBuffer");
    glBufferData_p              = (PFNGLBUFFERDATAPROC)glfwGetProcAddress("glBufferData");
    glEnableVertexAttribArray_p = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glfwGetProcAddress("glEnableVertexAttribArray");
    glVertexAttribPointer_p     = (PFNGLVERTEXATTRIBPOINTERPROC)glfwGetProcAddress("glVertexAttribPointer");

    return true;
}

void NayderOpenGLRenderer::SetupRealGraphicsPipeline() {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, screen_width, screen_height);
}

void NayderOpenGLRenderer::ClearScreenBuffer() {
    glClearColor(0.03f, 0.03f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void NayderOpenGLRenderer::HandleWindowPollEvents() { glfwPollEvents(); }
bool NayderOpenGLRenderer::ShouldWindowClose() { return glfwWindowShouldClose(window); }
void NayderOpenGLRenderer::SwapHardwareBuffers() { glfwSwapBuffers(window); }
void NayderOpenGLRenderer::TerminateGraphicsContext() { glfwDestroyWindow(window); glfwTerminate(); }
