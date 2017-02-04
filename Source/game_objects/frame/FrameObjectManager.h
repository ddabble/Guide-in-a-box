#pragma once

#include <vector>

class Game;
class EventHandler;
class FrameObject_interface;

class FrameObjectManager
{
	friend class GameObjectManager;

private:
	std::vector<FrameObject_interface*> m_objects;

	const Game& m_game;

private:
	FrameObjectManager(const Game& game);
	~FrameObjectManager();

public:
	void frameUpdate();
};
