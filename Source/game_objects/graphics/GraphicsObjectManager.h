#pragma once

#include <vector>

class Game;
class EventHandler;
class Window;
class GraphicsObject_interface;

class GraphicsObjectManager
{
	friend class GameObjectManager;

private:
	std::vector<GraphicsObject_interface*> m_objects;

	const Game& m_game;
	const Window& m_window;

private:
	GraphicsObjectManager(const Game& game, EventHandler& eventHandler);
	~GraphicsObjectManager();

public:
	void graphicsUpdate();

public:
	const Game& getGame() const { return m_game; }

	const Window& getWindow() const { return m_window; }
};
