#pragma once

#include "hud/HudManager.h"

class Game;
class EventHandler;

class GameObjectManager
{
private:
	HudManager m_hudManager;

public:
	GameObjectManager() : m_hudManager(HudManager()) {}

	void init(const Game* game);

	void addEventHooks(EventHandler& eventHandler);

	void frameUpdate(const Game* game);
	void physicsUpdate(const Game* game);

	/* Should be called when the object data is not gonna be used anymore, including on program termination. */
	void deallocateData();
};
