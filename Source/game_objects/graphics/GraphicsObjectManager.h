#pragma once

#include <vector>
#include <glm/glm.hpp>

class Game;
class EventHandler;
class Window;
class GraphicsObject;

class GraphicsObjectManager
{
	friend class GameObjectManager;

private:
	std::vector<GraphicsObject*> m_objects;

	glm::mat4 m_projectionMatrix;

	const Game& m_game;
	const Window& m_window;

private:
	GraphicsObjectManager(const Game& game);
	~GraphicsObjectManager();

	/* Should be called whenever the framebuffer is resized. */
	void updateFramebufferSize(int newWidth, int newHeight);

public:
	void graphicsUpdate();

public:
	const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }

	const Game& getGame() const { return m_game; }

	const Window& getWindow() const { return m_window; }
};
