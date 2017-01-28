#include "GameObjectManager.h"

#include "../Game.h"

#include "../event/EventHandler.h"

GameObjectManager::GameObjectManager(const Game* game, EventHandler& eventHandler) : m_frameObjectManager(game, eventHandler), m_graphicsObjectManager(game, eventHandler), m_physicsObjectManager(game, eventHandler)
{

}

void GameObjectManager::frameUpdate(const Game* game)
{
	m_frameObjectManager.frameUpdate(game);
}

void GameObjectManager::graphicsUpdate(const Game* game)
{
	m_graphicsObjectManager.graphicsUpdate(game);
}

void GameObjectManager::physicsUpdate(const Game* game)
{
	m_physicsObjectManager.physicsUpdate(game);
}
