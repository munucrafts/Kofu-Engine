#pragma once
#include "scene.h"
#include <geometry/GLTFLoader.h>
#include <Engine.h>
#include <glm/gtc/type_ptr.hpp>

void Scene::BeginScene(unsigned int windowWidth, unsigned int windowHeight)
{
    shaders.emplace("default", Shader("./shaders/default.vert", "./shaders/default.frag", ""));
    shaders.emplace("skyBox", Shader("./shaders/skyBox.vert", "./shaders/skyBox.frag", ""));
    shaders.emplace("screen", Shader("./shaders/screen.vert", "./shaders/screen.frag", ""));
    shaders.emplace("light", Shader("./shaders/light.vert", "./shaders/light.frag", ""));
    shaders.emplace("shadow", Shader("./shaders/shadow.vert", "./shaders/shadow.frag", ""));
    shaders.emplace("pointLightShadow", Shader("./shaders/pointLightShadow.vert", "./shaders/pointLightShadow.frag", "./shaders/pointLightShadow.geom"));

    renderMode = LIT;
    playerCamera.location = glm::vec3(0.0f, 6.0f, 25.0f);

    modelPaths.push_back("./assets/models/medieval.gltf");
    
    for (const std::string& path : modelPaths)
    {
        std::vector<Mesh*> newMeshes = GLTFLoader::GetGltfLoader().LoadGltfModel(path);
        meshes.insert(meshes.end(), newMeshes.begin(), newMeshes.end());
    }

    lights.emplace_back(new Light({ .lightType = SPOT_LIGHT, .intensity = 1.0f, .location = glm::vec3(-7.0f, 15.0f, -18.0f), .rotation = glm::vec3(-95.0f, 0.0f, 0.0f) }));
    lights.emplace_back(new Light({ .lightType = DIRECTIONAL_LIGHT, .intensity = 0.5f, .location = glm::vec3(10.0f, 10.0f, 0.0f), .rotation = glm::vec3(-45.f, 0.0f, 0.0f) }));
    lights.emplace_back(new Light({ .lightType = POINT_LIGHT, .intensity = 0.1f, .location = glm::vec3(0.0f, 10.0f, 0.0f)}));

    for (Mesh* mesh : meshes)
    {
        mesh->transform.location = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->transform.scale = glm::vec3(10.0f);
        mesh->InitMesh();
    }

    for (int i = 0; i < lights.size(); i++)
    {
        lights[i]->Init();
        shadowMapFBOs.emplace_back(lights[i]->lightDetails.lightType == POINT_LIGHT ? 
                                    RenderTarget::CreateCubemapTarget(shadowMapWidth, shadowMapHeight) : 
                                    RenderTarget::CreateShadowTarget(shadowMapWidth, shadowMapHeight));
    }

    skyBox.LoadSkybox();
    screenQuad.Init();
    msaaSceneFBO = RenderTarget::CreateMSAATarget(windowWidth, windowHeight, 8);
    ppFBO = RenderTarget::CreateSceneTarget(windowWidth, windowHeight);

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

    shaders.at("pointLightShadow").Activate();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, shadowMapWidth, shadowMapHeight);

    glUniform1f(glGetUniformLocation(activeShaderProgram, "farPlane"), lights[0]->farPlane);

    for (int i = 0; i < lights.size(); i++)
    {
        if (lights[i]->lightDetails.lightType == POINT_LIGHT)
        {
            shadowMapFBOs[i].Bind();

            glUniformMatrix4fv(glGetUniformLocation(activeShaderProgram, "shadowMatrices"), 6, GL_FALSE, glm::value_ptr(lights[i]->lightDetails.lightProjs[0]));
            glUniform3fv(glGetUniformLocation(activeShaderProgram, "lightPosition"), 1, glm::value_ptr(lights[i]->lightDetails.location));

            for (Mesh* mesh : meshes)
            {
                mesh->DrawMesh();
            }
        }
    }

    shaders.at("shadow").Activate();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, shadowMapWidth, shadowMapHeight);

    for (int i = 0; i < lights.size(); i++)
    {
        if (lights[i]->lightDetails.lightType != POINT_LIGHT)
        {
            shadowMapFBOs[i].Bind();

            glClear(GL_DEPTH_BUFFER_BIT);
            glUniformMatrix4fv(glGetUniformLocation(activeShaderProgram, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lights[i]->lightDetails.lightProjs[0]));

            for (Mesh* mesh : meshes)
            {
                mesh->DrawMesh();
            }
        }
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

    glUniform1i(glGetUniformLocation(activeShaderProgram, "renderMode"), (int)renderMode);
    glUniform1f(glGetUniformLocation(activeShaderProgram, "lightFarPlane"), lights[0]->farPlane);
    glUniform1i(glGetUniformLocation(activeShaderProgram, "lightCount"), lights.size());

    unsigned int reservedSlots = reservedTexSlots.size();

    for (std::pair<const std::string, unsigned int>& slot : reservedTexSlots)
    {
        glUniform1i(glGetUniformLocation(activeShaderProgram, slot.first.c_str()), slot.second);
    }

    for (int i = 0; i < lights.size(); i++)
    {
        bool isPointLight = lights[i]->lightDetails.lightType == POINT_LIGHT;
        lights[i]->CalculateLightProjection();

        GLuint nextTexUnit = reservedSlots + i;
        glActiveTexture(GL_TEXTURE0 + nextTexUnit);
        glBindTexture(isPointLight ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, shadowMapFBOs[i].depthTex);
        glUniform1i(glGetUniformLocation(activeShaderProgram, ((isPointLight ? "shadowCubeMap[" : "shadowMap[") + std::to_string(i) + "]").c_str()), nextTexUnit);
        glUniform3fv(glGetUniformLocation(activeShaderProgram, ("lightPositions[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(lights[i]->lightDetails.location));
        glUniform4fv(glGetUniformLocation(activeShaderProgram, ("lightColors[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(lights[i]->lightDetails.color));
        glUniform1i(glGetUniformLocation(activeShaderProgram, ("lightTypes[" + std::to_string(i) + "]").c_str()), (int)lights[i]->lightDetails.lightType);
        glUniform1f(glGetUniformLocation(activeShaderProgram, ("lightIntensities[" + std::to_string(i) + "]").c_str()), lights[i]->lightDetails.intensity);

        if (lights[i]->lightDetails.lightType == SPOT_LIGHT)
        {
            glUniform3fv(glGetUniformLocation(activeShaderProgram, ("lightDirections[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(lights[i]->GetDirection()));
            glUniform1f(glGetUniformLocation(activeShaderProgram, ("lightInnerCones[" + std::to_string(i) + "]").c_str()), std::cos(glm::radians(lights[i]->lightDetails.innerCone)));
            glUniform1f(glGetUniformLocation(activeShaderProgram, ("lightOuterCones[" + std::to_string(i) + "]").c_str()), std::cos(glm::radians(lights[i]->lightDetails.outerCone)));
        }

        if (!isPointLight)
        {
            glUniformMatrix4fv(glGetUniformLocation(activeShaderProgram, ("lightProjections[" + std::to_string(i) + "]").c_str()), 1, GL_FALSE, glm::value_ptr(lights[i]->lightDetails.lightProjs[0]));
        }
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
