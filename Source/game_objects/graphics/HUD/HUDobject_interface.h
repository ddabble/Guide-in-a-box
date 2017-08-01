#pragma once

#include "../../../util/graphics/gl.h"

#include "../../../Game.h"
#include "../GraphicsObjectManager.h"

// TODO: Rename to just HUDobject, seeing that it's more of an abstract class..?
class HUDobject_interface
{
protected:
	GLfloat m_vertexData[4 * 2 + 4 * 2];

	GLuint m_vertexArrayObject;

	GLint m_vertexData_uniformIndex;

protected:
	HUDobject_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager);

public:
	virtual ~HUDobject_interface() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager);

protected:
	/*
	width and height are the image's dimensions measured in pixels.
	xPos and yPos are the coordinates of the image's lower left corner.
	*/
	virtual void setFields(unsigned int width, unsigned int height, int xPos, int yPos);

	GLint getWidth() { return m_vertexData[2] - m_vertexData[0]; }
	GLint getHeight() { return m_vertexData[5] - m_vertexData[3]; }

	virtual void setWidth(int width, bool preserveAspectRatio);
	virtual void setHeight(int height, bool preserveAspectRatio);

	virtual void move(int xDirection, int yDirection);

	/* xPos and yPos are the coordinates of the image's lower left corner. */
	virtual void moveTo(int xPos, int yPos);

	/*
	Set newWidth or newHeight to -1 to make the image maintain its aspect ratio during the zoom.
	focusX and focusY are relative to the window's lower left corner, and are clamped between 0 and 1.
	*/
	virtual void zoom(int newWidth, int newHeight, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);

protected:
	void _setWidth(GLfloat width, bool preserveAspectRatio, GLfloat vertexData[8]);
	void _setHeight(GLfloat height, bool preserveAspectRatio, GLfloat vertexData[8]);

	void _move(GLfloat xDirection, GLfloat yDirection, GLfloat vertexData[8]);
	void _moveTo(GLfloat xPos, GLfloat yPos, GLfloat vertexData[8]);
	void _zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX, GLfloat focusY, GLfloat vertexData[8]);
};
