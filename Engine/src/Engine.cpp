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

    // Vertices coordinates
    GLfloat vertices[] =
    { //               COORDINATES                  /     COLORS           //
        -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.2f, 0.73f,  1.00f, // Lower left corner
         0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.3f, 1.0f,  0.32f, // Lower right corner
         0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.4f, 0.6f,  0.92f, // Upper corner
        -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.2f, 0.17f, // Inner left
         0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.39f, 0.5f, 1.00f, // Inner right
         0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.2f, 0.93f,  0.02f  // Inner down
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Lower right triangle
        5, 4, 1 // Upper triangle
    };

    vao.Init();
    vbo.Init(vertices, sizeof(vertices));
    ebo.Init(indices, sizeof(indices));

    vao.Bind();
    vbo.Bind();
    ebo.Bind();

    vao.LinkAttribs(vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
    vao.LinkAttribs(vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    activeShaderProgramId = shader.CreateShaders("./shaders/vert.glsl", "./shaders/frag.glsl");  

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Engine::RunEngine()
{
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.24f, 0.15f, 0.37f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(activeShaderProgramId);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        float uniScale = glGetUniformLocation(activeShaderProgramId, "scale");
        float uniIntensity = glGetUniformLocation(activeShaderProgramId, "intensity");
        glUniform1f(uniScale, 1.5f);
        glUniform1f(uniIntensity, 1.5f);

        vao.Bind();
        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    }
}

void Engine::QuitEngine()
{
    vbo.Delete();
    vao.Delete();
    ebo.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}