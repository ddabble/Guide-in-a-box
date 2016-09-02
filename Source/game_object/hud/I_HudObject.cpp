#include "I_HudObject.h"

#include <cstring>
#include <glm/glm.hpp>

#include "../../Game.h"

static constexpr GLfloat VERTEX_TEMPLATE[] =
{
	0, 0,
	1, 0,
	1, 1,
	0, 1
};

void I_HudObject::onFramebufferResize(int lastWidth, int lastHeight, int newWidth, int newHeight)
{
	if (!m_preserveAspectRatioOnResize)
		return;

	GLfloat newXWindowPos = (lastWidth * (m_vertexData[0] + 1)) / newWidth - 1;
	GLfloat newYWindowPos = (lastHeight * (m_vertexData[1] + 1)) / newHeight - 1;

	GLfloat imageWindowWidth = (lastWidth * getWindowCoordWidth()) / newWidth;
	GLfloat imageWindowHeight = (lastHeight * getWindowCoordHeight()) / newHeight;

	for (int i = 0; i < 8; i += 2)
	{
		m_vertexData[i] = newXWindowPos + VERTEX_TEMPLATE[i] * imageWindowWidth;
		m_vertexData[i + 1] = newYWindowPos + VERTEX_TEMPLATE[i + 1] * imageWindowHeight;
	}
}

void I_HudObject::setFields(unsigned int width, unsigned int height, int xPixelPos, int yPixelPos, bool preserveAspectRatioOnResize)
{
	I_HudObject::setFields(width, height, pixelsToWindowCoordWidth(xPixelPos) - 1, pixelsToWindowCoordHeight(yPixelPos) - 1, preserveAspectRatioOnResize);
}

void I_HudObject::setFields(unsigned int width, unsigned int height, GLfloat xPos, GLfloat yPos, bool preserveAspectRatioOnResize)
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

void I_HudObject::setWidth(int width_pixels, bool preserveAspectRatio)
{
	_setWidth(pixelsToWindowCoordWidth(width_pixels), preserveAspectRatio, m_vertexData);
}

void I_HudObject::setHeight(int height_pixels, bool preserveAspectRatio)
{
	_setHeight(pixelsToWindowCoordHeight(height_pixels), preserveAspectRatio, m_vertexData);
}

void I_HudObject::setWidth(GLfloat width_windowCoords, bool preserveAspectRatio)
{
	_setWidth(width_windowCoords, preserveAspectRatio, m_vertexData);
}

void I_HudObject::setHeight(GLfloat height_windowCoords, bool preserveAspectRatio)
{
	_setHeight(height_windowCoords, preserveAspectRatio, m_vertexData);
}

void I_HudObject::move(int xDirection_pixels, int yDirection_pixels)
{
	_move(pixelsToWindowCoordWidth(xDirection_pixels), pixelsToWindowCoordHeight(yDirection_pixels), m_vertexData);
}

void I_HudObject::move(GLfloat xDirection_windowCoords, GLfloat yDirection_windowCoords)
{
	_move(xDirection_windowCoords, yDirection_windowCoords, m_vertexData);
}

void I_HudObject::moveTo(int xPixelPos, int yPixelPos)
{
	_moveTo(pixelsToWindowCoordWidth(xPixelPos) - 1, pixelsToWindowCoordHeight(yPixelPos) - 1, m_vertexData);
}

void I_HudObject::moveTo(GLfloat xWindowPos, GLfloat yWindowPos)
{
	_moveTo(xWindowPos, yWindowPos, m_vertexData);
}

void I_HudObject::zoom(int newWidth_pixels, int newHeight_pixels, GLfloat focusX, GLfloat focusY)
{
	_zoom(pixelsToWindowCoordWidth(newWidth_pixels), pixelsToWindowCoordHeight(newHeight_pixels), focusX, focusY, m_vertexData);
}

void I_HudObject::zoom(GLfloat newWidth_windowCoords, GLfloat newHeight_windowCoords, GLfloat focusX, GLfloat focusY)
{
	_zoom(newWidth_windowCoords, newHeight_windowCoords, focusX, focusY, m_vertexData);
}

template<typename numeric_type> GLfloat I_HudObject::pixelsToWindowCoordWidth(numeric_type pixels)
{
	return 2 * (GLfloat)pixels / m_game->getWindowWidth();
}

template<typename numeric_type> GLfloat I_HudObject::pixelsToWindowCoordHeight(numeric_type pixels)
{
	return 2 * (GLfloat)pixels / m_game->getWindowHeight();
}

void I_HudObject::_setWidth(GLfloat width_windowCoords, bool preserveAspectRatio, GLfloat vertexData[8])
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

void I_HudObject::_setHeight(GLfloat height_windowCoords, bool preserveAspectRatio, GLfloat vertexData[8])
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

void I_HudObject::_move(GLfloat xDirection, GLfloat yDirection, GLfloat vertexData[8])
{
	for (int i = 0; i < 8; i += 2)
	{
		vertexData[i] += xDirection;
		vertexData[i + 1] += yDirection;
	}
}

void I_HudObject::_moveTo(GLfloat xPos, GLfloat yPos, GLfloat vertexData[8])
{
	GLfloat windowWidth = getWindowCoordWidth();
	GLfloat windowHeight = getWindowCoordHeight();

	for (int i = 0; i < 8; i += 2)
	{
		vertexData[i] = xPos + VERTEX_TEMPLATE[i] * windowWidth;
		vertexData[i + 1] = yPos + VERTEX_TEMPLATE[i + 1] * windowHeight;
	}
}

void I_HudObject::_zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX, GLfloat focusY, GLfloat vertexData[8])
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
