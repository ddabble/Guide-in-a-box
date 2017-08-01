#pragma once

#include "../../../util/graphics/gl.h"

#include "../../../Game.h"
#include "../GraphicsObjectManager.h"

// TODO: Rename to just HUDobject, seeing that it's more of an abstract class..?
class HUDobject_interface
{
protected:
	const GraphicsObjectManager& m_graphicsObjectManager;

	bool m_preserveAspectRatioOnResize;

	GLuint m_vertexArrayObject;

	GLfloat m_vertexData[4 * 2 + 4 * 2];
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
	virtual void setFields(unsigned int width, unsigned int height, int xPos, int yPos, bool preserveAspectRatioOnResize);

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

	/* focusX and focusY are relative to the texture's lower left corner, and are clamped between 0 and 1. */
	void setTextureZoom(GLfloat ratio, GLfloat focusX, GLfloat focusY);
	/*
	Note: the resulting texture coordinates are clamped between 0 and 1.
	This is done without skewing the texture in any direction.
	*/
	void moveTexture(GLfloat xDirection, GLfloat yDirection);
	/*
	xPos and yPos are the coordinates of the texture's lower left corner.
	Note: the resulting texture coordinates are clamped between 0 and 1.
	This is done without skewing the texture in any direction.
	*/
	void moveTextureTo(GLfloat xPos, GLfloat yPos);

protected:
	void _setWidth(GLfloat width, bool preserveAspectRatio, GLfloat vertexData[8]);
	void _setHeight(GLfloat height, bool preserveAspectRatio, GLfloat vertexData[8]);

	void _move(GLfloat xDirection, GLfloat yDirection, GLfloat vertexData[8]);
	void _moveTo(GLfloat xPos, GLfloat yPos, GLfloat vertexData[8]);
	void _zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX, GLfloat focusY, GLfloat vertexData[8]);
};
