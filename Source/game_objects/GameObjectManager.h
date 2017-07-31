#pragma once

#include "frame/FrameObjectManager.h"
#include "graphics/GraphicsObjectManager.h"
#include "physics/PhysicsObjectManager.h"

class GameObjectManager
{
	friend class Game;
	friend class EventHandler;

private:
	FrameObjectManager m_frameObjectManager;
	GraphicsObjectManager m_graphicsObjectManager;
	PhysicsObjectManager m_physicsObjectManager;

private:
	GameObjectManager(const Game& game);

	/* Should be called whenever the framebuffer is resized. */
	void updateFramebufferSize(int newWidth, int newHeight) { m_graphicsObjectManager.updateFramebufferSize(newWidth, newHeight); }

public:
	void frameUpdate();
	void graphicsUpdate();
	void physicsUpdate();
};
