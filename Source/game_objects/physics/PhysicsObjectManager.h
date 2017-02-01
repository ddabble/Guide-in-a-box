#pragma once

#include <vector>

class Game;
class EventHandler;
class PhysicsObject_interface;

class PhysicsObjectManager
{
	friend class GameObjectManager;

private:
	std::vector<PhysicsObject_interface*> m_objects;

	const Game& m_game;

private:
	PhysicsObjectManager(const Game& game, EventHandler& eventHandler);
	~PhysicsObjectManager();

public:
	void physicsUpdate();
};
