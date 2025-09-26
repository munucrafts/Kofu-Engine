#include "Mesh.h"
#include "Engine.h"
#include <glm/gtc/type_ptr.hpp>

void Mesh::LoadMesh(const std::string& path)
{
}

void Mesh::InitMesh()
{
    // Vertices coordinates
    GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    vao.Init();
    vbo.Init(vertices, sizeof(vertices));
    ebo.Init(indices, sizeof(indices));
    texture.Init();

    vao.Bind();
    vbo.Bind();
    ebo.Bind();
    texture.Bind();

    vao.LinkAttribs(vbo, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
    vao.LinkAttribs(vbo, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    vao.LinkAttribs(vbo, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
    texture.Unind();
}

void Mesh::ClearMesh()
{
    vbo.Delete();
    vao.Delete();
    ebo.Delete();
    texture.Delete();
}

void Mesh::DrawMesh()
{
    vao.Bind();
    texture.Bind();

    model = glm::mat4(1.0f);
    model = glm::translate(model, transform.location);
    model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, transform.scale);

    int camMatLoc = glGetUniformLocation(Engine::GetEngine().activeShaderProgramID, "model");
    glUniformMatrix4fv(camMatLoc, 1, GL_FALSE, glm::value_ptr(model));

    GLuint uniTex0 = glGetUniformLocation(Engine::GetEngine().activeShaderProgramID, "tex0");
    glUniform1i(uniTex0, 0);

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}