#include "HUDobject_Animated_interface.h"

#include <cstring>
#include <GLFW/glfw3.h>

void HUDobject_Animated_interface::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
{
	if (!m_isAnimating)
		return;

	double currentTime = glfwGetTime();
	if (currentTime < m_animationEndTime)
	{
		float progressPercentage = float((currentTime - m_animationStartTime) / (m_animationEndTime - m_animationStartTime));

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

void HUDobject_Animated_interface::setCoords(GLfloat xPos, GLfloat yPos, GLfloat width, GLfloat height, float animationDuration)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();
		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			_setCoords(xPos, yPos, width, height, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
			_setCoords(xPos, yPos, width, height, m_vertexDataAnimationDestination);

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		_setCoords(xPos, yPos, width, height, m_vertexDataAnimationOrigin);
		_setCoords(xPos, yPos, width, height, m_vertexDataAnimationDestination);
	} else
		_setCoords(xPos, yPos, width, height, m_vertexData);
}

void HUDobject_Animated_interface::setWidth(GLfloat width, bool preserveAspectRatio, float animationDuration)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();
		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			_setWidth(width, preserveAspectRatio, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
			_setWidth(width, preserveAspectRatio, m_vertexDataAnimationDestination);

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		_setWidth(width, preserveAspectRatio, m_vertexDataAnimationOrigin);
		_setWidth(width, preserveAspectRatio, m_vertexDataAnimationDestination);
	} else
		_setWidth(width, preserveAspectRatio, m_vertexData);
}

void HUDobject_Animated_interface::setHeight(GLfloat height, bool preserveAspectRatio, float animationDuration)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();

		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			_setHeight(height, preserveAspectRatio, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
			_setHeight(height, preserveAspectRatio, m_vertexDataAnimationDestination);

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		_setHeight(height, preserveAspectRatio, m_vertexDataAnimationOrigin);
		_setHeight(height, preserveAspectRatio, m_vertexDataAnimationDestination);
	} else
		_setHeight(height, preserveAspectRatio, m_vertexData);
}

void HUDobject_Animated_interface::move(GLfloat xDirection, GLfloat yDirection, float animationDuration)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();
		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			_move(xDirection, yDirection, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
			_move(xDirection, yDirection, m_vertexDataAnimationDestination);

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		_move(xDirection, yDirection, m_vertexDataAnimationOrigin);
		_move(xDirection, yDirection, m_vertexDataAnimationDestination);
	} else
		_move(xDirection, yDirection, m_vertexData);
}

void HUDobject_Animated_interface::moveTo(GLfloat xPos, GLfloat yPos, float animationDuration)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();
		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			_moveTo(xPos, yPos, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
			_moveTo(xPos, yPos, m_vertexDataAnimationDestination);

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		_moveTo(xPos, yPos, m_vertexDataAnimationOrigin);
		_moveTo(xPos, yPos, m_vertexDataAnimationDestination);
	} else
		_moveTo(xPos, yPos, m_vertexData);
}

void HUDobject_Animated_interface::zoom(GLfloat newWidth, GLfloat newHeight, float animationDuration, GLfloat focusX, GLfloat focusY)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();
		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			_zoom(newWidth, newHeight, focusX, focusY, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
			_zoom(newWidth, newHeight, focusX, focusY, m_vertexDataAnimationDestination);

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		_zoom(newWidth, newHeight, focusX, focusY, m_vertexDataAnimationOrigin);
		_zoom(newWidth, newHeight, focusX, focusY, m_vertexDataAnimationDestination);
	} else
		_zoom(newWidth, newHeight, focusX, focusY, m_vertexData);
}
