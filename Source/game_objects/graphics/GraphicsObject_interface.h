#pragma once

class Game;

class GraphicsObject_interface
{
public:
	virtual void graphicsUpdate(const Game* game) = 0;
};
