#include "HudObject_Animated_interface.h"

#include <cstring>
#include <GLFW/glfw3.h>

void HudObject_Animated_interface::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
{
	if (!m_isAnimating)
		return;

	double currentTime = glfwGetTime();
	if (currentTime < m_animationStartTime + m_animationDuration)
	{
		float progressPercentage = float(currentTime - m_animationStartTime) / m_animationDuration;

		for (int i = 0; i < 8; i += 2)
		{
			m_vertexData[i] = m_vertexDataAnimationOrigin[i] + (m_vertexDataAnimationDestination[i] - m_vertexDataAnimationOrigin[i]) * progressPercentage;
			m_vertexData[i + 1] = m_vertexDataAnimationOrigin[i + 1] + (m_vertexDataAnimationDestination[i + 1] - m_vertexDataAnimationOrigin[i + 1]) * progressPercentage;
		}
	} else
		m_isAnimating = false;
}

void HudObject_Animated_interface::setFields(unsigned int width, unsigned int height, int xPixelPos, int yPixelPos, bool preserveAspectRatioOnResize, float animationDuration)
{
	m_animationDuration = animationDuration;
	HudObject_interface::setFields(width, height, xPixelPos, yPixelPos, preserveAspectRatioOnResize);
}

void HudObject_Animated_interface::setFields(unsigned int width, unsigned int height, GLfloat xWindowPos, GLfloat yWindowPos, bool preserveAspectRatioOnResize, float animationDuration)
{
	m_animationDuration = animationDuration;
	HudObject_interface::setFields(width, height, xWindowPos, yWindowPos, preserveAspectRatioOnResize);
}

void HudObject_Animated_interface::setWidth(int width_pixels, bool preserveAspectRatio, bool animate)
{
	setWidth(pixelsToWindowCoordWidth(width_pixels), preserveAspectRatio, animate);
}

void HudObject_Animated_interface::setHeight(int height_pixels, bool preserveAspectRatio, bool animate)
{
	setHeight(pixelsToWindowCoordWidth(height_pixels), preserveAspectRatio, animate);
}

void HudObject_Animated_interface::setWidth(GLfloat width_windowCoords, bool preserveAspectRatio, bool animate)
{
	if (animate)
	{
		m_animationStartTime = glfwGetTime();

		std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
		std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));

		_setWidth(width_windowCoords, preserveAspectRatio, m_vertexDataAnimationDestination);

		m_isAnimating = true;
	} else if (m_isAnimating)
	{
		_setWidth(width_windowCoords, preserveAspectRatio, m_vertexDataAnimationOrigin);
		_setWidth(width_windowCoords, preserveAspectRatio, m_vertexDataAnimationDestination);
	} else
		_setWidth(width_windowCoords, preserveAspectRatio, m_vertexData);
}

void HudObject_Animated_interface::setHeight(GLfloat height_windowCoords, bool preserveAspectRatio, bool animate)
{
	if (animate)
	{
		m_animationStartTime = glfwGetTime();

		std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
		std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));

		_setHeight(height_windowCoords, preserveAspectRatio, m_vertexDataAnimationDestination);

		m_isAnimating = true;
	} else if (m_isAnimating)
	{
		_setHeight(height_windowCoords, preserveAspectRatio, m_vertexDataAnimationOrigin);
		_setHeight(height_windowCoords, preserveAspectRatio, m_vertexDataAnimationDestination);
	} else
		_setHeight(height_windowCoords, preserveAspectRatio, m_vertexData);
}

void HudObject_Animated_interface::move(int xDirection_pixels, int yDirection_pixels, bool animate)
{
	move(pixelsToWindowCoordWidth(xDirection_pixels), pixelsToWindowCoordHeight(yDirection_pixels), animate);
}

void HudObject_Animated_interface::move(GLfloat xDirection_windowCoords, GLfloat yDirection_windowCoords, bool animate)
{
	if (animate)
	{
		m_animationStartTime = glfwGetTime();

		std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
		std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));

		_move(xDirection_windowCoords, yDirection_windowCoords, m_vertexDataAnimationDestination);

		m_isAnimating = true;
	} else if (m_isAnimating)
	{
		_move(xDirection_windowCoords, yDirection_windowCoords, m_vertexDataAnimationOrigin);
		_move(xDirection_windowCoords, yDirection_windowCoords, m_vertexDataAnimationDestination);
	} else
		_move(xDirection_windowCoords, yDirection_windowCoords, m_vertexData);
}

void HudObject_Animated_interface::moveTo(int xPixelPos, int yPixelPos, bool animate)
{
	moveTo(pixelsToWindowCoordWidth(xPixelPos) - 1, pixelsToWindowCoordHeight(yPixelPos) - 1, animate);
}

void HudObject_Animated_interface::moveTo(GLfloat xWindowPos, GLfloat yWindowPos, bool animate)
{
	if (animate)
	{
		m_animationStartTime = glfwGetTime();

		std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
		std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));

		_move(xWindowPos, yWindowPos, m_vertexDataAnimationDestination);

		m_isAnimating = true;
	} else if (m_isAnimating)
	{
		_move(xWindowPos, yWindowPos, m_vertexDataAnimationOrigin);
		_move(xWindowPos, yWindowPos, m_vertexDataAnimationDestination);
	} else
		_move(xWindowPos, yWindowPos, m_vertexData);
}

void HudObject_Animated_interface::zoom(int newWidth_pixels, int newHeight_pixels, bool animate, GLfloat focusX, GLfloat focusY)
{
	zoom(pixelsToWindowCoordWidth(newWidth_pixels), pixelsToWindowCoordHeight(newHeight_pixels), animate, focusX, focusY);
}

void HudObject_Animated_interface::zoom(GLfloat newWidth_windowCoords, GLfloat newHeight_windowCoords, bool animate, GLfloat focusX, GLfloat focusY)
{
	if (animate)
	{
		m_animationStartTime = glfwGetTime();

		std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
		std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));

		_zoom(newWidth_windowCoords, newHeight_windowCoords, focusX, focusY, m_vertexDataAnimationDestination);

		m_isAnimating = true;
	} else if (m_isAnimating)
	{
		_zoom(newWidth_windowCoords, newHeight_windowCoords, focusX, focusY, m_vertexDataAnimationOrigin);
		_zoom(newWidth_windowCoords, newHeight_windowCoords, focusX, focusY, m_vertexDataAnimationDestination);
	} else
		_zoom(newWidth_windowCoords, newHeight_windowCoords, focusX, focusY, m_vertexData);
}
