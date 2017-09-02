#pragma once

#include <vector>

class Game;
class EventHandler;
class PhysicsObject;

class PhysicsObjectManager
{
	friend class GameObjectManager;

private:
	std::vector<PhysicsObject*> m_objects;

	const Game& m_game;

private:
	PhysicsObjectManager(const Game& game);
	~PhysicsObjectManager();

public:
	void physicsUpdate();
};
