#pragma once

#include <vector>

#include "types/FramebufferSizeHook_interface.h"
#include "types/CursorPosHook_interface.h"
#include "types/MouseButtonHook_interface.h"
#include "types/ScrollHook_interface.h"

struct GLFWwindow;

class EventHandler
{
	friend Game;

private:
	static Game* m_game;

	static std::vector<FramebufferSizeHook_interface*> m_framebufferSizeHooks;
	static std::vector<CursorPosHook_interface*> m_cursorPosHooks;
	static std::vector<MouseButtonHook_interface*> m_mouseButtonHooks;
	static std::vector<ScrollHook_interface*> m_scrollHooks;

	/*
	Must be called before any eventhandlin' can be done.
	*/
	static void init(Game& game);

	EventHandler() {}

public:
	/*
	Functions below have to be passed pointers to heap ("new").
	Deletion of the pointers must be handled from the caller's side.
	*/
	static void addFramebufferSizeHook(FramebufferSizeHook_interface* hook) { m_framebufferSizeHooks.push_back(hook); }
	static void addCursorPosHook(CursorPosHook_interface* hook) { m_cursorPosHooks.push_back(hook); }
	static void addMouseButtonHook(MouseButtonHook_interface* hook) { m_mouseButtonHooks.push_back(hook); }
	static void addScrollHook(ScrollHook_interface* hook) { m_scrollHooks.push_back(hook); }

private:
	/*
	Must be called after the GLFWwindow has been initialized.
	Should be called after all event hooks have been added.
	Note: this does not register an error callback function, which should be registered before GLFW is initialized.
	*/
	static void registerCallbacks(GLFWwindow* window);

private:
	static void framebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight);

	static void windowRefreshCallback(GLFWwindow* window);

	static void windowPosCallback(GLFWwindow* window, int xPos, int yPos);

	static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};
