#pragma once
#include "Engine.h"
#include "iostream"
#include "geometry/GLTFLoader.h"
#include <glm/gtc/type_ptr.hpp>
#include "rendering/RenderTarget.h"
#include "geometry/ScreenQuad.h"

int Engine::windowWidth = 1024;
int Engine::windowHeight = 724;
bool Engine::windowResized = false;

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

    window = glfwCreateWindow(windowWidth, windowHeight, "Kofu Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();

    activeScene = std::make_unique<Scene>();
    activeScene->BeginScene(windowWidth, windowHeight);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glViewport(0, 0, windowWidth, windowHeight);

    engineInitialized = true;
}

void Engine::WindowResize(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    windowResized = true;
    glViewport(0, 0, windowWidth, windowHeight);
}

void Engine::RunEngine()
{
    float prevTime = 0.0f;
    float fpsTimer = 0.0f;
    int fps = 0;

    while (!glfwWindowShouldClose(window) && engineInitialized)
    {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - prevTime;
        prevTime = currentTime;
        fpsTimer += deltaTime;
        fps++;

        if (fpsTimer >= 1.0f)
        {
            std::string statLine = "Kofu Engine [ " + std::to_string(fps) + " FPS | " + std::to_string(deltaTime * 1000.0f) + " ms ]";
            glfwSetWindowTitle(window, statLine.c_str());
            fps = 0;
            fpsTimer = 0.0f;
        }

        activeScene->RenderScene(windowWidth, windowHeight, windowResized, deltaTime);
        windowResized = false;

        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwSetFramebufferSizeCallback(window, WindowResize);
    }
}

void Engine::QuitEngine()
{
    activeScene->EndScene();
    glfwDestroyWindow(window);
    glfwTerminate();
}

float Engine::GetAspectRatio()
{
    return ((float)windowWidth/windowHeight);
}

void Engine::ClearWindow()
{
    glClearColor(0.38f, 0.67f, 0.94f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}
