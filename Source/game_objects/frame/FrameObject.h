#pragma once

class Game;

class FrameObject
{
public:
	virtual void frameUpdate(const Game& game) = 0;

	virtual ~FrameObject() {}
};
