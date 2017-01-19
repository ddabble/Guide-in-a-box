#pragma once

#include <vector>

#include "types/I_FramebufferSizeHook.h"
#include "types/I_CursorPosHook.h"
#include "types/I_MouseButtonHook.h"
#include "types/I_ScrollHook.h"

class Game;
struct GLFWwindow;

class EventHandler
{
	friend Game;

private:
	static std::vector<EventHandler*> eventHandlers;

	Game* m_game;

	std::vector<I_FramebufferSizeHook*> m_framebufferSizeHooks;
	std::vector<I_CursorPosHook*> m_cursorPosHooks;
	std::vector<I_MouseButtonHook*> m_mouseButtonHooks;
	std::vector<I_ScrollHook*> m_scrollHooks;

	EventHandler(Game* game);

public:
	void addFramebufferSizeHook(I_FramebufferSizeHook* hook) { m_framebufferSizeHooks.push_back(hook); }
	void addCursorPosHook(I_CursorPosHook* hook) { m_cursorPosHooks.push_back(hook); }
	void addMouseButtonHook(I_MouseButtonHook* hook) { m_mouseButtonHooks.push_back(hook); }
	void addScrollHook(I_ScrollHook* hook) { m_scrollHooks.push_back(hook); }

private:
	/*
	Must be called after the GLFWwindow has been initialized.
	Should be called after all event hooks have been added.
	Note: this does not register an error callback function, which should be registered before GLFW is initialized.
	*/
	static void registerCallbacks(GLFWwindow* window);

private:
	static void framebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight);
	void framebufferSize(GLFWwindow* window, int newWidth, int newHeight);

	static void windowRefreshCallback(GLFWwindow* window);
	void windowRefresh(GLFWwindow* window);

	static void windowPosCallback(GLFWwindow* window, int xPos, int yPos);
	void windowPos(GLFWwindow* window, int xPos, int yPos);

	static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
	void cursorPosition(GLFWwindow* window, double xPos, double yPos);

	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void mouseButton(GLFWwindow* window, int button, int action, int mods);

	static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	void scroll(GLFWwindow* window, double xOffset, double yOffset);
};
