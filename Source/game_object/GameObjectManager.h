#pragma once

#include "hud/HudManager.h"

class Game;
class EventHandler;

class GameObjectManager
{
private:
	HudManager m_hudManager;

public:
	GameObjectManager(const Game* game, EventHandler& eventHandler);

	void frameUpdate(const Game* game);
	void physicsUpdate(const Game* game);
};
