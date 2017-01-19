#pragma once

#include <vector>

#include "../../gl/gl.h"
#include "../../event/types/I_FramebufferSizeHook.h"

#include "I_HudObject.h"

class EventHandler;

class HudManager : I_FramebufferSizeHook
{
private:
	GLuint m_program;

	std::vector<I_HudObject*> m_objects;

	void buildProgram();
	void registerHudObjects(const Game* game, EventHandler& eventHandler);

public:
	HudManager(const Game* game, EventHandler& eventHandler);
	~HudManager();

	void frameUpdate(const Game* game);
	void physicsUpdate(const Game* game);

	void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight) override;
};
