#pragma once

#include "HUDobject_interface.h"

class HUDobject_Animated_interface : public HUDobject_interface
{
private:
	double m_animationStartTime;

protected:
	double m_animationEndTime;
	bool m_isAnimating = false;

	GLfloat m_vertexDataAnimationOrigin[4 * 2];
	GLfloat m_vertexDataAnimationDestination[4 * 2];

protected:
	HUDobject_Animated_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager) : HUDobject_interface(program, graphicsObjectManager) {}

	HUDobject_Animated_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager, glm::vec2 pos, GLfloat width, GLfloat height)
		: HUDobject_interface(program, graphicsObjectManager, pos, width, height) {}

public:
	virtual ~HUDobject_Animated_interface() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager) override;

protected:
	void setCoords(glm::vec2 pos, GLfloat width, GLfloat height, float animationDuration);

	void setWidth(GLfloat width, bool preserveAspectRatio, float animationDuration);
	void setHeight(GLfloat height, bool preserveAspectRatio, float animationDuration);

	void move(glm::vec2 direction, float animationDuration);

	void moveTo(glm::vec2 pos, float animationDuration);

	void zoom(GLfloat newWidth, GLfloat newHeight, float animationDuration, glm::vec2 focus = { 0.5f, 0.5f });

private:
	using HUDobject_interface::setCoords;
	using HUDobject_interface::setWidth;
	using HUDobject_interface::setHeight;
	using HUDobject_interface::move;
	using HUDobject_interface::moveTo;
	using HUDobject_interface::zoom;
};
