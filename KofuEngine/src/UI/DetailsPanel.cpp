#pragma once
#include "rendering/Scene.h"
#include "DetailsPanel.h"
#include "Components/Components.h"
#include <imgui.h>
#include <utilities/Util.h>
#include "TransformPanel.h"
#include "MeshPanel.h"
#include "CameraPanel.h"
#include "LightPanel.h"

void DetailsPanel::RenderUI(Scene* activeScene)
{
	ImGui::Begin("Details");

	if (activeScene->selectedObject == nullptr || activeScene->selectedObject->objectID == "None")
	{
		ImGui::Text("No Selection");
		ImGui::End();
		return;
	}

	Object* obj = activeScene->selectedObject;
	ObjectType objType = obj->objectType;
	std::string objIDText = "Object ID : " + obj->objectID;
	std::string objTypeText = "Object Type : " + Util::EnumToString(objType);

	ImVec4 normalColor = ImGui::GetStyleColorVec4(ImGuiCol_Button);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, normalColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, normalColor);

	ImGui::Button(objIDText.c_str());
	ImGui::Button(objTypeText.c_str());

	ImGui::PopStyleColor(2);

	TransformPanel transformPanel;

    switch (objType)
    {
    case STATIC_MESH:
    case INSTANCED_STATIC_MESH:
    case SKELETAL_MESH:
    {
        Mesh* mesh = static_cast<Mesh*>(obj);
        transformPanel.RenderUI(mesh->transform, true, true, true);

        MeshPanel meshPanel;
        meshPanel.RenderUI(mesh, objType);
    }
    break;

    case SPOT_LIGHT:
    case DIRECTIONAL_LIGHT:
    case POINT_LIGHT:
    {
        Light* light = static_cast<Light*>(obj);
        Transform lightTrans(light->lightDetails.location, light->lightDetails.rotation);
        transformPanel.RenderUI(lightTrans, true, true, false);
        light->lightDetails.location = lightTrans.location;
        light->lightDetails.rotation = lightTrans.rotation;

        LightPanel lightPanel;
        lightPanel.RenderUI(light, objType);
    }
    break;

    case CAMERA:
    {
        Camera* cam = static_cast<Camera*>(obj);
        Transform camTrans(cam->location);
        transformPanel.RenderUI(camTrans, true, false, false);
        cam->location = camTrans.location;

        CameraPanel camPanel;
        camPanel.RenderUI(cam);
    }
    break;

    case SKY_BOX:
    {
        Skybox* skybox = static_cast<Skybox*>(obj);
        Transform skyboxTrans({});
        transformPanel.RenderUI(skyboxTrans, false, false, false);
    }
    break;

    default:
        break;
    }

	ImGui::End();
}
