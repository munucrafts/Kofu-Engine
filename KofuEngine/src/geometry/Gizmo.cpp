#include "Gizmo.h"
#include <glad/glad.h>
#include "GLTFLoader.h"

void Gizmo::Init()
{
	MeshData meshData;
	meshData.meshType = STATIC_MESH;
	gizmoMesh = GLTFLoader::GetGltfLoader().LoadGltfModel("./assets/models/Gizmo/gizmo.gltf", meshData)[0];
	gizmoMesh->InitMesh();

	StaticMesh* smGizmoPtr = static_cast<StaticMesh*>(gizmoMesh);
	smGizmoPtr->transform.scale = glm::vec3(0.025f);
	glm::mat4& gizmoModel = smGizmoPtr->modelMat;
	gizmoModel[3] = glm::vec4(0, 0, 0, 1);
	gizmoModel[0] = glm::normalize(gizmoModel[0]);
	gizmoModel[1] = glm::normalize(gizmoModel[1]);
	gizmoModel[2] = glm::normalize(gizmoModel[2]);
}

void Gizmo::DrawGizmo(GLuint shaderID)
{
	gizmoMesh->DrawMesh(shaderID);
}
