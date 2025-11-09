#pragma once
#include "scene.h"
#include <geometry/GLTFLoader.h>
#include <glm/gtc/type_ptr.hpp>
#include <Engine.h>

void Scene::BeginScene(unsigned int windowWidth, unsigned int windowHeight)
{
    shaders.emplace("default", Shader("./shaders/default.vert", "./shaders/default.frag"));
    shaders.emplace("skyBox", Shader("./shaders/skyBox.vert", "./shaders/skyBox.frag"));
    shaders.emplace("screen", Shader("./shaders/screen.vert", "./shaders/screen.frag"));
    shaders.emplace("light", Shader("./shaders/light.vert", "./shaders/light.frag"));

    renderMode = LIT;
    playerCamera.location = glm::vec3(0.0f, 6.0f, 25.0f);

    modelPaths.push_back("./assets/models/medieval.gltf");
    
    for (const std::string& path : modelPaths)
    {
        std::vector<Mesh*> newMeshes = GLTFLoader::GetGltfLoader().LoadGltfModel(path);
        meshes.insert(meshes.end(), newMeshes.begin(), newMeshes.end());
    }

    Light* light = new Light(glm::vec4(1.0f), glm::vec3(10.0f, -2.0f, 0.0f), DIRECTIONAL_LIGHT);
    lights.emplace_back(light);

    for (Mesh* mesh : meshes)
    {
        mesh->transform.location = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->transform.scale = glm::vec3(10.0f);
        mesh->InitMesh();
    }

    for (Light* light : lights)
    {
        light->Init();
    }

    skyBox.LoadSkybox();
    screenQuad.Init();
    msaaSceneFBO = RenderTarget::CreateMSAATarget(windowWidth, windowHeight, 8);
    ppFBO = RenderTarget::CreateSceneTarget(windowWidth, windowHeight);
}

void Scene::RenderScene(unsigned int windowWidth, unsigned int windowHeight, bool windowResized, float deltaTime)
{
    if (windowResized)
    {
        msaaSceneFBO.Resize(windowWidth, windowHeight);
        ppFBO.Resize(windowWidth, windowHeight);
    }

    msaaSceneFBO.Bind();

    Engine::GetEngine().ClearWindow();

    shaders.at("light").Activate();
    playerCamera.NavigateCamera();
    playerCamera.ApplyCamMatrix();

    for (Light* light : lights)
    {
        light->DrawLightMesh();
    }

    shaders.at("default").Activate();
    playerCamera.ApplyCamMatrix();
    glUniform1f(glGetUniformLocation(activeShaderProgram, "nearClip"), playerCamera.nearClip);
    glUniform1f(glGetUniformLocation(activeShaderProgram, "farClip"), playerCamera.farClip);
    glUniform1i(glGetUniformLocation(activeShaderProgram, "renderMode"), (int)renderMode);
    glUniform3fv(glGetUniformLocation(activeShaderProgram, "camPos"), 1, glm::value_ptr(playerCamera.location));

    for (Light* light : lights)
    {
        glUniform3fv(glGetUniformLocation(activeShaderProgram, "lightPos"), 1, glm::value_ptr(light->location));
        glUniform4fv(glGetUniformLocation(activeShaderProgram, "lightCol"), 1, glm::value_ptr(light->color));
        glUniform1i(glGetUniformLocation(activeShaderProgram, "lightType"), (int)light->lightType);
    }

    for (Mesh* mesh : meshes)
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
}

void Scene::EndScene()
{
    for (Mesh* mesh : meshes)
    {
        delete mesh;
    }

    for (Light* light : lights)
    {
        delete light;
    }
}
