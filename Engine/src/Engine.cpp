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
    {
    //      COORDINATES              COLORS          TexCoord 
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,  // Lower left corner
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,  // Upper left corner
         0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,  // Upper right corner
         0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f   // Lower right corner
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 2, 1, // Upper triangle
        0, 3, 2  // Lower triangle
    };


    vao.Init();
    vbo.Init(vertices, sizeof(vertices));
    ebo.Init(indices, sizeof(indices));
    texture.Init();

    vao.Bind();
    vbo.Bind();
    ebo.Bind();
    texture.Bind();

    vao.LinkAttribs(vbo, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
    vao.LinkAttribs(vbo, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    vao.LinkAttribs(vbo, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    activeShaderProgramId = shader.CreateShaders("./shaders/vert.glsl", "./shaders/frag.glsl");  

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
    texture.Unind();
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
        GLuint uniTex0 = glGetUniformLocation(activeShaderProgramId, "tex0");

        glUniform1f(uniScale, 1.5f);
        glUniform1f(uniIntensity, 1.5f);
        glUniform1i(uniTex0, 0);

        vao.Bind();
        texture.Bind();

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
    texture.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}