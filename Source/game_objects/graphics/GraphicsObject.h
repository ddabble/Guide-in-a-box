#pragma once

#include "GraphicsObjectManager.h"

class GraphicsObject
{
public:
	virtual void graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager) = 0;

	virtual ~GraphicsObject() {}
};
