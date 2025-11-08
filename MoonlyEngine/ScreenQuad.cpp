#include "ScreenQuad.h"

void ScreenQuad::Init()
{
	vao.Init();
	vao.Bind();

	vbo.Init(vertices, sizeof(vertices));
	vbo.Bind();

	vao.LinkAttribs(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	vao.LinkAttribs(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}
void ScreenQuad::Draw()
{
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao.Unbind();
}
