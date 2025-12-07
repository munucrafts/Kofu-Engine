#pragma once
#include <vector>
#include <geometry/mesh.h>
#include "tiny_gltf.h"
#include <rendering/scene.h>

class GLTFLoader
{
public:
	std::vector<Mesh*> LoadGltfModel(const std::string& path, MeshData meshDetails);
	static GLTFLoader& GetGltfLoader();

private:
	tinygltf::Model gltfModel;
	tinygltf::TinyGLTF gltfLoader;
	std::vector<Mesh*> meshesArray;
	MeshData meshData;
	std::string modelPath;

private:
	void LoadGltfNode(tinygltf::Node& node);
	void LoadGltfMesh(tinygltf::Mesh& mesh);
	void LoadGltfSubMesh(tinygltf::Primitive& subMesh);

private:
	GLTFLoader() = default;
	GLTFLoader(const GLTFLoader& instance) = delete;
	~GLTFLoader() = default;
	GLTFLoader& operator= (GLTFLoader& instance) = delete;
};