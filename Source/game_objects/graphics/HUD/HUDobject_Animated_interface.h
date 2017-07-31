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

	void setFields(unsigned int width, unsigned int height, int xPos, int yPos, bool preserveAspectRatioOnResize, float animationDuration);

	void setWidth(int width, bool preserveAspectRatio, bool animate);
	void setHeight(int height, bool preserveAspectRatio, bool animate);

	void move(int xDirection, int yDirection, bool animate);

	void moveTo(int xPos, int yPos, bool animate);

	void zoom(int newWidth, int newHeight, bool animate, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);

private:
	void setFields(unsigned int width, unsigned int height, int xPos, int yPos, bool preserveAspectRatioOnResize) override {}
	void setWidth(int width, bool preserveAspectRatio) override {}
	void setHeight(int height, bool preserveAspectRatio) override {}
	void move(int xDirection, int yDirection) override {}
	void moveTo(int xPos, int yPos) override {}
	void zoom(int newWidth, int newHeight, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f) override {}
};
