#include "Mesh.h"

void Mesh::LoadMesh(const std::string& path)
{
}

void Mesh::InitMesh()
{
    // Vertices coordinates
    GLfloat vertices[] =
    {
        //      COORDINATES              COLORS          TexCoord 
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,  // Lower left corner
            -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,  // Upper left corner
             0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,  // Upper right corner
             0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f   // Lower right corner
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 2, 1, // Upper triangle
        0, 3, 2  // Lower triangle
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

void Mesh::DrawMesh(const GLuint& shaderProgramID)
{
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    float uniScale = glGetUniformLocation(shaderProgramID, "scale");
    float uniIntensity = glGetUniformLocation(shaderProgramID, "intensity");
    GLuint uniTex0 = glGetUniformLocation(shaderProgramID, "tex0");

    glUniform1f(uniScale, 1.5f);
    glUniform1f(uniIntensity, 1.0f);
    glUniform1i(uniTex0, 0);

    vao.Bind();
    texture.Bind();
}
