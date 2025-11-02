#pragma once
#include "Engine.h"
#include "iostream"
#include "GLTFLoader.h"

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
    shaders.emplace("frameBuffer", Shader("./shaders/frameBuffer.vert", "./shaders/frameBuffer.frag"));
    shaders.emplace("light", Shader("./shaders/light.vert", "./shaders/light.frag"));

    renderMode = LIT;
    playerCamera.location = glm::vec3(0.0f, 6.0f, 25.0f);

    skyBox.LoadSkybox();
    msaaFbo.Init(windowWidth, windowHeight, msaaSamples);
    ppFbo.Init(windowWidth, windowHeight);

    directionalLight = { glm::vec4(1.0f), glm::vec3(10.0f, 15.0f, 0.0f) };
    directionalLight.Init();

    activeScene.modelPaths.push_back("./assets/models/medieval.gltf");
    activeScene.modelPaths.push_back("./assets/models/Lantern.gltf");
    activeScene.LoadScene();

    for (Mesh* mesh : activeScene.meshes)
    {
        mesh->transform.location = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->transform.scale = glm::vec3(10.0f);
        mesh->InitMesh();
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

        msaaFbo.Bind();

        ClearWindow();
        shaders.at("default").Activate();

        playerCamera.NavigateCamera();
        playerCamera.ApplyCamMatrix();

        glUniform1f(glGetUniformLocation(activeShaderProgram, "nearClip"), nearClip);
        glUniform1f(glGetUniformLocation(activeShaderProgram, "farClip"), farClip);
        glUniform1i(glGetUniformLocation(activeShaderProgram, "renderMode"), (int)renderMode);

        glUniform3f(glGetUniformLocation(activeShaderProgram, "lightPos"), directionalLight.location.x, directionalLight.location.y, directionalLight.location.z);
        glUniform4f(glGetUniformLocation(activeShaderProgram, "lightCol"), directionalLight.color.r, directionalLight.color.g, directionalLight.color.b, directionalLight.color.a);

        glUniform3f(glGetUniformLocation(activeShaderProgram, "camPos"), playerCamera.location.x, playerCamera.location.y, playerCamera.location.z);

        for (Mesh* mesh : activeScene.meshes)
        {
            mesh->DrawMesh();
        }
        
        shaders.at("light").Activate();
        playerCamera.ApplyCamMatrix();
        directionalLight.DrawLightMesh();

        shaders.at("skyBox").Activate();
        skyBox.DrawSkybox();

        msaaFbo.DrawMSAA(ppFbo, windowWidth, windowHeight);
        msaaFbo.Unbind();

        shaders.at("frameBuffer").Activate();
        ppFbo.DrawFBO(activeShaderProgram);

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
