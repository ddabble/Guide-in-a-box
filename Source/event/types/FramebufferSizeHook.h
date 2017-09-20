#pragma once

#include "../../game_objects/graphics/GraphicsObjectManager.h"

class FramebufferSizeHook
{
public:
	virtual void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphics) = 0;

	virtual ~FramebufferSizeHook() {}
};
