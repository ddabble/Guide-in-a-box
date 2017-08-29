#include "Window.h"

#include <iostream>

#include <glload/gl_load.h>

#include <GLFW/glfw3.h>

/* Should be registered before GLFW is initialized. */
void errorCallback(int error, const char* description)
{
	std::cerr << "Error: " << description << std::endl;
}

Window::Window(char* windowName) : m_windowWidth(INITIAL_WINDOW_WIDTH), m_windowHeight(INITIAL_WINDOW_HEIGHT)
{
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		std::cerr << "Unable to initialize GLFW.\n" << "exiting..." << std::endl;
		throw std::runtime_error("");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// TODO: Make this an option in the settings
	//glfwWindowHint(GLFW_SAMPLES, 4);

	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, windowName, NULL, NULL);
	if (!m_window)
	{
		std::cerr << "Unable to create a window with GLFW.\n" << "exiting..." << std::endl;
		glfwTerminate();
		throw std::runtime_error("");
	}

	glfwSetWindowSizeLimits(m_window, 100, 100, GLFW_DONT_CARE, GLFW_DONT_CARE);

	glfwMakeContextCurrent(m_window);

	int loadTest = ogl_LoadFunctions();
	if (loadTest == ogl_LOAD_FAILED)
	{
		std::cerr << "Unable to initialize GL Load.\n" << loadTest - ogl_LOAD_SUCCEEDED << " core functions failed to load.\n" << "exiting..." << std::endl;
		glfwTerminate();
		throw std::runtime_error("");
	}

	glfwSwapInterval(1);
}
