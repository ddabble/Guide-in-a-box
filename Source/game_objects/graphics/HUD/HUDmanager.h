#pragma once

#include <vector>

#include "../../../util/graphics/gl.h"

#include "../GraphicsObject.h"
#include "../../../event/types/FramebufferSizeHook.h"

#include "HUDobject.h"

class HUDmanager : public GraphicsObject, FramebufferSizeHook
{
	friend class GraphicsObjectManager;

private:
	GLuint m_program;

	GLint m_projection_uniformIndex;

	std::vector<HUDobject*> m_objects;

	void registerHUDobjects(const GraphicsObjectManager& graphics);

private:
	HUDmanager(const GraphicsObjectManager& graphics);
	~HUDmanager();

public:
	void graphicsUpdate(const GraphicsObjectManager& graphics) override;

	void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphics) override;
};
