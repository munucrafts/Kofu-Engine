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

    Mesh* mesh1 = new Mesh();
    mesh1->transform.location = glm::vec3(0.0f, -0.5f, -2.0f);
    mesh1->transform.rotation = glm::vec3(0.0f, 45.0f, 0.0f);
    mesh1->transform.scale = glm::vec3(3.0f, 3.0f, 3.0f);
    meshes.push_back(mesh1);

    for (Mesh* mesh : meshes)
    {
        mesh->InitMesh();
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, windowWidth, windowHeight);
    activeShaderProgramID = shader.CreateShaders("./shaders/vert.glsl", "./shaders/frag.glsl");  

    engineInitialized = true;
}

void Engine::RunEngine()
{
    while (!glfwWindowShouldClose(window) && engineInitialized)
    {
        glClearColor(0.24f, 0.15f, 0.37f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(activeShaderProgramID);

        playerCamera.ApplyCamMatrix();
        playerCamera.NavigateCamera();

        for (Mesh* mesh : meshes)
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
    for (Mesh* mesh : meshes)
    {
        mesh->ClearMesh();
    }

    meshes.clear();
    glfwDestroyWindow(window);
    glfwTerminate();
}

float Engine::GetAspectRatio()
{
    return ((float)windowWidth/windowHeight);
}
