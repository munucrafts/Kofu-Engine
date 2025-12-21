#pragma once
#include "geometry/StaticMesh.h"
#include "Engine.h"
#include <glm/gtc/type_ptr.hpp>

StaticMesh::StaticMesh()
{
    meshType = STATIC_MESH;
}

StaticMesh::StaticMesh(const std::vector<Vertex> verts, const std::vector<GLuint> inds)
{
    meshType = STATIC_MESH;
    vertices = verts;
    indices = inds;
}

void StaticMesh::InitMeshManually()
{
    vao.Init();
    vao.Bind();
    vbo.Init(vertices);
    vbo.Bind();
    ebo.Init(indices);
    ebo.Bind();

    vao.LinkAttribs(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.LinkAttribs(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao.LinkAttribs(vbo, 2, 4, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    vao.LinkAttribs(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(10 * sizeof(float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    for (std::pair<const std::string, Texture>& tex : textures)
    {
        tex.second.Unbind();
    }
}

void StaticMesh::InitMesh()
{
    vao.Init();
    vao.Bind();
    vbo.Init(vertices);
    vbo.Bind();
    ebo.Init(indices);
    ebo.Bind();

    vao.LinkAttribs(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.LinkAttribs(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao.LinkAttribs(vbo, 2, 4, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    vao.LinkAttribs(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(10 * sizeof(float)));
    
    unsigned int texUnit = 0;

    for (auto& tex : textures)
    {
        tex.second.Init();
        tex.second.Bind(texUnit++);
    }
}

void StaticMesh::ClearMesh()
{
    vbo.Delete();
    vao.Delete();
    ebo.Delete();

    for (auto& tex : textures)
    {
        tex.second.Delete();
    }
}

void StaticMesh::DrawMesh(int shaderID)
{
    vao.Bind();

    unsigned int texUnit = 0;
    for (auto& tex : textures)
    {
        tex.second.Bind(texUnit++);
    }

    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, transform.location);
    modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMat = glm::scale(modelMat, transform.scale);

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}