#pragma once

#include "../../../gl/gl.h"

#include "../../../Game.h"
#include "../GraphicsObjectManager.h"

// TODO: Rename to just HUDobject, seeing that it's more of an abstract class..?
class HUDobject_interface
{
protected:
	const GraphicsObjectManager& m_graphicsObjectManager;

	unsigned int m_pixelWidth;
	unsigned int m_pixelHeight;

	bool m_preserveAspectRatioOnResize;

	GLuint m_vertexArrayObject;

	GLfloat m_vertexData[4 * 2 + 4 * 2];
	GLint m_vertexData_uniformIndex;

	GLint m_projection_uniformIndex;

protected:
	HUDobject_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager);

public:
	virtual ~HUDobject_interface() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager);

	/* Should be called whenever the framebuffer is resized. */
	virtual void onFramebufferResize(int lastWidth, int lastHeight, int newWidth, int newHeight, GLuint program);

protected:
	/*
	width and height are the image's dimensions measured in pixels.
	xPixelPos and yPixelPos are the coordinates of the image's lower left corner.
	*/
	virtual void setFields(unsigned int width, unsigned int height, int xPixelPos, int yPixelPos, bool preserveAspectRatioOnResize);
	/*
	width and height are the image's dimensions measured in pixels.
	xWindowPos and yWindowPos are the coordinates of the image's lower left corner.
	*/
	virtual void setFields(unsigned int width, unsigned int height, GLfloat xWindowPos, GLfloat yWindowPos, bool preserveAspectRatioOnResize);

	GLfloat getWindowCoordWidth() { return m_vertexData[2] - m_vertexData[0]; }
	GLfloat getWindowCoordHeight() { return m_vertexData[5] - m_vertexData[3]; }

	virtual void setWidth(int width_pixels, bool preserveAspectRatio);
	virtual void setHeight(int height_pixels, bool preserveAspectRatio);

	virtual void setWidth(GLfloat width_windowCoords, bool preserveAspectRatio);
	virtual void setHeight(GLfloat height_windowCoords, bool preserveAspectRatio);

	virtual void move(int xDirection_pixels, int yDirection_pixels);
	virtual void move(GLfloat xDirection_windowCoords, GLfloat yDirection_windowCoords);

	/* xPixelPos and yPixelPos are the coordinates of the image's lower left corner. */
	virtual void moveTo(int xPixelPos, int yPixelPos);
	/* xWindowPos and yWindowPos are the coordinates of the image's lower left corner. */
	virtual void moveTo(GLfloat xWindowPos, GLfloat yWindowPos);

	/*
	Set newWidth_pixels or newHeight_pixels to -1 to make the image maintain its aspect ratio during the zoom.
	focusX and focusY are relative to the window's lower left corner, and are clamped between 0 and 1.
	*/
	virtual void zoom(int newWidth_pixels, int newHeight_pixels, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);
	/*
	Set newWidth_windowCoords or newHeight_windowCoords to -1 to make the image maintain its aspect ratio during the zoom.
	focusX and focusY are relative to the window's lower left corner, and are clamped between 0 and 1.
	*/
	virtual void zoom(GLfloat newWidth_windowCoords, GLfloat newHeight_windowCoords, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);

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

	template<typename numeric_type> GLfloat pixelsToWindowCoordWidth(numeric_type pixels);
	template<typename numeric_type> GLfloat pixelsToWindowCoordHeight(numeric_type pixels);

protected:
	void _setWidth(GLfloat width_windowCoords, bool preserveAspectRatio, GLfloat vertexData[8]);
	void _setHeight(GLfloat height_windowCoords, bool preserveAspectRatio, GLfloat vertexData[8]);

	void _move(GLfloat xDirection, GLfloat yDirection, GLfloat vertexData[8]);
	void _moveTo(GLfloat xPos, GLfloat yPos, GLfloat vertexData[8]);
	void _zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX, GLfloat focusY, GLfloat vertexData[8]);
};
