#include "HUDobject_Animated.h"

#include <cstring>
#include <GLFW/glfw3.h>

void HUDobject_Animated::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphics)
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
		m_dirtyFlag = true;

	} else if (m_isAnimating)
	{
		for (int i = 0; i < 8; i += 2)
		{
			m_vertexData[i] = m_vertexDataAnimationDestination[i];
			m_vertexData[i + 1] = m_vertexDataAnimationDestination[i + 1];
		}
		m_dirtyFlag = true;

		m_isAnimating = false;
	}
}

void HUDobject_Animated::setCoords(glm::vec2 pos, GLfloat width, GLfloat height, float animationDuration)
{
	void* args[]{ &pos, &width, &height };
	animate(SET_COORDS, args, animationDuration);
}

void HUDobject_Animated::setWidth(GLfloat width, float animationDuration)
{
	void* args[]{ &width };
	animate(SET_WIDTH, args, animationDuration);
}

void HUDobject_Animated::setHeight(GLfloat height, float animationDuration)
{
	void* args[]{ &height };
	animate(SET_HEIGHT, args, animationDuration);
}

void HUDobject_Animated::move(glm::vec2 amount, float animationDuration)
{
	void* args[]{ &amount };
	animate(MOVE, args, animationDuration);
}

void HUDobject_Animated::moveTo(glm::vec2 pos, float animationDuration)
{
	void* args[]{ &pos };
	animate(MOVE_TO, args, animationDuration);
}

void HUDobject_Animated::zoom(GLfloat percentage, float animationDuration, glm::vec2 focus)
{
	void* args[]{ &percentage, &focus };
	animate(ZOOM, args, animationDuration);
}

void HUDobject_Animated::animate(animationFunction func, void* args[], float animationDuration)
{
	if (animationDuration > 0.0f)
	{
		m_animationStartTime = glfwGetTime();
		if (!m_isAnimating)
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			std::memcpy(m_vertexDataAnimationDestination, m_vertexData, sizeof(m_vertexDataAnimationDestination));
			invoke(func, args, *this, m_vertexDataAnimationDestination);

			m_isAnimating = true;
		} else
		{
			std::memcpy(m_vertexDataAnimationOrigin, m_vertexData, sizeof(m_vertexDataAnimationOrigin));
			invoke(func, args, *this, m_vertexDataAnimationDestination);
		}

		m_animationEndTime = m_animationStartTime + animationDuration;

	} else if (m_isAnimating)
	{
		invoke(func, args, *this, m_vertexDataAnimationOrigin);
		invoke(func, args, *this, m_vertexDataAnimationDestination);
	} else
		invoke(func, args, *this, m_vertexData);
}

constexpr void HUDobject_Animated::invoke(animationFunction func, void* args[], HUDobject_Dynamic& obj, GLfloat vertexData[])
{
	switch (func)
	{
		case SET_COORDS:
			_setCoords(*static_cast<glm::vec2*>(args[0]), *static_cast<GLfloat*>(args[1]), *static_cast<GLfloat*>(args[2]), obj, vertexData);
			break;

		case SET_WIDTH:
			_setWidth(*static_cast<GLfloat*>(args[0]), obj, vertexData);
			break;

		case SET_HEIGHT:
			_setHeight(*static_cast<GLfloat*>(args[0]), obj, vertexData);
			break;

		case MOVE:
			_move(*static_cast<glm::vec2*>(args[0]), obj, vertexData);
			break;

		case MOVE_TO:
			_moveTo(*static_cast<glm::vec2*>(args[0]), obj, vertexData);
			break;

		case ZOOM:
			_zoom(*static_cast<GLfloat*>(args[0]), *static_cast<glm::vec2*>(args[1]), obj, vertexData);
			break;
	}
}
