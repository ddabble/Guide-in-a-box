#pragma once

#include "HUDobject_Dynamic.h"

class HUDobject_Animated : public HUDobject_Dynamic
{
private:
	double m_animationStartTime;

protected:
	double m_animationEndTime;
	bool m_isAnimating = false;

	GLfloat m_vertexDataAnimationOrigin[4 * 2];
	GLfloat m_vertexDataAnimationDestination[4 * 2];

protected:
	HUDobject_Animated(GLuint program, const GraphicsObjectManager& graphicsObjectManager) : HUDobject_Dynamic(program, graphicsObjectManager) {}

	HUDobject_Animated(GLuint program, const GraphicsObjectManager& graphicsObjectManager, glm::vec2 pos, GLfloat width, GLfloat height)
		: HUDobject_Dynamic(program, graphicsObjectManager, pos, width, height) {}

public:
	virtual ~HUDobject_Animated() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager) override;

protected:
	void setCoords(glm::vec2 pos, GLfloat width, GLfloat height, float animationDuration);

	void setWidth(GLfloat width, float animationDuration);
	void setHeight(GLfloat height, float animationDuration);

	void move(glm::vec2 direction, float animationDuration);

	void moveTo(glm::vec2 pos, float animationDuration);

	void zoom(GLfloat percentage, float animationDuration, glm::vec2 focus);

private:
	enum animationFunction
	{
		SET_COORDS, SET_WIDTH, SET_HEIGHT, MOVE, MOVE_TO, ZOOM
	};

	void animate(animationFunction func, void* args[], float animationDuration);

	constexpr static void invoke(animationFunction func, void* args[], HUDobject_Dynamic& obj, GLfloat vertexData[8]);

private:
	using HUDobject_Dynamic::setCoords;
	using HUDobject_Dynamic::setWidth;
	using HUDobject_Dynamic::setHeight;
	using HUDobject_Dynamic::move;
	using HUDobject_Dynamic::moveTo;
	using HUDobject_Dynamic::zoom;
};
