#pragma once
#include <vector>
#include <Mesh.h>
#include "tiny_gltf.h"
#include <Scene.h>

class GLTFLoader
{
public:
	std::vector<Mesh*> LoadGltfModel(const std::string& path);
	static GLTFLoader& GetGltfLoader();

private:
	tinygltf::Model gltfModel;
	tinygltf::TinyGLTF gltfLoader;
	std::vector<Mesh*> meshesArray;

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

