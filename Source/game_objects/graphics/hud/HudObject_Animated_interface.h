#pragma once

#include "HudObject_interface.h"

class HudObject_Animated_interface : public HudObject_interface
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
	virtual ~HudObject_Animated_interface() {}

protected:
	HudObject_Animated_interface(const GraphicsObjectManager& graphicsObjectManager) : HudObject_interface(graphicsObjectManager) {}

	void setFields(unsigned int width, unsigned int height, int xPixelPos, int yPixelPos, bool preserveAspectRatioOnResize, float animationDuration);
	void setFields(unsigned int width, unsigned int height, GLfloat xWindowPos, GLfloat yWindowPos, bool preserveAspectRatioOnResize, float animationDuration);

	void setWidth(int width_pixels, bool preserveAspectRatio, bool animate);
	void setHeight(int height_pixels, bool preserveAspectRatio, bool animate);

	void setWidth(GLfloat width_windowCoords, bool preserveAspectRatio, bool animate);
	void setHeight(GLfloat height_windowCoords, bool preserveAspectRatio, bool animate);

	void move(int xDirection_pixels, int yDirection_pixels, bool animate);
	void move(GLfloat xDirection_windowCoords, GLfloat yDirection_windowCoords, bool animate);

	void moveTo(int xPixelPos, int yPixelPos, bool animate);
	void moveTo(GLfloat xWindowPos, GLfloat yWindowPos, bool animate);

	void zoom(int newWidth_pixels, int newHeight_pixels, bool animate, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);
	void zoom(GLfloat newWidth_windowCoords, GLfloat newHeight_windowCoords, bool animate, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);

private:
	void setFields(unsigned int width, unsigned int height, int xPixelPos, int yPixelPos, bool preserveAspectRatioOnResize) override {}
	void setFields(unsigned int width, unsigned int height, GLfloat xWindowPos, GLfloat yWindowPos, bool preserveAspectRatioOnResize) override {}
	void setWidth(int width_pixels, bool preserveAspectRatio) override {}
	void setHeight(int height_pixels, bool preserveAspectRatio) override {}
	void setWidth(GLfloat width_windowCoords, bool preserveAspectRatio) override {}
	void setHeight(GLfloat height_windowCoords, bool preserveAspectRatio) override {}
	void move(int xDirection_pixels, int yDirection_pixels) override {}
	void move(GLfloat xDirection_windowCoords, GLfloat yDirection_windowCoords) override {}
	void moveTo(int xPixelPos, int yPixelPos) override {}
	void moveTo(GLfloat xWindowPos, GLfloat yWindowPos) override {}
	void zoom(int newWidth_pixels, int newHeight_pixels, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f) override {}
	void zoom(GLfloat newWidth_windowCoords, GLfloat newHeight_windowCoords, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f) override {}
};
