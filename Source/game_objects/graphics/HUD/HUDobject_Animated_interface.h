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

	void setFields(GLint width, GLint height, GLint xPos, GLint yPos, float animationDuration);

	void setWidth(GLint width, bool preserveAspectRatio, bool animate);
	void setHeight(GLint height, bool preserveAspectRatio, bool animate);

	void move(GLint xDirection, GLint yDirection, bool animate);

	void moveTo(GLint xPos, GLint yPos, bool animate);

	void zoom(GLint newWidth, GLint newHeight, bool animate, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);

private:
	void setFields(GLint width, GLint height, GLint xPos, GLint yPos) override {}
	void setWidth(GLint width, bool preserveAspectRatio) override {}
	void setHeight(GLint height, bool preserveAspectRatio) override {}
	void move(GLint xDirection, GLint yDirection) override {}
	void moveTo(GLint xPos, GLint yPos) override {}
	void zoom(GLint newWidth, GLint newHeight, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f) override {}
};
