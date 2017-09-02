#include "PhysicsObjectManager.h"

#include "../../Game.h"
#include "PhysicsObject.h"

PhysicsObjectManager::PhysicsObjectManager(const Game& game) : m_game(game)
{

}

PhysicsObjectManager::~PhysicsObjectManager()
{
	//for (auto object : m_objects) delete object;
}

void PhysicsObjectManager::physicsUpdate()
{
	//for (auto object : m_objects)
	//	object->physicsUpdate(m_game);
}
