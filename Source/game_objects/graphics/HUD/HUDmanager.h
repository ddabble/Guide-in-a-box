#pragma once

#include <vector>

#include "../../../util/graphics/gl.h"

#include "../GraphicsObject_interface.h"
#include "../../../event/types/FramebufferSizeHook_interface.h"

#include "HUDobject_interface.h"

class EventHandler;

class HUDmanager : public GraphicsObject_interface, FramebufferSizeHook_interface
{
	friend class GraphicsObjectManager;

private:
	GLuint m_program;

	std::vector<HUDobject_interface*> m_objects;

	void buildProgram();
	void registerHudObjects(const GraphicsObjectManager& graphicsObjectManager);

private:
	HUDmanager(const GraphicsObjectManager& graphicsObjectManager);
	~HUDmanager();

public:
	void graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager) override;

	void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager) override;
};
