#pragma once

#include <thread>

#include "screen/Window.h"
#include "event/EventHandler.h"
#include "game_objects/GameObjectManager.h"
#include "input/InputManager.h"

struct GLFWwindow;

class Game
{
	friend void main(int, char**);
	friend class EventHandler;

protected:
	Window m_window;

	EventHandler m_eventHandler;

	GameObjectManager m_gameObjectManager;

	InputManager m_input;

protected:
	Game();
	virtual ~Game();

	virtual void run();

	virtual void frameUpdate();
	virtual void graphicsUpdate();

protected:
	std::thread m_physicsThread;
	static void physics(Game* game);

	bool m_keepRunning = true;

	double m_lastPhysicsTime;
	bool m_hasSlept = false;

	virtual void runPhysics();

	virtual void physicsUpdate();

public:
	static constexpr unsigned int PHYSICS_UPDATES_PER_SECOND = 50;
	static constexpr double PHYSICS_UPDATE_INTERVAL = 1.0 / PHYSICS_UPDATES_PER_SECOND;

	virtual unsigned int getPhysicsUpdatesPerSecond() const { return PHYSICS_UPDATES_PER_SECOND; }
	virtual double getPhysicsUpdateInterval() const { return PHYSICS_UPDATE_INTERVAL; }

	const Window& getWindow() const { return m_window; }
};
