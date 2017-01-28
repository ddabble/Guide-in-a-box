#pragma once

#include <vector>

#include "../../../gl/gl.h"
#include "../GraphicsObject_interface.h"
#include "../../../event/types/FramebufferSizeHook_interface.h"

#include "HudObject_interface.h"

class EventHandler;

class HudManager : public GraphicsObject_interface, FramebufferSizeHook_interface
{
private:
	GLuint m_program;

	std::vector<HudObject_interface*> m_objects;

	void buildProgram();
	void registerHudObjects(const Game* game, EventHandler& eventHandler);

public:
	HudManager(const Game* game, EventHandler& eventHandler);
	~HudManager();

	void graphicsUpdate(const Game* game) override;

	void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight) override;
};
