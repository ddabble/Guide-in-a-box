#include "HUDobject_Animated_interface.h"

#include <cstring>
#include <GLFW/glfw3.h>

void HUDobject_Animated_interface::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
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
	} else if (m_isAnimating)
	{
		for (int i = 0; i < 8; i += 2)
		{
			m_vertexData[i] = m_vertexDataAnimationDestination[i];
			m_vertexData[i + 1] = m_vertexDataAnimationDestination[i + 1];
		}

		m_isAnimating = false;
	}
}

void HUDobject_Animated_interface::setFields(unsigned int width, unsigned int height, int xPos, int yPos, bool preserveAspectRatioOnResize, float animationDuration)
{
	m_animationDuration = animationDuration;
	HUDobject_interface::setFields(width, height, xPos, yPos, preserveAspectRatioOnResize);
}

void HUDobject_Animated_interface::setWidth(int width, bool preserveAspectRatio, bool animate)
{
	if (animate)
	{
		m_animationStartTime = glfwGetTime();

		std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
		std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));

		_setWidth(width, preserveAspectRatio, m_vertexDataAnimationDestination);

		m_isAnimating = true;
	} else if (m_isAnimating)
	{
		_setWidth(width, preserveAspectRatio, m_vertexDataAnimationOrigin);
		_setWidth(width, preserveAspectRatio, m_vertexDataAnimationDestination);
	} else
		_setWidth(width, preserveAspectRatio, m_vertexData);
}

void HUDobject_Animated_interface::setHeight(int height, bool preserveAspectRatio, bool animate)
{
	if (animate)
	{
		m_animationStartTime = glfwGetTime();

		std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
		std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));

		_setHeight(height, preserveAspectRatio, m_vertexDataAnimationDestination);

		m_isAnimating = true;
	} else if (m_isAnimating)
	{
		_setHeight(height, preserveAspectRatio, m_vertexDataAnimationOrigin);
		_setHeight(height, preserveAspectRatio, m_vertexDataAnimationDestination);
	} else
		_setHeight(height, preserveAspectRatio, m_vertexData);
}

void HUDobject_Animated_interface::move(int xDirection, int yDirection, bool animate)
{
	if (animate)
	{
		m_animationStartTime = glfwGetTime();

		std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
		std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));

		_move(xDirection, yDirection, m_vertexDataAnimationDestination);

		m_isAnimating = true;
	} else if (m_isAnimating)
	{
		_move(xDirection, yDirection, m_vertexDataAnimationOrigin);
		_move(xDirection, yDirection, m_vertexDataAnimationDestination);
	} else
		_move(xDirection, yDirection, m_vertexData);
}

void HUDobject_Animated_interface::moveTo(int xPos, int yPos, bool animate)
{
	if (animate)
	{
		m_animationStartTime = glfwGetTime();

		std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
		std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));

		_move(xPos, yPos, m_vertexDataAnimationDestination);

		m_isAnimating = true;
	} else if (m_isAnimating)
	{
		_move(xPos, yPos, m_vertexDataAnimationOrigin);
		_move(xPos, yPos, m_vertexDataAnimationDestination);
	} else
		_move(xPos, yPos, m_vertexData);
}

void HUDobject_Animated_interface::zoom(int newWidth, int newHeight, bool animate, GLfloat focusX, GLfloat focusY)
{
	if (animate)
	{
		m_animationStartTime = glfwGetTime();

		std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
		std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));

		_zoom(newWidth, newHeight, focusX, focusY, m_vertexDataAnimationDestination);

		m_isAnimating = true;
	} else if (m_isAnimating)
	{
		_zoom(newWidth, newHeight, focusX, focusY, m_vertexDataAnimationOrigin);
		_zoom(newWidth, newHeight, focusX, focusY, m_vertexDataAnimationDestination);
	} else
		_zoom(newWidth, newHeight, focusX, focusY, m_vertexData);
}
