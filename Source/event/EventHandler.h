#pragma once

#include <vector>

#include "types/FramebufferSizeHook.h"
#include "types/CursorPosHook.h"
#include "types/MouseButtonHook.h"
#include "types/ScrollHook.h"

struct GLFWwindow;

class EventHandler
{
	friend class Game;

private:
	static Game* m_game;

	static std::vector<FramebufferSizeHook*> m_framebufferSizeHooks;
	static std::vector<CursorPosHook*> m_cursorPosHooks;
	static std::vector<MouseButtonHook*> m_mouseButtonHooks;
	static std::vector<ScrollHook*> m_scrollHooks;

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
	static void addFramebufferSizeHook(FramebufferSizeHook* hook) { m_framebufferSizeHooks.push_back(hook); }
	static void addCursorPosHook(CursorPosHook* hook) { m_cursorPosHooks.push_back(hook); }
	static void addMouseButtonHook(MouseButtonHook* hook) { m_mouseButtonHooks.push_back(hook); }
	static void addScrollHook(ScrollHook* hook) { m_scrollHooks.push_back(hook); }

	/*
	The respective function below must be called before the deletion of the pointer to a hook.
	*/
	static void removeFramebufferSizeHook(FramebufferSizeHook* hook);
	static void removeCursorPosHook(CursorPosHook* hook);
	static void removeMouseButtonHook(MouseButtonHook* hook);
	static void removeScrollHook(ScrollHook* hook);

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
