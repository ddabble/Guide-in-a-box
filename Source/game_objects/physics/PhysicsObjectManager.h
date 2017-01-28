#pragma once

#include <vector>

class Game;
class EventHandler;
class PhysicsObject_interface;

class PhysicsObjectManager
{
private:
	std::vector<PhysicsObject_interface*> m_objects;

public:
	PhysicsObjectManager(const Game* game, EventHandler& eventHandler);
	~PhysicsObjectManager();

	void physicsUpdate(const Game* game);
};
