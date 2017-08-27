#pragma once

#include "HUDobject.h"

class HUDobject_Dynamic : public HUDobject
{
protected:
	bool m_dirtyFlag = false;

protected:
	/* User should call setCoords() after calling this constructor. */
	HUDobject_Dynamic(GLuint program, const GraphicsObjectManager& graphicsObjectManager);

	HUDobject_Dynamic(GLuint program, const GraphicsObjectManager& graphicsObjectManager, glm::vec2 pos, GLfloat width, GLfloat height);

public:
	virtual ~HUDobject_Dynamic() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager) override;

protected:
	/*
	xPos and yPos are the coordinates of the image's lower left corner.
	width and height are the image's dimensions measured in pixels.
	*/
	virtual void setCoords(glm::vec2 pos, GLfloat width, GLfloat height) { _setCoords(pos, width, height, *this, m_vertexData); }

	virtual GLfloat getWidth() const { return _getWidth(m_vertexData); }
	virtual GLfloat getHeight() const { return _getHeight(m_vertexData); }

	virtual void setWidth(GLfloat width) { _setWidth(width, *this, m_vertexData); }
	virtual void setHeight(GLfloat height) { _setHeight(height, *this, m_vertexData); }

	virtual void move(glm::vec2 direction) { _move(direction, *this, m_vertexData); }

	/* xPos and yPos are the coordinates of the image's lower left corner. */
	virtual void moveTo(glm::vec2 pos) { _moveTo(pos, *this, m_vertexData); }

	/*
	Set newWidth or newHeight to -1 to make the image maintain its aspect ratio during the zoom.
	focusX and focusY are relative to the window's lower left corner, and are clamped between 0 and 1.
	*/
	virtual void zoom(GLfloat newWidth, GLfloat newHeight, glm::vec2 focus = { 0.5f, 0.5f }) { _zoom(newWidth, newHeight, focus, *this, m_vertexData); }

protected:
	static void _setCoords(glm::vec2 pos, GLfloat width, GLfloat height, HUDobject_Dynamic& obj, GLfloat vertexData[8]);

	constexpr static GLfloat _getWidth(const GLfloat vertexData[8]) { return vertexData[2] - vertexData[0]; }
	constexpr static GLfloat _getHeight(const GLfloat vertexData[8]) { return vertexData[5] - vertexData[3]; }

	static void _setWidth(GLfloat width, HUDobject_Dynamic& obj, GLfloat vertexData[8]);
	static void _setHeight(GLfloat height, HUDobject_Dynamic& obj, GLfloat vertexData[8]);
	static void _move(glm::vec2 direction, HUDobject_Dynamic& obj, GLfloat vertexData[8]);
	static void _moveTo(glm::vec2 pos, HUDobject_Dynamic& obj, GLfloat vertexData[8]);
	static void _zoom(GLfloat newWidth, GLfloat newHeight, glm::vec2 focus, HUDobject_Dynamic& obj, GLfloat vertexData[8]);

private:
	virtual void onFramebufferResize(int, int, int, int, GLuint) override {}
};
