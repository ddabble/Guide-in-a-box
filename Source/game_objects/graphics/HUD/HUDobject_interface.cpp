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

HUDobject_interface::HUDobject_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager) : m_graphicsObjectManager(graphicsObjectManager)
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

void HUDobject_interface::setFields(unsigned int width, unsigned int height, int xPos, int yPos, bool preserveAspectRatioOnResize)
{
	GLfloat vertexData[] =
	{
		// Vertices
		xPos,         yPos,
		xPos + width, yPos,
		xPos + width, yPos + height,
		xPos,         yPos + height,
		// Texture coordinates
		0, 0,
		1, 0,
		1, 1,
		0, 1
	};

	std::memcpy(m_vertexData, vertexData, sizeof(vertexData));
	m_preserveAspectRatioOnResize = preserveAspectRatioOnResize;
}

void HUDobject_interface::setWidth(int width, bool preserveAspectRatio)
{
	_setWidth(width, preserveAspectRatio, m_vertexData);
}

void HUDobject_interface::setHeight(int height, bool preserveAspectRatio)
{
	_setHeight(height, preserveAspectRatio, m_vertexData);
}

void HUDobject_interface::move(int xDirection, int yDirection)
{
	_move(xDirection, yDirection, m_vertexData);
}

void HUDobject_interface::moveTo(int xPos, int yPos)
{
	_moveTo(xPos - 1, yPos - 1, m_vertexData);
}

void HUDobject_interface::zoom(int newWidth, int newHeight, GLfloat focusX, GLfloat focusY)
{
	_zoom(newWidth, newHeight, focusX, focusY, m_vertexData);
}

void HUDobject_interface::_setWidth(GLfloat width, bool preserveAspectRatio, GLfloat vertexData[8])
{
	if (preserveAspectRatio)
	{
		GLfloat aspectRatio = (vertexData[2] - vertexData[0]) / (vertexData[5] - vertexData[1]);
		GLfloat newHeight = width / aspectRatio;

		vertexData[5] = vertexData[1] + newHeight;
		vertexData[7] = vertexData[1] + newHeight;
	}

	vertexData[2] = vertexData[0] + width;
	vertexData[4] = vertexData[0] + width;
}

void HUDobject_interface::_setHeight(GLfloat height, bool preserveAspectRatio, GLfloat vertexData[8])
{
	if (preserveAspectRatio)
	{
		GLfloat aspectRatio = (vertexData[2] - vertexData[0]) / (vertexData[5] - vertexData[1]);
		GLfloat newWidth = height * aspectRatio;

		vertexData[2] = vertexData[0] + newWidth;
		vertexData[4] = vertexData[0] + newWidth;
	}

	vertexData[5] = vertexData[1] + height;
	vertexData[7] = vertexData[1] + height;
}

void HUDobject_interface::_move(GLfloat xDirection, GLfloat yDirection, GLfloat vertexData[8])
{
	for (int i = 0; i < 8; i += 2)
	{
		vertexData[i] += xDirection;
		vertexData[i + 1] += yDirection;
	}
}

void HUDobject_interface::_moveTo(GLfloat xPos, GLfloat yPos, GLfloat vertexData[8])
{
	GLint windowWidth = getWidth();
	GLint windowHeight = getHeight();

	for (int i = 0; i < 8; i += 2)
	{
		vertexData[i] = xPos + VERTEX_TEMPLATE[i] * windowWidth;
		vertexData[i + 1] = yPos + VERTEX_TEMPLATE[i + 1] * windowHeight;
	}
}

void HUDobject_interface::_zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX, GLfloat focusY, GLfloat vertexData[8])
{
	focusX = glm::clamp(focusX, 0.0f, 1.0f);
	focusY = glm::clamp(focusY, 0.0f, 1.0f);

	GLint oldWidth = getWidth();
	GLint oldHeight = getHeight();

	if (newWidth < 0)
	{
		if (newHeight < 0)
			return;

		newWidth = newHeight * (oldWidth / oldHeight);
	}

	if (newHeight < 0)
		newHeight = newWidth / (oldWidth / oldHeight);

	GLfloat deltaWidth = newWidth - oldWidth;
	GLfloat deltaHeight = newHeight - oldHeight;

	GLfloat cursorPosInTexCoords_x = ((focusX * 2 - 1) - m_vertexData[0]) / oldWidth;
	GLfloat cursorPosInTexCoords_y = ((focusY * 2 - 1) - m_vertexData[1]) / oldHeight;

	for (int i = 0; i < 8; i += 2)
	{
		vertexData[i] += (VERTEX_TEMPLATE[i] - cursorPosInTexCoords_x) * deltaWidth;
		vertexData[i + 1] += (VERTEX_TEMPLATE[i + 1] - cursorPosInTexCoords_y) * deltaHeight;
	}
}
