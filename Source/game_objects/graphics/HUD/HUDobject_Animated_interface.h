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

	HUDobject_Animated_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager, GLfloat xPos, GLfloat yPos, GLfloat width, GLfloat height)
		: HUDobject_interface(program, graphicsObjectManager, xPos, yPos, width, height) {}

public:
	virtual ~HUDobject_Animated_interface() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager) override;

protected:
	void setCoords(GLfloat xPos, GLfloat yPos, GLfloat width, GLfloat height, float animationDuration);

	void setWidth(GLfloat width, bool preserveAspectRatio, float animationDuration);
	void setHeight(GLfloat height, bool preserveAspectRatio, float animationDuration);

	void move(GLfloat xDirection, GLfloat yDirection, float animationDuration);

	void moveTo(GLfloat xPos, GLfloat yPos, float animationDuration);

	void zoom(GLfloat newWidth, GLfloat newHeight, float animationDuration, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);

private:
	using HUDobject_interface::setCoords;
	using HUDobject_interface::setWidth;
	using HUDobject_interface::setHeight;
	using HUDobject_interface::move;
	using HUDobject_interface::moveTo;
	using HUDobject_interface::zoom;
};
