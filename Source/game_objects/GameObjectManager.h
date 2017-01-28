#pragma once

#include "frame/FrameObjectManager.h"
#include "graphics/GraphicsObjectManager.h"
#include "physics/PhysicsObjectManager.h"

class Game;
class EventHandler;

class GameObjectManager
{
private:
	FrameObjectManager m_frameObjectManager;
	GraphicsObjectManager m_graphicsObjectManager;
	PhysicsObjectManager m_physicsObjectManager;

public:
	GameObjectManager(const Game* game, EventHandler& eventHandler);

	void frameUpdate(const Game* game);
	void graphicsUpdate(const Game* game);
	void physicsUpdate(const Game* game);
};
