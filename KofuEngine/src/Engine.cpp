#pragma once
#include "Engine.h"
#include "iostream"
#include <glm/gtc/type_ptr.hpp>
#include "geometry/GLTFLoader.h"
#include "rendering/RenderTarget.h"
#include "geometry/Quad.h"
#include "stats/StatsHelper.h"

int Engine::windowWidth = 1024;
int Engine::windowHeight = 720;

constexpr char engineName[12] = "Kofu Engine";
constexpr int OGLMajor = 4;
constexpr int OGLMinor = 6;

Engine& Engine::GetEngine()
{
    static Engine instance;
    return instance;
}

void Engine::InitEngine()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OGLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OGLMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, engineName, nullptr, nullptr);

    GLFWimage images[1];
    images[0].pixels = stbi_load("assets/others/Icon.png", &images[0].width, &images[0].height, 0, 4);
    if (images[0].pixels)
    {
        glfwSetWindowIcon(window, 1, images);
        stbi_image_free(images[0].pixels);
    }

    glfwMakeContextCurrent(window);
    EnableVSync(true);
    gladLoadGL();

    activeScene = std::make_unique<Scene>();
    activeScene->BeginScene();

    engineInitialized = true;

    std::cout << "Kofu Engine Initialized." << std::endl;
}

void Engine::WindowResize(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
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
            glfwSetWindowTitle(window, engineName);
            StatsHelper::GetStatsHelper().FPS = fps;
            StatsHelper::GetStatsHelper().deltaSecs = deltaTime;
            fps = 0;
            fpsTimer = 0.0f;
        }

        activeScene->RenderScene(deltaTime);

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

    std::cout << "Kofu Engine Terminated." << std::endl;
}

void Engine::ClearWindow(const unsigned int width, const unsigned height, const glm::vec4& clearColor)
{
    glViewport(0, 0, width, height);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

float Engine::GetWindowAspectRatio()
{
    return ((float)windowWidth/windowHeight);
}

std::string Engine::GetOGLVersionText()
{
    return ("#version " + std::to_string(OGLMajor) + std::to_string(OGLMinor) + "0 core");
}

void Engine::EnableVSync(bool enable)
{
    glfwSwapInterval(enable);
}
