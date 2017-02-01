#include "PhysicsObjectManager.h"

#include "PhysicsObject_interface.h"

PhysicsObjectManager::PhysicsObjectManager(const Game& game, EventHandler& eventHandler) : m_game(game)
{

}

PhysicsObjectManager::~PhysicsObjectManager()
{
	//for (int i = 0; i < m_objects.size(); i++)
	//	delete m_objects[i];
}

void PhysicsObjectManager::physicsUpdate()
{
	//for (auto& object : m_objects)
	//	object->physicsUpdate(game);
}
