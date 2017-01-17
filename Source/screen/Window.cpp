#include "Window.h"

GLfloat Window::pixelCoordsToWindowCoords_x(GLfloat pixels_x) const
{
	return 2 * pixels_x / m_windowWidth - 1;
}

GLfloat Window::pixelCoordsToWindowCoords_y(GLfloat pixels_y) const
{
	return 2 * pixels_y / m_windowHeight - 1;
}

GLfloat Window::windowCoordsToPixelCoords_x(GLfloat x) const
{
	return m_windowWidth * (x + 1) / 2;
}

GLfloat Window::windowCoordsToPixelCoords_y(GLfloat y) const
{
	return m_windowHeight * (y + 1) / 2;
}
