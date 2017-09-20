#pragma once

#include "../util/graphics/gl.h"

struct GLFWwindow;

class Window
{
	friend class Game;
	friend class EventHandler;

private:
	static constexpr int INITIAL_WINDOW_WIDTH = 1280;
	static constexpr int INITIAL_WINDOW_HEIGHT = 768;

private:
	GLFWwindow* m_window;

	int m_windowWidth;
	int m_windowHeight;

	Window(const char* windowName);
	void initGLFW(const char* windowName);
	void initGL_Load();

	~Window();

	/* Should be called whenever the window is resized. */
	void updateFramebufferSize(int newWidth, int newHeight);

public:
	GLFWwindow* getGLFWwindow() const { return m_window; }

	/* Returns the width in pixels. */
	int getWidth() const { return m_windowWidth; }

	/* Returns the height in pixels. */
	int getHeight() const { return m_windowHeight; }
};
