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

    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };

    vao.Init();
    vbo.Init(vertices, sizeof(vertices));

    vao.Bind();
    vbo.Bind();

    vao.LinkAttribs(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    activeShaderProgram = shader.CreateShaders("../shaders/Triangle.vert", "../shaders/Triangle.frag");

    vao.Unbind();
    vbo.Unbind();
}

void Engine::RunEngine()
{
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.24f, 0.45f, 0.37f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(activeShaderProgram);
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    }
}

void Engine::QuitEngine()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}