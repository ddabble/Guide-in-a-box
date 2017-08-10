#pragma once

#include "HUDobject_interface.h"

class HUDobject_Animated_interface : public HUDobject_interface
{
protected:
	GLfloat m_vertexDataAnimationOrigin[4 * 2];
	GLfloat m_vertexDataAnimationDestination[4 * 2];

	float m_animationDuration;
	bool m_isAnimating = false;
private:
	double m_animationStartTime;

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager) override;

public:
	virtual ~HUDobject_Animated_interface() {}

protected:
	HUDobject_Animated_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager) : HUDobject_interface(program, graphicsObjectManager) {}

	HUDobject_Animated_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager, GLfloat xPos, GLfloat yPos, GLfloat width, GLfloat height)
		: HUDobject_interface(program, graphicsObjectManager, xPos, yPos, width, height) {}
	
	void setCoords(GLfloat xPos, GLfloat yPos, GLfloat width, GLfloat height, float animationDuration);

	void setWidth(GLfloat width, bool preserveAspectRatio, bool animate);
	void setHeight(GLfloat height, bool preserveAspectRatio, bool animate);

	void move(GLfloat xDirection, GLfloat yDirection, bool animate);

	void moveTo(GLfloat xPos, GLfloat yPos, bool animate);

	void zoom(GLfloat newWidth, GLfloat newHeight, bool animate, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);

private:
	void setCoords(GLfloat xPos, GLfloat yPos, GLfloat width, GLfloat height) override {}
	void setWidth(GLfloat width, bool preserveAspectRatio) override {}
	void setHeight(GLfloat height, bool preserveAspectRatio) override {}
	void move(GLfloat xDirection, GLfloat yDirection) override {}
	void moveTo(GLfloat xPos, GLfloat yPos) override {}
	void zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f) override {}
};
