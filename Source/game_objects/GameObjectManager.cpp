#include "GameObjectManager.h"

#include "../Game.h"

#include "../event/EventHandler.h"

GameObjectManager::GameObjectManager(const Game& game) : m_frameObjectManager(game), m_graphicsObjectManager(game), m_physicsObjectManager(game)
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
