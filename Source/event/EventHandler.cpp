#include "EventHandler.h"

#include <iostream>

// Must be included before the GLFW header
#include "../gl/gl.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../Game.h"

Game* EventHandler::m_game;

std::vector<FramebufferSizeHook_interface*> EventHandler::m_framebufferSizeHooks;
std::vector<CursorPosHook_interface*> EventHandler::m_cursorPosHooks;
std::vector<MouseButtonHook_interface*> EventHandler::m_mouseButtonHooks;
std::vector<ScrollHook_interface*> EventHandler::m_scrollHooks;

void EventHandler::init(Game& game)
{
	m_game = &game;
	registerCallbacks(game.m_window.m_window);
}

void EventHandler::registerCallbacks(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetWindowRefreshCallback(window, windowRefreshCallback);
	glfwSetWindowPosCallback(window, windowPosCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
}

void EventHandler::framebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	int* width = &(m_game->m_window.m_windowWidth);
	int* height = &(m_game->m_window.m_windowHeight);

	for (auto hook : m_framebufferSizeHooks)
		hook->framebufferSizeCallback(*width, *height, newWidth, newHeight, m_game->m_gameObjectManager.m_graphicsObjectManager);

	*width = newWidth;
	*height = newHeight;
}

void EventHandler::windowRefreshCallback(GLFWwindow* window)
{
	m_game->frameUpdate();
	m_game->graphicsUpdate();

	glfwSwapBuffers(window);
}

void EventHandler::windowPosCallback(GLFWwindow* window, int xPos, int yPos)
{
	m_game->frameUpdate();
	m_game->graphicsUpdate();

	glfwSwapBuffers(window);
}

void EventHandler::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	InputManager* input = &(m_game->m_input);
	input->m_mouse.updateCursorPos(xPos, yPos, m_game->m_window);

	for (auto hook : m_cursorPosHooks)
		hook->cursorPosCallback(*input);
}

void EventHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	InputManager* input = &(m_game->m_input);

	for (auto hook : m_mouseButtonHooks)
		hook->mouseButtonCallback(*input);

	// TODO:
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
			input->m_mouse.m_isLeftMouseButtonDown = true;
		else
			input->m_mouse.m_isLeftMouseButtonDown = false;
	}
}

void EventHandler::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	for (auto hook : m_scrollHooks)
		hook->scrollCallback((float)xOffset, (float)yOffset, m_game->m_input);
}
