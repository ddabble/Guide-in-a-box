#include "HUDobject_interface.h"

#include <cstring>
#include <glm/glm.hpp>

static constexpr GLfloat VERTEX_TEMPLATE[] =
{
	0, 0,
	1, 0,
	1, 1,
	0, 1
};

HUDobject_interface::HUDobject_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
	: HUDobject_interface(program, graphicsObjectManager, { 0.0f, 0.0f }, (GLfloat)graphicsObjectManager.getWindow().getWidth(), (GLfloat)graphicsObjectManager.getWindow().getHeight()) {}

HUDobject_interface::HUDobject_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager, glm::vec2 pos, GLfloat width, GLfloat height)
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

void HUDobject_interface::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
{
	// TODO: Change object's position with matrices instead
	glUniform2fv(m_vertexData_uniformIndex, 8, m_vertexData);

	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void HUDobject_interface::_setCoords(glm::vec2 pos, GLfloat width, GLfloat height, GLfloat* vertexData)
{
	const GLfloat newVertexData[] =
	{
		pos.x,         pos.y,
		pos.x + width, pos.y,
		pos.x + width, pos.y + height,
		pos.x,         pos.y + height,
	};

	std::memcpy(vertexData, newVertexData, sizeof(newVertexData));
}

void HUDobject_interface::_setWidth(GLfloat width, GLfloat* vertexData)
{
	vertexData[2] = vertexData[0] + width;
	vertexData[4] = vertexData[0] + width;
}

void HUDobject_interface::_setHeight(GLfloat height, GLfloat* vertexData)
{
	vertexData[5] = vertexData[1] + height;
	vertexData[7] = vertexData[1] + height;
}

void HUDobject_interface::_move(glm::vec2 direction, GLfloat* vertexData)
{
	for (int i = 0; i < 8; i += 2)
	{
		vertexData[i] += direction.x;
		vertexData[i + 1] += direction.y;
	}
}

void HUDobject_interface::_moveTo(glm::vec2 pos, GLfloat* vertexData)
{
	_setCoords(pos, _getWidth(vertexData), _getHeight(vertexData), vertexData);
}

void HUDobject_interface::_zoom(GLfloat newWidth, GLfloat newHeight, glm::vec2 focus, GLfloat* vertexData)
{
	glm::clamp(focus, 0.0f, 1.0f);

	GLfloat oldWidth = _getWidth(vertexData);
	GLfloat oldHeight = _getHeight(vertexData);

	if (newWidth < 0.0f)
	{
		if (newHeight < 0.0f)
			return;

		newWidth = newHeight * (oldWidth / oldHeight);
	}

	if (newHeight < 0.0f)
		newHeight = newWidth / (oldWidth / oldHeight);

	GLfloat deltaWidth = newWidth - oldWidth;
	GLfloat deltaHeight = newHeight - oldHeight;

	glm::vec2 cursorPosInTexCoords{ ((focus.x * 2 - 1) - vertexData[0]) / oldWidth,
									((focus.y * 2 - 1) - vertexData[1]) / oldHeight };

	for (int i = 0; i < 8; i += 2)
	{
		vertexData[i] += (VERTEX_TEMPLATE[i] - cursorPosInTexCoords.x) * deltaWidth;
		vertexData[i + 1] += (VERTEX_TEMPLATE[i + 1] - cursorPosInTexCoords.y) * deltaHeight;
	}
}
