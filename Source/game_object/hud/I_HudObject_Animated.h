#pragma once

#include "I_HudObject.h"

class I_HudObject_Animated : public I_HudObject
{
	/*
	width and height are the image's dimensions measured in pixels.
	xPixelPos and yPixelPos are the coordinates of the image's lower left corner.
	*/
	void setFields(unsigned int width, unsigned int height, int xPixelPos, int yPixelPos, bool preserveAspectRatioOnResize) override;

	/*
	width and height are the image's dimensions measured in pixels.
	xWindowPos and yWindowPos are the coordinates of the image's lower left corner.
	*/
	void setFields(unsigned int width, unsigned int height, GLfloat xWindowPos, GLfloat yWindowPos, bool preserveAspectRatioOnResize) override;

	void setWidth(int width_pixels, bool preserveAspectRatio) override;
	void setHeight(int height_pixels, bool preserveAspectRatio) override;

	void setWidth(GLfloat width_windowCoords, bool preserveAspectRatio) override;
	void setHeight(GLfloat height_windowCoords, bool preserveAspectRatio) override;

	void move(int xDirection_pixels, int yDirection_pixels) override;
	void move(GLfloat xDirection_windowCoords, GLfloat yDirection_windowCoords) override;

	/* xPixelPos and yPixelPos are the coordinates of the image's lower left corner. */
	void moveTo(int xPixelPos, int yPixelPos) override;
	/* xWindowPos and yWindowPos are the coordinates of the image's lower left corner. */
	void moveTo(GLfloat xWindowPos, GLfloat yWindowPos) override;

	/*
	Set newWidth_pixels or newHeight_pixels to -1 to make the image maintain its aspect ratio during the zoom.
	focusX and focusY are relative to the window's lower left corner, and are clamped between 0 and 1.
	*/
	void zoom(int newWidth_pixels, int newHeight_pixels, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f) override;
	/*
	Set newWidth_windowCoords or newHeight_windowCoords to -1 to make the image maintain its aspect ratio during the zoom.
	focusX and focusY are relative to the window's lower left corner, and are clamped between 0 and 1.
	*/
	void zoom(GLfloat newWidth_windowCoords, GLfloat newHeight_windowCoords, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f) override;
};
