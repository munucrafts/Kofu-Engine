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

    window = glfwCreateWindow(windowWidth, windowHeight, "Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();

    renderMode = UNLIT;
    playerCamera.location = glm::vec3(0.0f, 6.0f, 25.0f);

    GLTFLoader::GetGltfLoader().LoadGltfModel("./assets/models/Medieval.gltf", &activeScene);

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

    Shader defaultShader;
    activeShaderProgramID = defaultShader.CreateShaders("./shaders/vert.glsl", "./shaders/frag.glsl");  

    engineInitialized = true;
}

void Engine::RunEngine()
{
    float prevTime = 0.0f, currentTime = 0.0f, timeDiff = 0.0f;
    int counter = 0;

    while (!glfwWindowShouldClose(window) && engineInitialized)
    {
        currentTime = glfwGetTime();
        timeDiff = currentTime - prevTime;
        counter++;

        if (timeDiff >= 1.0f / 30.0f)
        {
            std::string FPS = std::to_string((int)(1.0f / timeDiff) * counter);
            std::string statLine = "Engine : [ FPS = " + FPS + " ]";
            glfwSetWindowTitle(window, statLine.c_str());
            prevTime = currentTime;
            counter = 0;
        }

        glClearColor(0.38f, 0.67f, 0.94f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(activeShaderProgramID);

        playerCamera.ApplyCamMatrix();
        playerCamera.NavigateCamera();

        glUniform1f(glGetUniformLocation(activeShaderProgramID, "nearClip"), nearClip);
        glUniform1f(glGetUniformLocation(activeShaderProgramID, "farClip"), farClip);
        glUniform1i(glGetUniformLocation(activeShaderProgramID, "renderMode"), (int)renderMode);

        for (Mesh* mesh : activeScene.meshes)
        {
            mesh->DrawMesh();
        }

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
