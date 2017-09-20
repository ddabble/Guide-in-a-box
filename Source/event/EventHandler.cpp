#include "EventHandler.h"

#include <iostream>
#include <algorithm>

// Must be included before the GLFW header
#include "../util/graphics/gl.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../Game.h"

Game* EventHandler::m_game;

std::vector<FramebufferSizeHook*> EventHandler::m_framebufferSizeHooks;
std::vector<CursorPosHook*> EventHandler::m_cursorPosHooks;
std::vector<MouseButtonHook*> EventHandler::m_mouseButtonHooks;
std::vector<ScrollHook*> EventHandler::m_scrollHooks;

void EventHandler::init(Game& game)
{
	m_game = &game;
	registerCallbacks(game.m_window.m_window);
}

void EventHandler::removeFramebufferSizeHook(FramebufferSizeHook* hook)
{
	m_framebufferSizeHooks.erase(std::remove(m_framebufferSizeHooks.begin(), m_framebufferSizeHooks.end(), hook), m_framebufferSizeHooks.end());
}

void EventHandler::removeCursorPosHook(CursorPosHook* hook)
{
	m_cursorPosHooks.erase(std::remove(m_cursorPosHooks.begin(), m_cursorPosHooks.end(), hook), m_cursorPosHooks.end());
}

void EventHandler::removeMouseButtonHook(MouseButtonHook* hook)
{
	m_mouseButtonHooks.erase(std::remove(m_mouseButtonHooks.begin(), m_mouseButtonHooks.end(), hook), m_mouseButtonHooks.end());
}

void EventHandler::removeScrollHook(ScrollHook* hook)
{
	m_scrollHooks.erase(std::remove(m_scrollHooks.begin(), m_scrollHooks.end(), hook), m_scrollHooks.end());
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
	int width = m_game->m_window.m_windowWidth;
	int height = m_game->m_window.m_windowHeight;

	m_game->m_window.updateFramebufferSize(newWidth, newHeight);
	m_game->m_gameObjectManager.updateFramebufferSize(newWidth, newHeight);

	for (FramebufferSizeHook* hook : m_framebufferSizeHooks)
		hook->framebufferSizeCallback(width, height, newWidth, newHeight, m_game->m_gameObjectManager.m_graphicsObjectManager);
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

	for (CursorPosHook* hook : m_cursorPosHooks)
		hook->cursorPosCallback(*input);
}

void EventHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	InputManager* input = &(m_game->m_input);

	for (MouseButtonHook* hook : m_mouseButtonHooks)
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
	for (ScrollHook* hook : m_scrollHooks)
		hook->scrollCallback((float)xOffset, (float)yOffset, m_game->m_input);
}
