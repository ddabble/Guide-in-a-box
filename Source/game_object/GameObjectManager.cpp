#include "GameObjectManager.h"

#include "../Game.h"
#include "../event/EventHandler.h"

void GameObjectManager::init(const Game* game)
{
	m_hudManager.init(game);
}

void GameObjectManager::addEventHooks(EventHandler& eventHandler)
{
	m_hudManager.addEventHooks(eventHandler);
}

void GameObjectManager::frameUpdate(const Game* game)
{
	m_hudManager.frameUpdate(game);
}

void GameObjectManager::physicsUpdate(const Game* game)
{
	m_hudManager.physicsUpdate(game);
}

void GameObjectManager::deallocateData()
{
	m_hudManager.deallocateData();
}
