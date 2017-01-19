#include "GameObjectManager.h"

#include "../Game.h"

#include "../event/EventHandler.h"

GameObjectManager::GameObjectManager(const Game* game, EventHandler& eventHandler) : m_hudManager(game, eventHandler)
{

}

void GameObjectManager::frameUpdate(const Game* game)
{
	m_hudManager.frameUpdate(game);
}

void GameObjectManager::physicsUpdate(const Game* game)
{
	m_hudManager.physicsUpdate(game);
}
