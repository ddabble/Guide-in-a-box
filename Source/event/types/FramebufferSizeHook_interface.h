#pragma once

#include "../../game_objects/graphics/GraphicsObjectManager.h"

class FramebufferSizeHook_interface
{
public:
	virtual void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager) = 0;

	virtual ~FramebufferSizeHook_interface() {}
};
