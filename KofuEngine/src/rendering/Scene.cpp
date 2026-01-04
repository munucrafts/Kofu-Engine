#pragma once
#include "scene.h"
#include <geometry/GLTFLoader.h>
#include <Engine.h>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include "../audio/AudioMaster.h"

void Scene::BeginScene(unsigned int windowWidth, unsigned int windowHeight)
{
    AudioMaster::GetAudioMaster().InitAudioMaster();
    renderMode = LIT;
    playerCamera.location = glm::vec3(0.0f, 6.0f, 25.0f);

    shaders.emplace(STATIC_MESH, Shader("./shaders/staticMesh.vert", "./shaders/staticMesh.frag", ""));
    shaders.emplace(INSTANCED_STATIC_MESH, Shader("./shaders/instancedStaticMesh.vert", "./shaders/instancedStaticMesh.frag", ""));
    shaders.emplace(SKY_BOX, Shader("./shaders/skyBox.vert", "./shaders/skyBox.frag", ""));
    shaders.emplace(SCREEN, Shader("./shaders/screen.vert", "./shaders/screen.frag", ""));
    shaders.emplace(GRID, Shader("./shaders/grid.vert", "./shaders/grid.frag", ""));
    shaders.emplace(LIGHT_MESH, Shader("./shaders/lightMesh.vert", "./shaders/lightMesh.frag", ""));
    shaders.emplace(LIGHT_SHADOW, Shader("./shaders/shadow.vert", "./shaders/shadow.frag", ""));
    shaders.emplace(POINT_LIGHT_SHADOW, Shader("./shaders/pointLightShadow.vert", "./shaders/pointLightShadow.frag", "./shaders/pointLightShadow.geom"));

    //modelPaths.insert({"./assets/models/Ruel/scene.gltf", MeshData(STATIC_MESH, Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(5.1f)))});
    //modelPaths.insert({"./assets/models/Medieval/medieval.gltf", MeshData(STATIC_MESH, Transform(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f), glm::vec3(10.0f)))});
    //modelPaths.insert({"./assets/models/BatmanRP/scene.gltf", MeshData(STATIC_MESH, Transform(glm::vec3(0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(5.1f)))});
    modelPaths.insert({"./assets/models/Batman/scene.gltf", MeshData(STATIC_MESH, Transform(glm::vec3(0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.1f)))});
    //modelPaths.insert({"./assets/models/Helmet/Scene.gltf", MeshData(INSTANCED_STATIC_MESH, Transform(glm::vec3(0.0f, 10.0f ,0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(5.0f)), 4)});
    
    for (const std::pair<std::string, MeshData>& path : modelPaths)
    {
        std::vector<Mesh*> newMeshes = GLTFLoader::GetGltfLoader().LoadGltfModel(path.first, path.second);
        meshes.insert(meshes.end(), newMeshes.begin(), newMeshes.end());
    }

    //lights.emplace_back(new Light({ .lightType = SPOT_LIGHT, .intensity = 1.0f, .location = glm::vec3(-7.0f, 15.0f, -18.0f), .rotation = glm::vec3(-95.0f, 0.0f, 0.0f) }));
    //lights.emplace_back(new Light({ .lightType = POINT_LIGHT, .intensity = 0.1f, .location = glm::vec3(0.0f, 10.0f, 0.0f)}));
    lights.emplace_back(new Light({ .lightType = DIRECTIONAL_LIGHT, .intensity = 1.0f, .location = glm::vec3(10.0f, 10.0f, 10.0f), .rotation = glm::vec3(-45.f, 0.0f, 0.0f) }));

    SortMeshesByType();

    for (Mesh* mesh : meshes) mesh->InitMesh();

    for (int i = 0; i < lights.size(); i++)
    {
        lights[i]->Init();
        shadowMapFBOs.emplace_back(lights[i]->lightDetails.lightType == POINT_LIGHT ? 
                                    RenderTarget::CreateCubemapTarget(shadowMapWidth, shadowMapHeight) : 
                                    RenderTarget::CreateShadowTarget(shadowMapWidth, shadowMapHeight));
    }

    skyBox.LoadSkybox();
    screenQuad.Init();
    gridQuad.Init(Transform(glm::vec3(0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(10000.0f)));
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

    GLuint shaderID = 0;
    playerCamera.NavigateCamera();

    Engine::GetEngine().ClearWindow(shadowMapWidth, shadowMapHeight);

    for (int i = 0; i < lights.size(); i++)
    {
        shadowMapFBOs[i].Bind();
        glClear(GL_DEPTH_BUFFER_BIT);

        if (lights[i]->lightDetails.lightType == POINT_LIGHT)
        {
            shaderID = shaders.at(POINT_LIGHT_SHADOW).Activate();
            glUniformMatrix4fv(glGetUniformLocation(shaderID, "shadowMatrices"), 6, GL_FALSE, glm::value_ptr(lights[i]->lightDetails.lightProjs[0]));
            glUniform3fv(glGetUniformLocation(shaderID, "lightPosition"), 1, glm::value_ptr(lights[i]->lightDetails.location));
        }
        else
        {
            shaderID = shaders.at(LIGHT_SHADOW).Activate();
            glUniformMatrix4fv(glGetUniformLocation(shaderID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lights[i]->lightDetails.lightProjs[0]));
        }

        glUniform1f(glGetUniformLocation(shaderID, "farPlane"), lights[0]->farPlane);

        for (Mesh* mesh : meshes) mesh->DrawMesh(shaderID);
    }

    msaaSceneFBO.Bind();
    Engine::GetEngine().ClearWindow(windowWidth, windowHeight);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    shaderID = shaders.at(LIGHT_MESH).Activate();
    playerCamera.ApplyCamMatrix(shaderID);

    for (Light* light : lights) light->DrawLightMesh(shaderID);

    ObjectType lastMeshType = NONE;

    for (Mesh* mesh : meshes)
    {
        if (mesh->meshType != lastMeshType)
        {
            lastMeshType = mesh->meshType;
            shaderID = shaders.at(lastMeshType).Activate();
            UploadLightData(shaderID);
            playerCamera.ApplyCamMatrix(shaderID);
        }

        mesh->DrawMesh(shaderID);
    }

    shaderID = shaders.at(SKY_BOX).Activate();
    skyBox.DrawSkybox(shaderID);

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    shaderID = shaders.at(GRID).Activate();
    playerCamera.ApplyCamMatrix(shaderID);
    gridQuad.vao.Bind();
    gridQuad.DrawQuad(shaderID);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, msaaSceneFBO.id);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ppFBO.id);
    glBlitFramebuffer(0, 0, windowWidth, windowHeight, 0, 0, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    msaaSceneFBO.Unbind();

    shaderID = shaders.at(SCREEN).Activate();
    screenQuad.vao.Bind();
    glUniform1i(glGetUniformLocation(shaderID, "screenTexture"), 0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glBindTexture(GL_TEXTURE_2D, ppFBO.colorTex);
    screenQuad.DrawQuad(shaderID);
}

void Scene::EndScene()
{
    for (Mesh* mesh : meshes) delete mesh;
    for (Light* light : lights) delete light;
}

void Scene::UploadLightData(const GLuint shaderId)
{
    glUniform1i(glGetUniformLocation(shaderId, "renderMode"), (int)renderMode);
    glUniform1f(glGetUniformLocation(shaderId, "lightFarPlane"), lights[0]->farPlane);
    glUniform1i(glGetUniformLocation(shaderId, "lightCount"), lights.size());

    unsigned int reservedSlots = reservedTexSlots.size();

    for (const std::pair<std::string, unsigned int>& slot : reservedTexSlots)
    {
        glUniform1i(glGetUniformLocation(shaderId, slot.first.c_str()), slot.second);
    }

    for (int i = 0; i < lights.size(); i++)
    {
        lights[i]->CalculateLightProjection();

        bool isPointLight = lights[i]->lightDetails.lightType == POINT_LIGHT;
        GLuint nextTexUnit = reservedSlots + i;

        glActiveTexture(GL_TEXTURE0 + nextTexUnit);
        glBindTexture(isPointLight ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, shadowMapFBOs[i].depthTex);
        glUniform1i(glGetUniformLocation(shaderId, ((isPointLight ? "shadowCubeMap[" : "shadowMap[") + std::to_string(i) + "]").c_str()), nextTexUnit);
        glUniform3fv(glGetUniformLocation(shaderId, ("lightPositions[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(lights[i]->lightDetails.location));
        glUniform4fv(glGetUniformLocation(shaderId, ("lightColors[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(lights[i]->lightDetails.color));
        glUniform1i(glGetUniformLocation(shaderId, ("lightTypes[" + std::to_string(i) + "]").c_str()), (int)lights[i]->lightDetails.lightType);
        glUniform1f(glGetUniformLocation(shaderId, ("lightIntensities[" + std::to_string(i) + "]").c_str()), lights[i]->lightDetails.intensity);

        if (lights[i]->lightDetails.lightType == SPOT_LIGHT)
        {
            glUniform3fv(glGetUniformLocation(shaderId, ("lightDirections[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(lights[i]->GetDirection()));
            glUniform1f(glGetUniformLocation(shaderId, ("lightInnerCones[" + std::to_string(i) + "]").c_str()), std::cos(glm::radians(lights[i]->lightDetails.innerCone)));
            glUniform1f(glGetUniformLocation(shaderId, ("lightOuterCones[" + std::to_string(i) + "]").c_str()), std::cos(glm::radians(lights[i]->lightDetails.outerCone)));
        }

        if (!isPointLight)
        {
            glUniformMatrix4fv(glGetUniformLocation(shaderId, ("lightProjections[" + std::to_string(i) + "]").c_str()), 1, GL_FALSE, glm::value_ptr(lights[i]->lightDetails.lightProjs[0]));
        }
    }
}

void Scene::SortMeshesByType()
{
    std::sort(meshes.begin(), meshes.end(), [](Mesh* a, Mesh* b)
        {
            return a->meshType < b->meshType;
        }
    );
}
