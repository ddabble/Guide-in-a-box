#pragma once

#include "GraphicsObjectManager.h"

class GraphicsObject_interface
{
public:
	virtual void graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager) = 0;

	virtual ~GraphicsObject_interface() {}
};
