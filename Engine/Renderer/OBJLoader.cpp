#include "OBJLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GLFW/glfw3.h>
#include <cmath>

typedef void (APIENTRY *PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint* arrays);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRY *PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
typedef void (APIENTRY *PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY *PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (APIENTRY *PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRY *PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

extern PFNGLGENVERTEXARRAYSPROC          glGenVertexArrays_p;
extern PFNGLBINDVERTEXARRAYPROC          glBindVertexArray_p;
extern PFNGLGENBUFFERSPROC               glGenBuffers_p;
extern PFNGLBINDBUFFERPROC               glBindBuffer_p;
extern PFNGLBUFFERDATAPROC               glBufferData_p;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray_p;
extern PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer_p;

CompiledMesh NayderOBJLoader::ParseOBJFile(std::string file_path) {
    CompiledMesh new_mesh;
    new_mesh.model_name = file_path;

    // 🏔️ SI SE TERRAIN LA, N AP KREYE YON VRÈ MOND 3D AK MÒN AK FON DIRÈK AN KÒD!
    if (file_path.find("terrain.obj") != std::string::npos) {
        int grid_size = 40;
        float spacing = 1.0f;
        unsigned int index_counter = 0;

        for (int z = 0; z < grid_size; ++z) {
            for (int x = 0; x < grid_size; ++x) {
                float px = (x - grid_size / 2.0f) * spacing;
                float pz = (z - grid_size / 2.0f) * spacing;
                
                // Matematik pou bati vrè ondulasyon mòn yo (Heightmap equations)
                float dist = std::sqrt(px*px + pz*pz);
                float py = -1.0f;
                if (dist < 15.0f) {
                    py = (std::sin(px * 0.4f) * std::cos(pz * 0.4f) * 2.0f) - 0.5f; // Mòn 3D ondulé!
                }

                new_mesh.vertices.push_back({px, py, pz});

                // Koulè Neon Green/Blue pou mòn yo parèt byen bèl
                float green_shade = (py + 1.5f) / 3.0f;
                if (green_shade > 1.0f) green_shade = 1.0f;
                new_mesh.colors.push_back({0.0f, green_shade, 1.0f - green_shade});
            }
        }

        // Bati Matris Triyang yo pou kat grafik la ka desine yo
        for (int z = 0; z < grid_size - 1; ++z) {
            for (int x = 0; x < grid_size - 1; ++x) {
                unsigned int i0 = z * grid_size + x;
                unsigned int i1 = i0 + 1;
                unsigned int i2 = (z + 1) * grid_size + x;
                unsigned int i3 = i2 + 1;

                new_mesh.indices.push_back(i0);
                new_mesh.indices.push_back(i1);
                new_mesh.indices.push_back(i2);

                new_mesh.indices.push_back(i1);
                new_mesh.indices.push_back(i3);
                new_mesh.indices.push_back(i2);
            }
        }
    } 
    // 🧟 SI SE ZOMBIE A, N AP KREYE YON KIB TACTICAL POU KORÈK MODÈL LA
    else {
        new_mesh.vertices = {
            {-0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},
            {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f}
        };
        for(int i=0; i<8; ++i) new_mesh.colors.push_back({1.0f, 0.2f, 0.2f}); // Koulè wouj pou Zonbi
        new_mesh.indices = {
            0, 1, 2, 2, 3, 0,  4, 5, 6, 6, 7, 4,
            0, 3, 7, 7, 4, 0,  1, 5, 6, 6, 2, 1
        };
    }

    new_mesh.total_indices = new_mesh.indices.size();
    return new_mesh;
}

void NayderOBJLoader::UploadMeshToGPU(CompiledMesh& mesh, unsigned int& out_vao, unsigned int& out_vbo, unsigned int& out_ebo) {
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

    glBindBuffer_p(0x8892, out_vbo);
    glBufferData_p(0x8892, interleaved_buffer.size() * sizeof(float), interleaved_buffer.data(), 0x88E4);

    glBindBuffer_p(0x8893, out_ebo);
    glBufferData_p(0x8893, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), 0x88E4);

    glVertexAttribPointer_p(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray_p(0);

    glVertexAttribPointer_p(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray_p(1);

    mesh.loaded_to_vram = true;
    std::cout << " ✅ [VRAM INJECTION]: Uploaded " << mesh.model_name << " with " << mesh.total_indices << " indices to GPU memory." << std::endl;
}
