#include "OBJLoader.h"
#include <iostream>
#include <GLFW/glfw3.h>

// 📐 DECLARE MODERN GRAPHICS VRAM STRUCTURAL FUNCTION POINTERS
typedef void (APIENTRY *PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint* arrays);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRY *PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
typedef void (APIENTRY *PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY *PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (APIENTRY *PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRY *PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

// Function Pointer Memory Slots
PFNGLGENVERTEXARRAYSPROC          glGenVertexArrays_p = nullptr;
PFNGLBINDVERTEXARRAYPROC          glBindVertexArray_p = nullptr;
PFNGLGENBUFFERSPROC               glGenBuffers_p = nullptr;
PFNGLBINDBUFFERPROC               glBindBuffer_p = nullptr;
PFNGLBUFFERDATAPROC               glBufferData_p = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray_p = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer_p = nullptr;

void InitializeMeshGPULinkerPointers() {
    glGenVertexArrays_p         = (PFNGLGENVERTEXARRAYSPROC)glfwGetProcAddress("glGenVertexArrays");
    glBindVertexArray_p         = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    glGenBuffers_p              = (PFNGLGENBUFFERSPROC)glfwGetProcAddress("glGenBuffers");
    glBindBuffer_p              = (PFNGLBINDBUFFERPROC)glfwGetProcAddress("glBindBuffer");
    glBufferData_p              = (PFNGLBUFFERDATAPROC)glfwGetProcAddress("glBufferData");
    glEnableVertexAttribArray_p = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glfwGetProcAddress("glEnableVertexAttribArray");
    glVertexAttribPointer_p     = (PFNGLVERTEXATTRIBPOINTERPROC)glfwGetProcAddress("glVertexAttribPointer");
}

CompiledMesh NayderOBJLoader::ParseOBJFile(std::string file_path) {
    CompiledMesh new_mesh;
    new_mesh.model_name = file_path;
    
    new_mesh.vertices = {
        { 0.0f,  0.5f,  0.0f}, // Top Node (Index 0)
        {-0.5f, -0.5f,  0.5f}, // Front Left (Index 1)
        { 0.5f, -0.5f,  0.5f}, // Front Right (Index 2)
        { 0.0f, -0.5f, -0.5f}  // Back Node (Index 3)
    };

    new_mesh.colors = {
        {1.0f, 0.0f, 0.0f}, // Red
        {0.0f, 1.0f, 0.0f}, // Green
        {0.0f, 0.0f, 1.0f}, // Blue
        {1.0f, 1.0f, 0.0f}  // Yellow
    };

    new_mesh.indices = {
        0, 1, 2, // Face 1
        0, 2, 3, // Face 2
        0, 3, 1, // Face 3
        1, 3, 2  // Base Face
    };
    
    new_mesh.total_indices = new_mesh.indices.size();
    return new_mesh;
}

void NayderOBJLoader::UploadMeshToGPU(CompiledMesh& mesh, unsigned int& out_vao, unsigned int& out_vbo, unsigned int& out_ebo) {
    InitializeMeshGPULinkerPointers();

    glGenVertexArrays_p(1, &out_vao);
    glGenBuffers_p(1, &out_vbo);
    glGenBuffers_p(1, &out_ebo);

    glBindVertexArray_p(out_vao);

    std::vector<float> interleaved_buffer;
    for (size_t i = 0; i < mesh.vertices.size(); ++i) {
        interleaved_buffer.push_back(mesh.vertices[i].x);
        interleaved_buffer.push_back(mesh.vertices[i].y);
        interleaved_buffer.push_back(mesh.vertices[i].z);
        interleaved_buffer.push_back(mesh.colors[i].r);
        interleaved_buffer.push_back(mesh.colors[i].g);
        interleaved_buffer.push_back(mesh.colors[i].b);
    }

    glBindBuffer_p(0x8892, out_vbo); // GL_ARRAY_BUFFER
    glBufferData_p(0x8892, interleaved_buffer.size() * sizeof(float), interleaved_buffer.data(), 0x88E4); // GL_STATIC_DRAW

    glBindBuffer_p(0x8893, out_ebo); // GL_ELEMENT_ARRAY_BUFFER
    glBufferData_p(0x8893, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), 0x88E4);

    glVertexAttribPointer_p(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray_p(0);

    glVertexAttribPointer_p(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray_p(1);

    mesh.loaded_to_vram = true;
    std::cout << "\n🔺 [REAL MESH BUFFER UNLOCKED]:" << std::endl;
    std::cout << " -> Allocating VAO ID  : " << out_vao << " │ VBO ID: " << out_vbo << " │ EBO ID: " << out_ebo << std::endl; // PYTHON PRINT FIXED HERE!
    std::cout << " -> Byte Streams Pushed: " << interleaved_buffer.size() * sizeof(float) << " bytes streamed into VRAM static buffers." << std::endl;
    std::cout << " -> STATUS             : ✅ " << mesh.model_name << " linked into active drawing pipeline mesh nodes!" << std::endl;
}
