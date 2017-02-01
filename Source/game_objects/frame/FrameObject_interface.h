#pragma once

class Game;

class FrameObject_interface
{
public:
	virtual void frameUpdate(const Game& game) = 0;

	virtual ~FrameObject_interface() {}
};
