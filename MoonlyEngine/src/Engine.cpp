#pragma once
#include "Engine.h"
#include "iostream"
#include "GLTFLoader.h"
#include <glm/gtc/type_ptr.hpp>
#include "RenderTarget.h"
#include "../ScreenQuad.h"

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

    window = glfwCreateWindow(windowWidth, windowHeight, "Moonly Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();

    shaders.emplace("default", Shader("./shaders/default.vert", "./shaders/default.frag"));
    shaders.emplace("skyBox", Shader("./shaders/skyBox.vert", "./shaders/skyBox.frag"));
    shaders.emplace("screen", Shader("./shaders/screen.vert", "./shaders/screen.frag"));
    shaders.emplace("light", Shader("./shaders/light.vert", "./shaders/light.frag"));

    renderMode = LIT;
    playerCamera.location = glm::vec3(0.0f, 6.0f, 25.0f);

    activeScene.modelPaths.push_back("./assets/models/medieval.gltf");
    activeScene.modelPaths.push_back("./assets/models/Lantern.gltf");
    activeScene.LoadScene();

    Light* light = new Light(glm::vec4(1.0f), glm::vec3(10.0f, -2.0f, 0.0f), DIRECTIONAL_LIGHT);
    activeScene.lights.emplace_back(light);

    for (Mesh* mesh : activeScene.meshes)
    {
        mesh->transform.location = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->transform.scale = glm::vec3(10.0f);
        mesh->InitMesh();
    }

    for (Light* light : activeScene.lights)
    {
        light->Init();
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glViewport(0, 0, windowWidth, windowHeight);

    engineInitialized = true;
}

void Engine::RunEngine()
{
    float prevTime = 0.0f, currentTime = 0.0f, timeDiff = 0.0f;
    int counter = 0;

    Skybox skyBox;
    skyBox.LoadSkybox();
    ScreenQuad screenQuad;
    screenQuad.Init();
    FBO msaaSceneFBO = RenderTarget::CreateMSAATarget(windowWidth, windowHeight, 8);
    FBO ppFBO = RenderTarget::CreateSceneTarget(windowWidth, windowHeight);

    while (!glfwWindowShouldClose(window) && engineInitialized)
    {
        currentTime = (float)glfwGetTime();
        timeDiff = currentTime - prevTime;
        counter++;

        if (timeDiff >= 1.0f / 30.0f)
        {
            std::string FPS = std::to_string((int)(1.0f / timeDiff) * counter);
            std::string statLine = "Moonly Engine [ FPS : " + FPS + " ]";
            glfwSetWindowTitle(window, statLine.c_str());
            prevTime = currentTime;
            counter = 0;
        }

        msaaSceneFBO.Bind();

        ClearWindow();

        shaders.at("light").Activate();
        playerCamera.ApplyCamMatrix();

        for (Light* light : activeScene.lights)
        {
            light->DrawLightMesh();
        }

        shaders.at("default").Activate();

        glUniform1f(glGetUniformLocation(activeShaderProgram, "nearClip"), nearClip);
        glUniform1f(glGetUniformLocation(activeShaderProgram, "farClip"), farClip);
        glUniform1i(glGetUniformLocation(activeShaderProgram, "renderMode"), (int)renderMode);
        glUniform3fv(glGetUniformLocation(activeShaderProgram, "camPos"), 1, glm::value_ptr(playerCamera.location));

        for (Light* light : activeScene.lights)
        {
            glUniform3fv(glGetUniformLocation(activeShaderProgram, "lightPos"), 1, glm::value_ptr(light->location));
            glUniform4fv(glGetUniformLocation(activeShaderProgram, "lightCol"), 1, glm::value_ptr(light->color));
            glUniform1i(glGetUniformLocation(activeShaderProgram, "lightType"), (int)light->lightType);
        }

        playerCamera.NavigateCamera();
        playerCamera.ApplyCamMatrix();

        for (Mesh* mesh : activeScene.meshes)
        {
            mesh->DrawMesh();
        }
        
        shaders.at("skyBox").Activate();
        skyBox.DrawSkybox();

        glBindFramebuffer(GL_READ_FRAMEBUFFER, msaaSceneFBO.id);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ppFBO.id);
        glBlitFramebuffer(0, 0, windowWidth, windowHeight, 0, 0, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        msaaSceneFBO.Unbind();

        shaders.at("screen").Activate();
        screenQuad.vao.Bind();
        glUniform1i(glGetUniformLocation(activeShaderProgram, "screenTexture"), 0);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glBindTexture(GL_TEXTURE_2D, ppFBO.colorTex);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        screenQuad.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    }
}

void Engine::QuitEngine()
{
    activeScene.UnloadScene();
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
