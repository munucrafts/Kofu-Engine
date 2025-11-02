#include "Mesh.h"
#include "Engine.h"
#include <glm/gtc/type_ptr.hpp>


Mesh::Mesh(std::vector<Vertex> verts, std::vector<GLuint> inds)
{
    vertices = verts;
    indices = inds;

    //// Reset normals
    //for (auto& v : vertices)
    //    v.normal = glm::vec3(0.0f);

    //// Accumulate face normals for each vertex
    //for (size_t i = 0; i < indices.size(); i += 3)
    //{
    //    GLuint i0 = indices[i];
    //    GLuint i1 = indices[i + 1];
    //    GLuint i2 = indices[i + 2];

    //    glm::vec3 v0 = vertices[i0].position;
    //    glm::vec3 v1 = vertices[i1].position;
    //    glm::vec3 v2 = vertices[i2].position;

    //    glm::vec3 edge1 = v1 - v0;
    //    glm::vec3 edge2 = v2 - v0;
    //    glm::vec3 faceNormal = glm::normalize(glm::cross(edge1, edge2));

    //    // Add the face normal to each vertex normal
    //    vertices[i0].normal += faceNormal;
    //    vertices[i1].normal += faceNormal;
    //    vertices[i2].normal += faceNormal;
    //}

    //// Normalize all vertex normals
    //for (auto& v : vertices)
    //    v.normal = glm::normalize(v.normal);
}

void Mesh::InitMeshManually()
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
    baseTex.Unbind();
    normalTex.Unbind();
    metallicTex.Unbind();
    occlusionTex.Unbind();
}

void Mesh::InitMesh()
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

    baseTex.Init();
    normalTex.Init();
    metallicTex.Init();
    occlusionTex.Init();

    baseTex.Bind(GL_TEXTURE0);
    normalTex.Bind(GL_TEXTURE1);
    occlusionTex.Bind(GL_TEXTURE2);
    metallicTex.Bind(GL_TEXTURE3);

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
    baseTex.Unbind();
    normalTex.Unbind();
    metallicTex.Unbind();
    occlusionTex.Unbind();
}

void Mesh::ClearMesh()
{
    vbo.Delete();
    vao.Delete();
    ebo.Delete();
    baseTex.Delete();
}

void Mesh::DrawMesh()
{
    vao.Bind();
    baseTex.Bind(GL_TEXTURE0);
    normalTex.Bind(GL_TEXTURE1);
    occlusionTex.Bind(GL_TEXTURE2);
    metallicTex.Bind(GL_TEXTURE3);

    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, transform.location);
    modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMat = glm::scale(modelMat, transform.scale);

    int camMatLoc = glGetUniformLocation(Engine::GetEngine().activeShaderProgram, "modelMat");
    glUniformMatrix4fv(camMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

    GLuint baseTexLoc = glGetUniformLocation(Engine::GetEngine().activeShaderProgram, "baseTex");
    glUniform1i(baseTexLoc, 0);

    GLuint normalTexLoc = glGetUniformLocation(Engine::GetEngine().activeShaderProgram, "normalTex");
    glUniform1i(normalTexLoc, 1);

    GLuint occlusionTexLoc = glGetUniformLocation(Engine::GetEngine().activeShaderProgram, "occlusionTex");
    glUniform1i(occlusionTexLoc, 2);

    GLuint metallicTexLoc = glGetUniformLocation(Engine::GetEngine().activeShaderProgram, "metallicTex");
    glUniform1i(metallicTexLoc, 3);

    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}