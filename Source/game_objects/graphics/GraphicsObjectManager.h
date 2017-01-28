#pragma once

#include <vector>

class Game;
class EventHandler;
class GraphicsObject_interface;

class GraphicsObjectManager
{
private:
	std::vector<GraphicsObject_interface*> m_objects;

public:
	GraphicsObjectManager(const Game* game, EventHandler& eventHandler);
	~GraphicsObjectManager();

	void graphicsUpdate(const Game* game);
};
