#pragma once

#include "../gl/gl.h"

struct GLFWwindow;

class Window
{
	friend class Game;
	friend class EventHandler;

public:
	static constexpr int INITIAL_WINDOW_WIDTH = 1280;
	static constexpr int INITIAL_WINDOW_HEIGHT = 768;

private:
	GLFWwindow* m_window;

	int m_windowWidth;
	int m_windowHeight;

	Window(char* windowName);

public:
	GLFWwindow* getGLFWwindow() const { return m_window; }

	int getWidth() const { return m_windowWidth; }
	int getHeight() const { return m_windowHeight; }

	GLfloat pixelCoordsToWindowCoords_x(GLfloat pixels_x) const;
	GLfloat pixelCoordsToWindowCoords_y(GLfloat pixels_y) const;

	GLfloat windowCoordsToPixelCoords_x(GLfloat x) const;
	GLfloat windowCoordsToPixelCoords_y(GLfloat y) const;
};
