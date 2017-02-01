#pragma once

#include <vector>

#include "../../../gl/gl.h"

#include "../GraphicsObject_interface.h"
#include "../../../event/types/FramebufferSizeHook_interface.h"

#include "HudObject_interface.h"

class EventHandler;

class HudManager : public GraphicsObject_interface, FramebufferSizeHook_interface
{
	friend class GraphicsObjectManager;

private:
	GLuint m_program;

	std::vector<HudObject_interface*> m_objects;

	void buildProgram();
	void registerHudObjects(const GraphicsObjectManager& graphicsObjectManager, EventHandler& eventHandler);

private:
	HudManager(const GraphicsObjectManager& graphicsObjectManager, EventHandler& eventHandler);
	~HudManager();

public:
	void graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager) override;

	void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager) override;
};
