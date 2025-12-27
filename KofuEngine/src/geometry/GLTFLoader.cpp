#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "geometry/GLTFLoader.h"
#include "rendering/scene.h"
#include <iostream>

GLTFLoader& GLTFLoader::GetGltfLoader()
{
	static GLTFLoader instance;
	return instance;
}

std::vector<Mesh*> GLTFLoader::LoadGltfModel(const std::string& path, const MeshData& meshDetails)
{
	std::filesystem::path filePath(path);
	modelPath = filePath.parent_path().string();

	meshData = meshDetails;

	std::string error, warning;
	gltfLoader.LoadASCIIFromFile(&gltfModel, &error, &warning, path);

	if (!warning.empty())
		std::cout << "Warning - " << warning << std::endl;

	if (!error.empty())
		std::cout << "Error - " << error << std::endl;

	const tinygltf::Scene& scene = gltfModel.scenes[gltfModel.defaultScene];

	for (int i = 0; i < scene.nodes.size(); i++)
	{
		if (scene.nodes[i] >= 0 && scene.nodes[i] < gltfModel.nodes.size())
		{
			LoadGltfNode(gltfModel.nodes[scene.nodes[i]]);
		}
	}

	std::vector<Mesh*> meshes = meshesArray;
	meshesArray.clear();
	meshData = {};
	modelPath = "";

	return meshes;
}

void GLTFLoader::LoadGltfNode(tinygltf::Node& node)
{
	if (node.mesh >= 0)
	{
		tinygltf::Mesh& mesh = gltfModel.meshes[node.mesh];
		LoadGltfMesh(mesh);
	}

	for (int childIndex : node.children)
	{
		LoadGltfNode(gltfModel.nodes[childIndex]);
	}
}

void GLTFLoader::LoadGltfMesh(tinygltf::Mesh& mesh)
{
	for (tinygltf::Primitive& primitive : mesh.primitives)
	{
		LoadGltfSubMesh(primitive);
	}
}

void GLTFLoader::LoadGltfSubMesh(tinygltf::Primitive& subMesh)
{
	std::map<std::string, int>& attribs = subMesh.attributes;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec2> texCoords;

	if (attribs.find("POSITION") != attribs.end())
	{
		tinygltf::Accessor& accessor = gltfModel.accessors[attribs.at("POSITION")];
		tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
		tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

		float* data = reinterpret_cast<float*>(&buffer.data[accessor.byteOffset + bufferView.byteOffset]);

		for (int i = 0; i < accessor.count; i++)
		{
			float x = data[i * 3 + 0];
			float y = data[i * 3 + 1];
			float z = data[i * 3 + 2];

			positions.push_back(glm::vec3(x, y, z));
		}
	}

	if (attribs.find("NORMAL") != attribs.end())
	{
		tinygltf::Accessor& accessor = gltfModel.accessors[attribs.at("NORMAL")];
		tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
		tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

		float* data = reinterpret_cast<float*>(&buffer.data[accessor.byteOffset + bufferView.byteOffset]);

		for (int i = 0; i < accessor.count; i++)
		{
			float x = data[i * 3 + 0];
			float y = data[i * 3 + 1];
			float z = data[i * 3 + 2];

			normals.push_back(glm::vec3(x, y, z));
		}
	}

	if (attribs.find("COLOR_0") != attribs.end())
	{
		tinygltf::Accessor& accessor = gltfModel.accessors[attribs.at("COLOR_0")];
		tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
		tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

		int componentCount = tinygltf::GetNumComponentsInType(accessor.type);

		float* data = reinterpret_cast<float*>(&buffer.data[accessor.byteOffset + bufferView.byteOffset]);

		for (int i = 0; i < accessor.count; i++)
		{
			float r = data[i * 4 + 0];
			float g = data[i * 4 + 1];
			float b = data[i * 4 + 2];
			float a = (componentCount == 4) ? data[i * 4 + 3] : 1.0f;

			colors.push_back(glm::vec4(r, g, b, a));
		}
	}

	if (attribs.find("TEXCOORD_0") != attribs.end())
	{
		tinygltf::Accessor& accessor = gltfModel.accessors[attribs.at("TEXCOORD_0")];
		tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
		tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

		float* data = reinterpret_cast<float*>(&buffer.data[accessor.byteOffset + bufferView.byteOffset]);

		for (int i = 0; i < accessor.count; i++)
		{
			float u = data[i * 2 + 0];
			float v = data[i * 2 + 1];

			texCoords.push_back(glm::vec2(u, v));
		}
	}

	if (subMesh.indices >= 0)
	{
		tinygltf::Accessor& accessor = gltfModel.accessors[subMesh.indices];
		tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
		tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

		void* dataPtr = &buffer.data[accessor.byteOffset + bufferView.byteOffset];

		switch (accessor.componentType)
		{
		case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
		{
			uint16_t* buf = reinterpret_cast<uint16_t*>(dataPtr);

			for (size_t i = 0; i < accessor.count; ++i)
				indices.push_back(buf[i]);

			break;
		}
		case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
		{
			uint32_t* buf = reinterpret_cast<uint32_t*>(dataPtr);

			for (size_t i = 0; i < accessor.count; ++i)
				indices.push_back(buf[i]);

			break;
		}
		default:
			throw std::runtime_error("Unsupported index type");
		}
	}

	for (int i = 0; i < positions.size(); i++)
	{
		glm::vec3 normal = (i < normals.size()) ? normals[i] : glm::vec3(0.0f);
		glm::vec4 color = (i < colors.size()) ? colors[i] : glm::vec4(1.0f);
		glm::vec2 texCoord = (i < texCoords.size()) ? texCoords[i] : glm::vec2(0.0f);

		vertices.push_back({ positions[i], normal, color, texCoord });
	}

	Mesh* mesh = nullptr;

	switch (meshData.meshType)
	{
	case(STATIC_MESH):
		{
			mesh = new StaticMesh(vertices, indices);
			break;
		}
	case(INSTANCED_STATIC_MESH):
		{
			mesh = new InstancedStaticMesh(vertices, indices, meshData.instanceCount);
			break;
		}
	case(SKELETAL_MESH):
		{
			mesh = new SkeletalMesh(vertices, indices);
			break;
		}
	}

	if (!mesh) return;

	mesh->transform = meshData.transform;

	int materialIndex = subMesh.material;
	if (materialIndex >= 0)
	{
		tinygltf::Material& material = gltfModel.materials[materialIndex];

		int baseTexIndex = material.pbrMetallicRoughness.baseColorTexture.index;
		if (baseTexIndex >= 0)
		{
			int imgIndex = gltfModel.textures[baseTexIndex].source;
			std::string textureName = modelPath + "/" + gltfModel.images[imgIndex].uri;
			mesh->textures["baseTex"] = Texture(textureName.c_str());
		}

		int normalTexIndex = material.normalTexture.index;
		if (normalTexIndex >= 0)
		{
			int imgIndex = gltfModel.textures[normalTexIndex].source;
			std::string textureName = modelPath + "/" + gltfModel.images[imgIndex].uri;
			mesh->textures["normalTex"] = Texture(textureName.c_str());
		}

		int occlusionTexIndex = material.occlusionTexture.index;
		if (occlusionTexIndex >= 0)
		{
			int imgIndex = gltfModel.textures[occlusionTexIndex].source;
			std::string textureName = modelPath + "/" + gltfModel.images[imgIndex].uri;
			mesh->textures["occlusionTex"] = Texture(textureName.c_str());
		}

		int metallicTexIndex = material.pbrMetallicRoughness.metallicRoughnessTexture.index;
		if (metallicTexIndex >= 0)
		{
			int imgIndex = gltfModel.textures[metallicTexIndex].source;
			std::string textureName = modelPath + "/" + gltfModel.images[imgIndex].uri;
			mesh->textures["metallicTex"] = Texture(textureName.c_str());
		}
	}

	meshesArray.emplace_back(mesh);
}
