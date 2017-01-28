#pragma once

class Game;

class PhysicsObject_interface
{
public:
	virtual void physicsUpdate(const Game* game) = 0;
};
