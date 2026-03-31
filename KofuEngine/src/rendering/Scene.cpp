#pragma once
#include "scene.h"
#include <geometry/GLTFLoader.h>
#include <Engine.h>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include "../audio/AudioMaster.h"
#include <imgui.h>
#include <Stats/StatsHelper.h>
#include <Components/Controller.h>

void Scene::BeginScene()
{
    AudioMaster::GetAudioMaster().InitAudioMaster();
    MasterUI::GetMasterUI().InitMasterUI();

    renderMode = LIT;

    shaders.emplace(STATIC_MESH, Shader("./shaders/staticMesh.vert", "./shaders/staticMesh.frag"));
    shaders.emplace(GIZMO, Shader("./shaders/gizmo.vert", "./shaders/gizmo.frag"));
    shaders.emplace(INSTANCED_STATIC_MESH, Shader("./shaders/instancedStaticMesh.vert", "./shaders/instancedStaticMesh.frag"));
    shaders.emplace(SKY_BOX, Shader("./shaders/skyBox.vert", "./shaders/skyBox.frag"));
    shaders.emplace(SCREEN, Shader("./shaders/screen.vert", "./shaders/screen.frag"));
    shaders.emplace(GRID, Shader("./shaders/grid.vert", "./shaders/grid.frag"));
    shaders.emplace(LIGHT_MESH, Shader("./shaders/lightMesh.vert", "./shaders/lightMesh.frag"));
    shaders.emplace(LIGHT_SHADOW, Shader("./shaders/shadow.vert", "./shaders/shadow.frag"));
    shaders.emplace(POINT_LIGHT_SHADOW, Shader("./shaders/pointLightShadow.vert", "./shaders/pointLightShadow.frag", "./shaders/pointLightShadow.geom"));

    playerCamera.location = glm::vec3(0.0f, 10.0f, 50.0f);

    //modelPaths.insert({"./assets/models/Ruel/scene.gltf", MeshData(STATIC_MESH, Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(5.1f)))});
    //modelPaths.insert({"./assets/models/Medieval/medieval.gltf", MeshData(STATIC_MESH, Transform(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f), glm::vec3(10.0f)))});
    //modelPaths.insert({"./assets/models/BatmanRP/scene.gltf", MeshData(STATIC_MESH, Transform(glm::vec3(0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(5.1f)))});
    //modelPaths.insert({"./assets/models/Helmet/Scene.gltf", MeshData(INSTANCED_STATIC_MESH, Transform(glm::vec3(0.0f, 0.0f ,-150.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f)), 4)});
    modelPaths.insert({"./assets/models/Batman/scene.gltf", MeshData(STATIC_MESH, Transform(glm::vec3(0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.1f)))});
    
    for (const std::pair<std::string, MeshData>& path : modelPaths)
    {
        std::vector<Mesh*> newMeshes = GLTFLoader::GetGltfLoader().LoadGltfModel(path.first, path.second);
        meshes.insert(meshes.end(), newMeshes.begin(), newMeshes.end());
    }

    //lights.emplace_back(new Light({.lightType = SPOT_LIGHT, .intensity = 0.2f, .location = glm::vec3(-7.0f, 15.0f, -18.0f)}));
    //lights.emplace_back(new Light({.lightType = POINT_LIGHT, .intensity = 0.1f, .location = glm::vec3(0.0f, 10.0f, 0.0f)}));
    lights.emplace_back(new Light({.lightType = DIRECTIONAL_LIGHT, .intensity = 1.0f, .location = glm::vec3(10.0f, 10.0f, 10.0f)}));

    SortObjectsByType();

    for (Mesh* mesh : meshes) mesh->InitMesh();

    for (int i = 0; i < lights.size(); i++)
    {
        lights[i]->Init();
        shadowMapFBOs.emplace_back(lights[i]->lightDetails.lightType == POINT_LIGHT ? 
                                    RenderTarget::CreateCubemapTarget(shadowMapWidth, shadowMapHeight) : 
                                    RenderTarget::CreateShadowTarget(shadowMapWidth, shadowMapHeight));
    }

    skyBox.LoadSkybox();
    worldGizmo.Init();
    gridQuad.Init(Transform(glm::vec3(0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(20000.0f)));
    msaaSceneFBO = RenderTarget::CreateMSAATarget(viewportWidth, viewportHeight, 8);
    screenTexFBO = RenderTarget::CreateSceneTarget(viewportWidth, viewportHeight);
}

void Scene::RenderScene(const float deltaTime)
{
    Controller& controller = Controller::GetController();

    if (MasterUI::GetMasterUI().IsMouseOnViewport()) 
        controller.Navigate(playerCamera);

    GLuint shaderID = 0;

    for (int i = 0; i < lights.size(); i++)
    {
        shadowMapFBOs[i].Bind();
        glViewport(0, 0, shadowMapWidth, shadowMapHeight);
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
    glViewport(0, 0, viewportWidth, viewportHeight);
    Engine::GetEngine().ClearWindow(viewportWidth, viewportHeight);

    glDisable(GL_CULL_FACE);
    shaderID = shaders.at(LIGHT_MESH).Activate();
    playerCamera.ApplyCamMatrix(shaderID);
    for (Light* light : lights)
    {
        UploadObjectSelectionData(shaderID, light);
        light->DrawLightMesh(shaderID);
    }

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    ObjectType prevMeshType = NONE;
    for (Mesh* mesh : meshes)
    {
        if (mesh->objectType != prevMeshType)
        {
            prevMeshType = mesh->objectType;
            shaderID = shaders.at(prevMeshType).Activate();
            UploadLightData(shaderID);
            playerCamera.ApplyCamMatrix(shaderID);
        }

        UploadObjectSelectionData(shaderID, mesh);
        mesh->DrawMesh(shaderID);
    }

    glActiveTexture(GL_TEXTURE0);

    if (renderMode == LIT || renderMode == UNLIT)
    {
        shaderID = shaders.at(SKY_BOX).Activate();
        skyBox.DrawSkybox(shaderID);
    }

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    shaderID = shaders.at(GRID).Activate();
    playerCamera.ApplyCamMatrix(shaderID);
    gridQuad.DrawQuad(shaderID);
    glDepthMask(GL_TRUE);

    const unsigned int gizmoSize = 150;
    glViewport(viewportWidth - gizmoSize, viewportHeight - gizmoSize, gizmoSize, gizmoSize);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    shaderID = shaders.at(GIZMO).Activate();
    playerCamera.ApplyGizmoCamMatrix(shaderID);
    worldGizmo.DrawGizmo(shaderID);

    glViewport(0, 0, viewportWidth, viewportHeight);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, msaaSceneFBO.id);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, screenTexFBO.id);
    glBlitFramebuffer(0, 0, viewportWidth, viewportHeight, 0, 0, viewportWidth, viewportHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);              
    glClear(GL_COLOR_BUFFER_BIT);                      
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    msaaSceneFBO.Unbind();

    MasterUI::GetMasterUI().RenderMasterUI(this);
    StatsHelper::GetStatsHelper().ClearDrawCallCount();
}

void Scene::EndScene()
{
    for (Mesh* mesh : meshes) delete mesh;
    for (Light* light : lights) delete light;
}

void Scene::UploadLightData(const GLuint shaderID)
{
    glUniform1i(glGetUniformLocation(shaderID, "renderMode"), (int)renderMode);
    glUniform1f(glGetUniformLocation(shaderID, "lightFarPlane"), lights[0]->farPlane);
    glUniform1i(glGetUniformLocation(shaderID, "lightCount"), lights.size());

    unsigned int reservedSlots = reservedTexSlots.size();

    for (const std::pair<std::string, unsigned int>& slot : reservedTexSlots)
    {
        glUniform1i(glGetUniformLocation(shaderID, slot.first.c_str()), slot.second);
    }

    for (int i = 0; i < lights.size(); i++)
    {
        lights[i]->CalculateLightProjection();

        bool isPointLight = lights[i]->lightDetails.lightType == POINT_LIGHT;
        GLuint nextTexUnit = reservedSlots + i;

        glActiveTexture(GL_TEXTURE0 + nextTexUnit);
        glBindTexture(isPointLight ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, shadowMapFBOs[i].depthTex);
        glUniform1i(glGetUniformLocation(shaderID, ((isPointLight ? "shadowCubeMap[" : "shadowMap[") + std::to_string(i) + "]").c_str()), nextTexUnit);
        glUniform3fv(glGetUniformLocation(shaderID, ("lightPositions[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(lights[i]->lightDetails.location));
        glUniform4fv(glGetUniformLocation(shaderID, ("lightColors[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(lights[i]->lightDetails.color));
        glUniform1i(glGetUniformLocation(shaderID, ("lightTypes[" + std::to_string(i) + "]").c_str()), (int)lights[i]->lightDetails.lightType);
        glUniform1f(glGetUniformLocation(shaderID, ("lightIntensities[" + std::to_string(i) + "]").c_str()), lights[i]->lightDetails.intensity);

        if (lights[i]->lightDetails.lightType == SPOT_LIGHT)
        {
            glUniform3fv(glGetUniformLocation(shaderID, ("lightDirections[" + std::to_string(i) + "]").c_str()), 1, glm::value_ptr(lights[i]->GetDirection()));
            glUniform1f(glGetUniformLocation(shaderID, ("lightInnerCones[" + std::to_string(i) + "]").c_str()), std::cos(glm::radians(lights[i]->lightDetails.innerCone)));
            glUniform1f(glGetUniformLocation(shaderID, ("lightOuterCones[" + std::to_string(i) + "]").c_str()), std::cos(glm::radians(lights[i]->lightDetails.outerCone)));
        }

        if (!isPointLight)
        {
            glUniformMatrix4fv(glGetUniformLocation(shaderID, ("lightProjections[" + std::to_string(i) + "]").c_str()), 1, GL_FALSE, glm::value_ptr(lights[i]->lightDetails.lightProjs[0]));
        }
    }
}

void Scene::UploadObjectSelectionData(const GLuint shaderID, const Object* obj)
{
    glm::vec4 selectedColor = glm::vec4(0.9f, 0.95f, 1.0f, 1.0f);
    float selectedMix = 0.55f;
    bool isSelected = obj == selectedObject ? 1 : 0;

    glUniform1i(glGetUniformLocation(shaderID, "isSelected"), isSelected);
    glUniform1f(glGetUniformLocation(shaderID, "selectMix"), isSelected * selectedMix);
    glUniform4fv(glGetUniformLocation(shaderID, "selectColor"), 1, glm::value_ptr(selectedColor));
}

void Scene::ResizeFBOs(const int viewWidth, const int viewHeight)
{
    msaaSceneFBO.Resize(viewWidth, viewHeight);
    screenTexFBO.Resize(viewWidth, viewHeight);
}

void Scene::SortObjectsByType()
{
    std::sort(meshes.begin(), meshes.end(), [](Mesh* a, Mesh* b)
        {
            return a->objectType < b->objectType;
        }
    );

    std::sort(lights.begin(), lights.end(), [](Light* a, Light* b)
        {
            return a->lightDetails.lightType < b->lightDetails.lightType;
        }
    );
}

float Scene::GetViewportAspectRatio()
{
    return ((float)viewportWidth / viewportHeight);
}
