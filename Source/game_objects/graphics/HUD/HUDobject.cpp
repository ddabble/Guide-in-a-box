#include "HUDobject.h"

#include <cstring>
#include <glm/glm.hpp>


HUDobject::HUDobject(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
	: HUDobject(program, graphicsObjectManager, { 0.0f, 0.0f }, (GLfloat)graphicsObjectManager.getWindow().getWidth(), (GLfloat)graphicsObjectManager.getWindow().getHeight()) {}

HUDobject::HUDobject(GLuint program, const GraphicsObjectManager& graphicsObjectManager, glm::vec2 pos, GLfloat width, GLfloat height)
	: m_vertexData
{
	// Vertices
	pos.x,         pos.y,
	pos.x + width, pos.y,
	pos.x + width, pos.y + height,
	pos.x,         pos.y + height,
	// Texture coordinates
	0, 0,
	1, 0,
	1, 1,
	0, 1
}
{
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	constexpr GLint vertexIndices[] = { 0, 1, 2, 3 };

	GLuint buf;
	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);

	// Notice the "I" and the lack of a "normalized" argument
	glVertexAttribIPointer(0, 1, GL_INT, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	m_vertexData_uniformIndex = glGetUniformLocation(program, "vertexData");
}

void HUDobject::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
