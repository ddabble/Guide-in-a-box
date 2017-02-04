#pragma once

#include <vector>
#include <glm/glm.hpp>

class Game;
class EventHandler;
class Window;
class GraphicsObject_interface;

class GraphicsObjectManager
{
	friend class GameObjectManager;

private:
	std::vector<GraphicsObject_interface*> m_objects;

	glm::mat4 m_resizeMatrix;

	const Game& m_game;
	const Window& m_window;

private:
	GraphicsObjectManager(const Game& game);
	~GraphicsObjectManager();

public:
	void graphicsUpdate();

public:
	const glm::mat4& getResizeMatrix() const { return m_resizeMatrix; }

	const Game& getGame() const { return m_game; }

	const Window& getWindow() const { return m_window; }
};
