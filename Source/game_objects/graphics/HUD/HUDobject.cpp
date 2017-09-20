#include "HUDobject.h"

#include <cstring>
#include <glm/glm.hpp>

#include "../GraphicsObjectManager.h"
#include "../../../screen/Window.h"

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

	glGenBuffers(1, &m_vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexData), m_vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 2 * 4));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenTextures(1, &m_textureObject);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);
}

void HUDobject::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
{
	glBindVertexArray(m_vertexArrayObject);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
