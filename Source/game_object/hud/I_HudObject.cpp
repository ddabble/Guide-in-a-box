#include "I_HudObject.h"

#include <glm/glm.hpp>

#include "../../Game.h"

static constexpr GLfloat VERTEX_TEMPLATE[] =
{
	0, 0,
	1, 0,
	1, 1,
	0, 1
};

void I_HudObject::onFramebufferResize(int newWidth, int newHeight)
{
	if (!m_preserveAspectRatioOnResize)
		return;

	GLfloat newXWindowPos = (2 * (GLfloat)m_xPixelPos / newWidth) - 1;
	GLfloat newYWindowPos = (2 * (GLfloat)m_yPixelPos / newHeight) - 1;

	GLfloat imageWindowWidth = 2 * (GLfloat)m_pixelWidth / newWidth;
	GLfloat imageWindowHeight = 2 * (GLfloat)m_pixelHeight / newHeight;

	for (int i = 0; i < 8; i += 2)
	{
		m_vertexData[i] = newXWindowPos + VERTEX_TEMPLATE[i] * imageWindowWidth;
		m_vertexData[i + 1] = newYWindowPos + VERTEX_TEMPLATE[i + 1] * imageWindowHeight;
	}
}

void I_HudObject::setFields(unsigned int width, unsigned int height, int xPixelPos, int yPixelPos, bool preserveAspectRatioOnResize)
{
	m_xPixelPos = xPixelPos;
	m_yPixelPos = yPixelPos;

	setFields(width, height, pixelsToWindowCoordWidth(xPixelPos) - 1, pixelsToWindowCoordHeight(yPixelPos) - 1, preserveAspectRatioOnResize);
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
	memcpy(m_vertexData, vertexData, sizeof(vertexData));
	m_preserveAspectRatioOnResize = preserveAspectRatioOnResize;
}

void I_HudObject::setWidth(int width_pixels, bool preserveAspectRatio)
{
	setWidth(pixelsToWindowCoordWidth(width_pixels), preserveAspectRatio);
}

void I_HudObject::setHeight(int height_pixels, bool preserveAspectRatio)
{
	setHeight(pixelsToWindowCoordHeight(height_pixels), preserveAspectRatio);
}

// TODO:

void I_HudObject::setWidth(GLfloat width_windowCoords, bool preserveAspectRatio)
{
	m_vertexData[2] = m_vertexData[0] + width_windowCoords;
	m_vertexData[4] = m_vertexData[0] + width_windowCoords;
}

void I_HudObject::setHeight(GLfloat height_windowCoords, bool preserveAspectRatio)
{
	m_vertexData[5] = m_vertexData[1] + height_windowCoords;
	m_vertexData[7] = m_vertexData[1] + height_windowCoords;
}

void I_HudObject::move(int xDirection_pixels, int yDirection_pixels)
{
	m_xPixelPos += xDirection_pixels;
	m_yPixelPos += yDirection_pixels;

	_move(pixelsToWindowCoordWidth(xDirection_pixels), pixelsToWindowCoordHeight(yDirection_pixels));
}

void I_HudObject::move(GLfloat xDirection_windowCoords, GLfloat yDirection_windowCoords)
{
	_move(xDirection_windowCoords, yDirection_windowCoords);
}

void I_HudObject::_move(GLfloat xDirection, GLfloat yDirection)
{
	for (int i = 0; i < 8; i += 2)
	{
		m_vertexData[i] += xDirection;
		m_vertexData[i + 1] += yDirection;
	}
}

void I_HudObject::moveTo(int xPixelPos, int yPixelPos)
{
	m_xPixelPos = xPixelPos;
	m_yPixelPos = yPixelPos;

	_moveTo(pixelsToWindowCoordWidth(xPixelPos) - 1, pixelsToWindowCoordHeight(yPixelPos) - 1);
}

void I_HudObject::moveTo(GLfloat xWindowPos, GLfloat yWindowPos)
{
	_moveTo(xWindowPos, yWindowPos);
}

void I_HudObject::_moveTo(GLfloat xPos, GLfloat yPos)
{
	GLfloat windowWidth = getWindowCoordWidth();
	GLfloat windowHeight = getWindowCoordHeight();

	for (int i = 0; i < 8; i += 2)
	{
		m_vertexData[i] = xPos + VERTEX_TEMPLATE[i] * windowWidth;
		m_vertexData[i + 1] = yPos + VERTEX_TEMPLATE[i + 1] * windowHeight;
	}
}

void I_HudObject::zoom(int newWidth_pixels, int newHeight_pixels, GLfloat focusX, GLfloat focusY)
{
	_zoom(pixelsToWindowCoordWidth(newWidth_pixels), pixelsToWindowCoordHeight(newHeight_pixels), focusX, focusY);

	m_xPixelPos = (int)glm::round(/*RS_DRH::getInstance()->getWindowWidth() * */(m_vertexData[0] + 1) / 2);
	m_yPixelPos = (int)glm::round(/*RS_DRH::getInstance()->getWindowHeight() * */(m_vertexData[1] + 1) / 2);
}

void I_HudObject::zoom(GLfloat newWidth_windowCoords, GLfloat newHeight_windowCoords, GLfloat focusX, GLfloat focusY)
{
	_zoom(newWidth_windowCoords, newHeight_windowCoords, focusX, focusY);
}

void I_HudObject::_zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX, GLfloat focusY)
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

	GLfloat cursorPosInTexCoords_x = ((focusX * 2 - 1) - getXWindowPos()) / oldWidth;
	GLfloat cursorPosInTexCoords_y = ((focusY * 2 - 1) - getYWindowPos()) / oldHeight;

	for (int i = 0; i < 8; i += 2)
	{
		m_vertexData[i] += (VERTEX_TEMPLATE[i] - cursorPosInTexCoords_x) * deltaWidth;
		m_vertexData[i + 1] += (VERTEX_TEMPLATE[i + 1] - cursorPosInTexCoords_y) * deltaHeight;
	}
}

template<typename numeric_type> GLfloat I_HudObject::pixelsToWindowCoordWidth(numeric_type pixels)
{
	return 2 * (GLfloat)pixels / m_game->getWindowWidth();
}

template<typename numeric_type> GLfloat I_HudObject::pixelsToWindowCoordHeight(numeric_type pixels)
{
	return 2 * (GLfloat)pixels / m_game->getWindowHeight();
}
