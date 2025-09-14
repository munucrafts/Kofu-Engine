#include "Engine.h"
#include "iostream"

Engine& Engine::GetEngine()
{
    static Engine instance;
    return instance;
}

void Engine::InitEngine()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, "Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.24f, 0.45f, 0.37f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void Engine::RunEngine()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    }
}

void Engine::QuitEngine()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}