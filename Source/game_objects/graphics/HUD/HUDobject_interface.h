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
	virtual void setFields(GLint width, GLint height, GLint xPos, GLint yPos);

	GLint getWidth() { return m_vertexData[2] - m_vertexData[0]; }
	GLint getHeight() { return m_vertexData[5] - m_vertexData[3]; }

	virtual void setWidth(GLint width, bool preserveAspectRatio);
	virtual void setHeight(GLint height, bool preserveAspectRatio);

	virtual void move(GLint xDirection, GLint yDirection);

	/* xPos and yPos are the coordinates of the image's lower left corner. */
	virtual void moveTo(GLint xPos, GLint yPos);

	/*
	Set newWidth or newHeight to -1 to make the image maintain its aspect ratio during the zoom.
	focusX and focusY are relative to the window's lower left corner, and are clamped between 0 and 1.
	*/
	virtual void zoom(GLint newWidth, GLint newHeight, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);
};
