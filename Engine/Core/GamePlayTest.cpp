#include "../World/WorldRenderer.h"

#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <iostream>

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!\n";
        return -1;
    }

    GLFWwindow* window =
        glfwCreateWindow(
            1366,
            768,
            "Nayder Engine v0.3.1 - Gameplay Test",
            nullptr,
            nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);

    WorldRenderer world;

    world.Initialize();

    while (!glfwWindowShouldClose(window))
    {
        glViewport(0,0,1366,768);

        world.Render();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}

