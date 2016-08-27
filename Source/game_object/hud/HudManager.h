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

	void registerHudObjects(const Game* game);

public:
	void init(const Game* game);

	void addEventHooks(EventHandler& eventHandler);

	void frameUpdate(const Game* game);
	void physicsUpdate(const Game* game);

	void framebufferSizeCallback(int width, int height) override;

	/* Should be called when the object data is not gonna be used anymore, including on program termination. */
	void deallocateData();
};
