#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "Input.cpp"
#include "GameLoop.cpp"
#include <iostream>
#include <vector>
#include <cmath>

// 📐 MATEMATIK MATRIS C++ POU PWOJEKSYON PÈSPEKTIV REYÈL (FOV, Aspect Ratio, Near, Far)
void MakePerspectiveMatrix(float fov_degrees, float aspect, float near_plane, float far_plane, float* m) {
    float radians = fov_degrees * (3.14159265f / 180.0f);
    float f = 1.0f / std::tan(radians / 2.0f);
    for (int i = 0; i < 16; ++i) m[i] = 0.0f;
    m[0] = f / aspect;
    m[5] = f;
    m[10] = (far_plane + near_plane) / (near_plane - far_plane);
    m[11] = -1.0f;
    m[14] = (2.0f * far_plane * near_plane) / (near_plane - far_plane);
}

// 🎥 MATEMATIK POU VRÈ KAMERA FIRST-PERSON (View Matrix transform)
void MakeViewMatrix(float px, float py, float pz, float yaw_deg, float pitch_deg, float* m) {
    float rad_yaw = yaw_deg * (3.14159265f / 180.0f);
    float rad_pitch = pitch_deg * (3.14159265f / 180.0f);

    float cosPitch = std::cos(rad_pitch);
    float sinPitch = std::sin(rad_pitch);
    float cosYaw = std::cos(rad_yaw);
    float sinYaw = std::sin(rad_yaw);

    float xaxis[3] = { cosYaw, 0.0f, -sinYaw };
    float yaxis[3] = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
    float zaxis[3] = { sinYaw * cosPitch, -sinPitch, cosYaw * cosPitch };

    m[0] = xaxis[0]; m[4] = xaxis[1]; m[8] = xaxis[2]; m[12] = -(xaxis[0]*px + xaxis[1]*py + xaxis[2]*pz);
    m[1] = yaxis[0]; m[5] = yaxis[1]; m[9] = yaxis[2]; m[13] = -(yaxis[0]*px + yaxis[1]*py + yaxis[2]*pz);
    m[2] = zaxis[0]; m[6] = zaxis[1]; m[10] = zaxis[2]; m[14] = -(zaxis[0]*px + zaxis[1]*py + zaxis[2]*pz);
    m[3] = 0.0f;     m[7] = 0.0f;     m[11] = 0.0f;     m[15] = 1.0f;
}

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "  👑 [NAYDER ENGINE v0.3.1] - FIRST REAL 3D WORLD VIEW" << std::endl;
    std::cout << "=======================================================" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderOBJLoader obj_loader;
    NayderGameLoopClock engine_clock(107.0);

    // Louvri fenèt 1366x768 la
    if (!engine_runtime.InitializeWindowContext(1366, 768, "Nayder Engine - Real 3D World View v0.3.1")) {
        return -1;
    }

    GLFWwindow* active_window = glfwGetCurrentContext();
    input_engine.ConfigureInputCallbacks(active_window);
    
    // Bloke sourit la nan mitan fenèt la pou vrè kontwòl FPS 360 kamera deteksyon
    glfwSetInputMode(active_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    engine_runtime.SetupRealGraphicsPipeline();

    // 🏔️ KREYE KÒD JWÈMETRI POU YON GWO TERRAIN PLAT AK MÒN DIRÈK (v0.3.1 Ground)
    CompiledMesh terrain_mesh;
    terrain_mesh.model_name = "Real_Terrain_Grid";
    int grid_size = 50;
    float spacing = 2.0f;
    for (int z = 0; z < grid_size; ++z) {
        for (int x = 0; x < grid_size; ++x) {
            float tx = (x - grid_size / 2.0f) * spacing;
            float tz = (z - grid_size / 2.0f) * spacing;
            
            // Ondulasyon mòn yo nan background nan
            float dist = std::sqrt(tx*tx + tz*tz);
            float ty = -1.5f; // Tè plat nan mitan an pou lari a
            if (dist > 15.0f) {
                ty = (std::sin(tx * 0.2f) * std::cos(tz * 0.2f) * 3.0f) - 1.0f; // Mòn nan perimeter a
            }
            terrain_mesh.vertices.push_back({tx, ty, tz});
            
            // Koulè vèt/mawon pou mòn ak plèn Desert Ghost City a parèt klè
            if (ty < -1.2f) terrain_mesh.colors.push_back({0.2f, 0.4f, 0.2f}); // Plèn vèt fènwa
            else terrain_mesh.colors.push_back({0.5f, 0.4f, 0.3f}); // Mòn jòn/mawon desè
        }
    }
    for (int z = 0; z < grid_size - 1; ++z) {
        for (int x = 0; x < grid_size - 1; ++x) {
            unsigned int i0 = z * grid_size + x;
            unsigned int i1 = i0 + 1;
            unsigned int i2 = (z + 1) * grid_size + x;
            unsigned int i3 = i2 + 1;
            terrain_mesh.indices.push_back(i0); terrain_mesh.indices.push_back(i1); terrain_mesh.indices.push_back(i2);
            terrain_mesh.indices.push_back(i1); terrain_mesh.indices.push_back(i3); terrain_mesh.indices.push_back(i2);
        }
    }
    terrain_mesh.total_indices = terrain_mesh.indices.size();

    // 🧟 KREYE KÒD JWÈMETRI MODÈL SOLDIER / ZOMBIE POU YO PARÈT AN 3D (Cubes)
    CompiledMesh zombie_mesh;
    zombie_mesh.model_name = "Zombie_Box_Mesh";
    zombie_mesh.vertices = {
        {-0.5f, -1.0f,  0.5f}, { 0.5f, -1.0f,  0.5f}, { 0.5f,  1.0f,  0.5f}, {-0.5f,  1.0f,  0.5f},
        {-0.5f, -1.0f, -0.5f}, { 0.5f, -1.0f, -0.5f}, { 0.5f,  1.0f, -0.5f}, {-0.5f,  1.0f, -0.5f}
    };
    for (int i = 0; i < 8; ++i) zombie_mesh.colors.push_back({1.0f, 0.0f, 0.0f}); // Koulè Wouj klere pou Zonbi
    zombie_mesh.indices = {
        0, 1, 2, 2, 3, 0,  4, 5, 6, 6, 7, 4,  0, 3, 7, 7, 4, 0,  1, 5, 6, 6, 2, 1,  3, 2, 6, 6, 7, 3,  0, 1, 5, 5, 4, 0
    };
    zombie_mesh.total_indices = zombie_mesh.indices.size();

    // Chaje yo de (2) a nan VRAM kat grafik la
    unsigned int tVAO, tVBO, tEBO;
    obj_loader.UploadMeshToGPU(terrain_mesh, tVAO, tVBO, tEBO);
    unsigned int zVAO, zVBO, zEBO;
    obj_loader.UploadMeshToGPU(zombie_mesh, zVAO, zVBO, zEBO);

    // Kowòdone inisyal Kamera FPS la (Mete l anlè tè a byen kòrèk!)
    float cam_x = 0.0f, cam_y = 1.5f, cam_z = 5.0f;
    float yaw = -90.0f, pitch = 0.0f;

    float proj_matrix[16];
    float view_matrix[16];
    MakePerspectiveMatrix(45.0f, 1366.0f / 768.0f, 0.1f, 100.0f, proj_matrix);

    std::cout << "\n🚀 [REAL 3D RUNTIME ONLINE]: Move mouse to look, WASD to walk over terrain nodes!" << std::endl;

    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // 1. KOUTE SOURiT LAN NAN NIVO OS POU VRÈ CONTWÒL 360 DEGREE
        NayderInputSystem::GetCameraOrientation(yaw, pitch);

        // 2. KALKiLE DEPLASMAN KAMERA FPS SE-LON ANG SOURiT LAN (WASD matrix steps)
        float rad_yaw = yaw * (3.14159265f / 180.0f);
        float forward_x = std::cos(rad_yaw); float forward_z = std::sin(rad_yaw);
        float right_x = -std::sin(rad_yaw);  float right_z = std::cos(rad_yaw);
        float move_speed = 4.0f * dt;

        if (NayderInputSystem::key_states[GLFW_KEY_W]) { cam_x += forward_x * move_speed; cam_z += forward_z * move_speed; }
        if (NayderInputSystem::key_states[GLFW_KEY_S]) { cam_x -= forward_x * move_speed; cam_z -= forward_z * move_speed; }
        if (NayderInputSystem::key_states[GLFW_KEY_A]) { cam_x -= right_x * move_speed;  cam_z -= right_z * move_speed; }
        if (NayderInputSystem::key_states[GLFW_KEY_D]) { cam_x += right_x * move_speed;  cam_z += right_z * move_speed; }

        // Netwaye ekran an epi mete yon bèl KOULÈ SYÈL BLE KLiRE (Sky Color v0.3.1)
        glClearColor(0.4f, 0.6f, 0.9f, 1.0f); // Bright blue sky background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Aktive lojik matris pwojeksyon yo nan kat grafik la
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(proj_matrix);

        // Kalkile vrè matris View a chak frame selon kote ou gade a
        MakeViewMatrix(cam_x, cam_y, cam_z, yaw, pitch, view_matrix);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(view_matrix);

        // 3. DESiNE VRÈ MOND TERRAIN AN 3D (Real Terrain rendering pass)
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        
        // Pouse pwen tè yo
        PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
        if (glBindVertexArray_ptr) glBindVertexArray_ptr(tVAO);
        glDrawElements(GL_TRIANGLES, terrain_mesh.total_indices, GL_UNSIGNED_INT, 0);

        // 4. DESiNE MODÈL ZOMBIE / SOLDIER YO NAN MITAN SÈN NAN (3D Entities pass)
        // Zonbi 1 plase nan kowòdone (X: 2.0, Z: -5.0)
        glPushMatrix();
        glTranslatef(2.0f, 0.0f, -5.0f);
        if (glBindVertexArray_ptr) glBindVertexArray_ptr(zVAO);
        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);
        glPopMatrix();

        // Zonbi 2 plase nan kowòdone (X: -3.0, Z: -8.0)
        glPushMatrix();
        glTranslatef(-3.0f, 0.0f, -8.0f);
        if (glBindVertexArray_ptr) glBindVertexArray_ptr(zVAO);
        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);
        glPopMatrix();

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        engine_runtime.SwapHardwareBuffers();
        engine_clock.SynchronizeFrameRateLock();
        engine_runtime.HandleWindowPollEvents();
    }

    engine_runtime.TerminateGraphicsContext();
    return 0;
}
