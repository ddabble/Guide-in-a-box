#include "GameObjectManager.h"

#include "../Game.h"

#include "../event/EventHandler.h"

GameObjectManager::GameObjectManager(const Game& game, EventHandler& eventHandler) : m_frameObjectManager(game, eventHandler), m_graphicsObjectManager(game, eventHandler), m_physicsObjectManager(game, eventHandler)
{

}

void GameObjectManager::frameUpdate()
{
	m_frameObjectManager.frameUpdate();
}

void GameObjectManager::graphicsUpdate()
{
	m_graphicsObjectManager.graphicsUpdate();
}

void GameObjectManager::physicsUpdate()
{
	m_physicsObjectManager.physicsUpdate();
}
