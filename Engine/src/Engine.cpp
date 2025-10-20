#include "Engine.h"
#include "iostream"
#include "GLTFLoader.h"

std::vector<Vertex> screenRectVerts =
{
    { glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(1.0f, 0.0f) },
    { glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(0.0f, 0.0f) },
    { glm::vec3(-1.0f,  1.0f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(0.0f, 1.0f) },
    { glm::vec3(1.0f,  1.0f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(1.0f, 1.0f) },
    { glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(1.0f, 0.0f) },
    { glm::vec3(-1.0f,  1.0f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(0.0f, 1.0f) }
};

VAO screenRectVao;
VBO screenRectVbo;

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

    screenRectVao.Init();
    screenRectVao.Bind();
    screenRectVbo.Init(screenRectVerts);
    screenRectVbo.Bind();
    screenRectVao.LinkAttribs(screenRectVbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    screenRectVao.LinkAttribs(screenRectVbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(10 * sizeof(float)));

    fbo.Init();
    fbo.Bind();
    rbo.Init(windowWidth, windowHeight);
    rbo.Bind();
    fbTex.Init(windowWidth, windowHeight);
    fbTex.Bind();
    
    renderMode = LIT;
    playerCamera.location = glm::vec3(0.0f, 6.0f, 25.0f);

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

    Shader defaultShader("./shaders/default.vert", "./shaders/default.frag");
    activeShaderProgram = defaultShader.shaderProgram;  

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
            std::string statLine = "Engine : [ FPS = " + FPS + " ]";
            glfwSetWindowTitle(window, statLine.c_str());
            prevTime = currentTime;
            counter = 0;
        }

        fbo.Bind();

        glClearColor(0.38f, 0.67f, 0.94f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glUseProgram(activeShaderProgram);

        playerCamera.ApplyCamMatrix();
        playerCamera.NavigateCamera();

        glUniform1f(glGetUniformLocation(activeShaderProgram, "nearClip"), nearClip);
        glUniform1f(glGetUniformLocation(activeShaderProgram, "farClip"), farClip);
        glUniform1i(glGetUniformLocation(activeShaderProgram, "renderMode"), (int)renderMode);

        for (Mesh* mesh : activeScene.meshes)
        {
            mesh->DrawMesh();
        }

        fbo.Unbind();
        Shader frameBufferShader("./shaders/frameBuffer.vert", "./shaders/frameBuffer.frag");
        activeShaderProgram = frameBufferShader.shaderProgram;
        screenRectVao.Bind();
        glDisable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        fbTex.Bind();
        GLuint screenTexLoc = glGetUniformLocation(activeShaderProgram, "screenTexture");
        glUniform1i(screenTexLoc, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    }
}

void Engine::QuitEngine()
{
    activeScene.UnloadScene();

    fbo.Delete();
    rbo.Delete();
    fbTex.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}

float Engine::GetAspectRatio()
{
    return ((float)windowWidth/windowHeight);
}
