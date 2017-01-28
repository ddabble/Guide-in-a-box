#pragma once

#include <vector>

class Game;
class EventHandler;
class FrameObject_interface;

class FrameObjectManager
{
private:
	std::vector<FrameObject_interface*> m_objects;

public:
	FrameObjectManager(const Game* game, EventHandler& eventHandler);
	~FrameObjectManager();

	void frameUpdate(const Game* game);
};
