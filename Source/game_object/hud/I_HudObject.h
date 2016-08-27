#pragma once

#include "../../gl/gl.h"
#include "../../event/EventHandler.h"

class Game;

class I_HudObject
{
protected:
	const Game* m_game;

	unsigned int m_pixelWidth;
	unsigned int m_pixelHeight;

	/* X coordinate of the image's lower left corner. */
	int m_xPixelPos;
	/* Y coordinate of the image's lower left corner. */
	int m_yPixelPos;

	GLfloat m_vertexData[4 * 2 + 4 * 2];

	bool m_preserveAspectRatioOnResize;

public:
	virtual void addEventHooks(EventHandler& eventHandler) {}

	virtual void frameUpdate(GLuint program, const Game* game) = 0;
	virtual void physicsUpdate(const Game* game) {}

	/* Should be called whenever the framebuffer is resized. */
	virtual void onFramebufferResize(int newWidth, int newHeight);

protected:
	I_HudObject(const Game* game) : m_game(game) {}

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

	GLfloat getXWindowPos() { return m_vertexData[0]; }
	GLfloat getYWindowPos() { return m_vertexData[1]; }

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

private:
	void _move(GLfloat xDirection, GLfloat yDirection);
	void _moveTo(GLfloat xPos, GLfloat yPos);
	void _zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f);
};
