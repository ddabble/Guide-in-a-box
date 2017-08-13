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

void HUDobject_Animated_interface::setCoords(glm::vec2 pos, GLfloat width, GLfloat height, float animationDuration)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();
		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			_setCoords(pos, width, height, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
			_setCoords(pos, width, height, m_vertexDataAnimationDestination);

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		_setCoords(pos, width, height, m_vertexDataAnimationOrigin);
		_setCoords(pos, width, height, m_vertexDataAnimationDestination);
	} else
		_setCoords(pos, width, height, m_vertexData);
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

void HUDobject_Animated_interface::move(glm::vec2 direction, float animationDuration)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();
		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			_move(direction, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
			_move(direction, m_vertexDataAnimationDestination);

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		_move(direction, m_vertexDataAnimationOrigin);
		_move(direction, m_vertexDataAnimationDestination);
	} else
		_move(direction, m_vertexData);
}

void HUDobject_Animated_interface::moveTo(glm::vec2 pos, float animationDuration)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();
		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			_moveTo(pos, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
			_moveTo(pos, m_vertexDataAnimationDestination);

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		_moveTo(pos, m_vertexDataAnimationOrigin);
		_moveTo(pos, m_vertexDataAnimationDestination);
	} else
		_moveTo(pos, m_vertexData);
}

void HUDobject_Animated_interface::zoom(GLfloat newWidth, GLfloat newHeight, float animationDuration, glm::vec2 focus)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();
		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			_zoom(newWidth, newHeight, focus, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
			_zoom(newWidth, newHeight, focus, m_vertexDataAnimationDestination);

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		_zoom(newWidth, newHeight, focus, m_vertexDataAnimationOrigin);
		_zoom(newWidth, newHeight, focus, m_vertexDataAnimationDestination);
	} else
		_zoom(newWidth, newHeight, focus, m_vertexData);
}
