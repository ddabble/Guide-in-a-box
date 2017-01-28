#include "EventHandler.h"

#include <iostream>

#include "../gl/gl.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../Game.h"

std::vector<EventHandler*> EventHandler::eventHandlers;

EventHandler::EventHandler(Game* game) : m_game(game)
{
	registerCallbacks(game->m_window.m_window);

	eventHandlers.push_back(this);
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
	for (EventHandler* eventHandler : eventHandlers)
		eventHandler->framebufferSize(window, newWidth, newHeight);
}
void EventHandler::framebufferSize(GLFWwindow* window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	int& width = m_game->m_window.m_windowWidth;
	int& height = m_game->m_window.m_windowHeight;

	for (auto& hook : m_framebufferSizeHooks)
		hook->framebufferSizeCallback(width, height, newWidth, newHeight);

	width = newWidth;
	height = newHeight;
}

void EventHandler::windowRefreshCallback(GLFWwindow* window)
{
	for (EventHandler* eventHandler : eventHandlers)
		eventHandler->windowRefresh(window);
}
void EventHandler::windowRefresh(GLFWwindow* window)
{
	m_game->frameUpdate();
	m_game->graphicsUpdate();

	glfwSwapBuffers(window);
}

void EventHandler::windowPosCallback(GLFWwindow* window, int xPos, int yPos)
{
	for (EventHandler* eventHandler : eventHandlers)
		eventHandler->windowPos(window, xPos, yPos);
}
void EventHandler::windowPos(GLFWwindow* window, int xPos, int yPos)
{
	m_game->frameUpdate();
	m_game->graphicsUpdate();

	glfwSwapBuffers(window);
}

void EventHandler::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	for (EventHandler* eventHandler : eventHandlers)
		eventHandler->cursorPosition(window, xPos, yPos);
}
void EventHandler::cursorPosition(GLFWwindow* window, double xPos, double yPos)
{
	InputManager& input = m_game->m_input;
	input.m_mouse.updateCursorPos(xPos, yPos, m_game->m_window);

	for (auto& hook : m_cursorPosHooks)
		hook->cursorPosCallback(input);
}

void EventHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	for (EventHandler* eventHandler : eventHandlers)
		eventHandler->mouseButton(window, button, action, mods);
}
void EventHandler::mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	InputManager& input = m_game->m_input;

	for (auto& hook : m_mouseButtonHooks)
		hook->mouseButtonCallback(input);

	// TODO:
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
			input.m_mouse.m_isLeftMouseButtonDown = true;
		else
			input.m_mouse.m_isLeftMouseButtonDown = false;
	}
}

void EventHandler::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	for (EventHandler* eventHandler : eventHandlers)
		eventHandler->scroll(window, xOffset, yOffset);
}
void EventHandler::scroll(GLFWwindow* window, double xOffset, double yOffset)
{
	InputManager& input = m_game->m_input;

	for (auto& hook : m_scrollHooks)
		hook->scrollCallback((float)xOffset, (float)yOffset, input);
}
