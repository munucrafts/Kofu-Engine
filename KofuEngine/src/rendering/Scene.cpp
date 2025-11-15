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
    shaders.emplace("shadow", Shader("./shaders/shadow.vert", "./shaders/shadow.frag"));

    renderMode = LIT;
    playerCamera.location = glm::vec3(0.0f, 6.0f, 25.0f);

    modelPaths.push_back("./assets/models/medieval.gltf");
    
    for (const std::string& path : modelPaths)
    {
        std::vector<Mesh*> newMeshes = GLTFLoader::GetGltfLoader().LoadGltfModel(path);
        meshes.insert(meshes.end(), newMeshes.begin(), newMeshes.end());
    }

    Light* light = new Light(glm::vec4(1.0f), glm::vec3(10.0f, 10.0f, 0.0f), DIRECTIONAL_LIGHT);
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
    shadowMapFBO = RenderTarget::CreateShadowTarget(shadowMapWidth, shadowMapHeight);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glViewport(0, 0, windowWidth, windowHeight);
}

void Scene::RenderScene(unsigned int windowWidth, unsigned int windowHeight, bool windowResized, float deltaTime)
{
    if (windowResized)
    {
        msaaSceneFBO.Resize(windowWidth, windowHeight);
        ppFBO.Resize(windowWidth, windowHeight);
    }

    shaders.at("shadow").Activate();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, shadowMapWidth, shadowMapHeight);
    shadowMapFBO.Bind();
    glClear(GL_DEPTH_BUFFER_BIT);

    for (Light* light : lights)
    {
        light->CalculateLightProjection();
        glUniformMatrix4fv(glGetUniformLocation(activeShaderProgram, "lightProjection"), 1, GL_FALSE, glm::value_ptr(light->lightProj));
    }

    for (Mesh* mesh : meshes)
    {
        mesh->DrawMesh();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, windowWidth, windowHeight);
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

    glUniform1i(glGetUniformLocation(activeShaderProgram, "baseTex"), 0);
    glUniform1i(glGetUniformLocation(activeShaderProgram, "normalTex"), 1);
    glUniform1i(glGetUniformLocation(activeShaderProgram, "occlusionTex"), 2);
    glUniform1i(glGetUniformLocation(activeShaderProgram, "metallicTex"), 3);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, shadowMapFBO.depthTex);
    glUniform1i(glGetUniformLocation(activeShaderProgram, "shadowMap"), 4);

    for (Light* light : lights)
    {
        glUniform3fv(glGetUniformLocation(activeShaderProgram, "lightPos"), 1, glm::value_ptr(light->location));
        glUniform4fv(glGetUniformLocation(activeShaderProgram, "lightCol"), 1, glm::value_ptr(light->color));
        glUniform1i(glGetUniformLocation(activeShaderProgram, "lightType"), (int)light->lightType);

        light->CalculateLightProjection();
        glUniformMatrix4fv(glGetUniformLocation(activeShaderProgram, "lightProjection"), 1, GL_FALSE, glm::value_ptr(light->lightProj));
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
