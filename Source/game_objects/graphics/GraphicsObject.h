#pragma once

#include "GraphicsObjectManager.h"

class GraphicsObject
{
public:
	virtual void graphicsUpdate(const GraphicsObjectManager& graphics) = 0;

	virtual ~GraphicsObject() {}
};
