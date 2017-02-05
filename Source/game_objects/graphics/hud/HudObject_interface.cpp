#include "HudObject_interface.h"

#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

static constexpr GLfloat VERTEX_TEMPLATE[] =
{
	0, 0,
	1, 0,
	1, 1,
	0, 1
};

HudObject_interface::HudObject_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager) : m_graphicsObjectManager(graphicsObjectManager)
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

	m_vertexDataUniformIndex = glGetUniformLocation(program, "vertexData");

	m_resizeUniformIndex = glGetUniformLocation(program, "resize");
	glUniformMatrix4fv(m_resizeUniformIndex, 1, GL_FALSE, glm::value_ptr(graphicsObjectManager.getResizeMatrix()));
}

void HudObject_interface::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
{
	glUniform2fv(m_vertexDataUniformIndex, 8, m_vertexData);

	glBindVertexArray(m_vertexArrayObject);
	// TODO: glDrawElements instead?
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void HudObject_interface::onFramebufferResize(int lastWidth, int lastHeight, int newWidth, int newHeight, GLuint program)
{
	if (!m_preserveAspectRatioOnResize)
		return;

	glUseProgram(program);
	glUniformMatrix4fv(m_resizeUniformIndex, 1, GL_FALSE, glm::value_ptr(m_graphicsObjectManager.getResizeMatrix()));
}

void HudObject_interface::setFields(unsigned int width, unsigned int height, int xPixelPos, int yPixelPos, bool preserveAspectRatioOnResize)
{
	HudObject_interface::setFields(width, height, pixelsToWindowCoordWidth(xPixelPos) - 1, pixelsToWindowCoordHeight(yPixelPos) - 1, preserveAspectRatioOnResize);
}

void HudObject_interface::setFields(unsigned int width, unsigned int height, GLfloat xPos, GLfloat yPos, bool preserveAspectRatioOnResize)
{
	GLfloat widthRatio = pixelsToWindowCoordWidth(width);
	GLfloat heightRatio = pixelsToWindowCoordHeight(height);

	GLfloat vertexData[] =
	{
		// Vertices
		xPos,			   yPos,
		xPos + widthRatio, yPos,
		xPos + widthRatio, yPos + heightRatio,
		xPos,			   yPos + heightRatio,
		// Texture coordinates
		0, 0,
		1, 0,
		1, 1,
		0, 1
	};

	m_pixelWidth = width;
	m_pixelHeight = height;
	std::memcpy(m_vertexData, vertexData, sizeof(vertexData));
	m_preserveAspectRatioOnResize = preserveAspectRatioOnResize;
}

void HudObject_interface::setWidth(int width_pixels, bool preserveAspectRatio)
{
	_setWidth(pixelsToWindowCoordWidth(width_pixels), preserveAspectRatio, m_vertexData);
}

void HudObject_interface::setHeight(int height_pixels, bool preserveAspectRatio)
{
	_setHeight(pixelsToWindowCoordHeight(height_pixels), preserveAspectRatio, m_vertexData);
}

void HudObject_interface::setWidth(GLfloat width_windowCoords, bool preserveAspectRatio)
{
	_setWidth(width_windowCoords, preserveAspectRatio, m_vertexData);
}

void HudObject_interface::setHeight(GLfloat height_windowCoords, bool preserveAspectRatio)
{
	_setHeight(height_windowCoords, preserveAspectRatio, m_vertexData);
}

void HudObject_interface::move(int xDirection_pixels, int yDirection_pixels)
{
	_move(pixelsToWindowCoordWidth(xDirection_pixels), pixelsToWindowCoordHeight(yDirection_pixels), m_vertexData);
}

void HudObject_interface::move(GLfloat xDirection_windowCoords, GLfloat yDirection_windowCoords)
{
	_move(xDirection_windowCoords, yDirection_windowCoords, m_vertexData);
}

void HudObject_interface::moveTo(int xPixelPos, int yPixelPos)
{
	_moveTo(pixelsToWindowCoordWidth(xPixelPos) - 1, pixelsToWindowCoordHeight(yPixelPos) - 1, m_vertexData);
}

void HudObject_interface::moveTo(GLfloat xWindowPos, GLfloat yWindowPos)
{
	_moveTo(xWindowPos, yWindowPos, m_vertexData);
}

void HudObject_interface::zoom(int newWidth_pixels, int newHeight_pixels, GLfloat focusX, GLfloat focusY)
{
	_zoom(pixelsToWindowCoordWidth(newWidth_pixels), pixelsToWindowCoordHeight(newHeight_pixels), focusX, focusY, m_vertexData);
}

void HudObject_interface::zoom(GLfloat newWidth_windowCoords, GLfloat newHeight_windowCoords, GLfloat focusX, GLfloat focusY)
{
	_zoom(newWidth_windowCoords, newHeight_windowCoords, focusX, focusY, m_vertexData);
}

template<typename numeric_type> GLfloat HudObject_interface::pixelsToWindowCoordWidth(numeric_type pixels)
{
	return 2 * (GLfloat)pixels / m_graphicsObjectManager.getWindow().getWidth();
}

template<typename numeric_type> GLfloat HudObject_interface::pixelsToWindowCoordHeight(numeric_type pixels)
{
	return 2 * (GLfloat)pixels / m_graphicsObjectManager.getWindow().getHeight();
}

void HudObject_interface::_setWidth(GLfloat width_windowCoords, bool preserveAspectRatio, GLfloat vertexData[8])
{
	if (preserveAspectRatio)
	{
		GLfloat aspectRatio = (vertexData[2] - vertexData[0]) / (vertexData[5] - vertexData[1]);
		GLfloat newHeight = width_windowCoords / aspectRatio;

		vertexData[5] = vertexData[1] + newHeight;
		vertexData[7] = vertexData[1] + newHeight;
	}

	vertexData[2] = vertexData[0] + width_windowCoords;
	vertexData[4] = vertexData[0] + width_windowCoords;
}

void HudObject_interface::_setHeight(GLfloat height_windowCoords, bool preserveAspectRatio, GLfloat vertexData[8])
{
	if (preserveAspectRatio)
	{
		GLfloat aspectRatio = (vertexData[2] - vertexData[0]) / (vertexData[5] - vertexData[1]);
		GLfloat newWidth = height_windowCoords * aspectRatio;

		vertexData[2] = vertexData[0] + newWidth;
		vertexData[4] = vertexData[0] + newWidth;
	}

	vertexData[5] = vertexData[1] + height_windowCoords;
	vertexData[7] = vertexData[1] + height_windowCoords;
}

void HudObject_interface::_move(GLfloat xDirection, GLfloat yDirection, GLfloat vertexData[8])
{
	for (int i = 0; i < 8; i += 2)
	{
		vertexData[i] += xDirection;
		vertexData[i + 1] += yDirection;
	}
}

void HudObject_interface::_moveTo(GLfloat xPos, GLfloat yPos, GLfloat vertexData[8])
{
	GLfloat windowWidth = getWindowCoordWidth();
	GLfloat windowHeight = getWindowCoordHeight();

	for (int i = 0; i < 8; i += 2)
	{
		vertexData[i] = xPos + VERTEX_TEMPLATE[i] * windowWidth;
		vertexData[i + 1] = yPos + VERTEX_TEMPLATE[i + 1] * windowHeight;
	}
}

void HudObject_interface::_zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX, GLfloat focusY, GLfloat vertexData[8])
{
	focusX = glm::clamp(focusX, 0.0f, 1.0f);
	focusY = glm::clamp(focusY, 0.0f, 1.0f);

	GLfloat oldWidth = getWindowCoordWidth();
	GLfloat oldHeight = getWindowCoordHeight();

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
