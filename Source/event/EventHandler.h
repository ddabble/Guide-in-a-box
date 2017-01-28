#pragma once

#include <vector>

#include "types/FramebufferSizeHook_interface.h"
#include "types/CursorPosHook_interface.h"
#include "types/MouseButtonHook_interface.h"
#include "types/ScrollHook_interface.h"

class Game;
struct GLFWwindow;

class EventHandler
{
	friend Game;

private:
	static std::vector<EventHandler*> eventHandlers;

	Game* m_game;

	std::vector<FramebufferSizeHook_interface*> m_framebufferSizeHooks;
	std::vector<CursorPosHook_interface*> m_cursorPosHooks;
	std::vector<MouseButtonHook_interface*> m_mouseButtonHooks;
	std::vector<ScrollHook_interface*> m_scrollHooks;

	EventHandler(Game* game);

public:
	void addFramebufferSizeHook(FramebufferSizeHook_interface* hook) { m_framebufferSizeHooks.push_back(hook); }
	void addCursorPosHook(CursorPosHook_interface* hook) { m_cursorPosHooks.push_back(hook); }
	void addMouseButtonHook(MouseButtonHook_interface* hook) { m_mouseButtonHooks.push_back(hook); }
	void addScrollHook(ScrollHook_interface* hook) { m_scrollHooks.push_back(hook); }

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
