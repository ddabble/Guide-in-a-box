#pragma once

class Game;

class PhysicsObject
{
public:
	virtual void physicsUpdate(const Game& game) = 0;

	virtual ~PhysicsObject() {}
};
