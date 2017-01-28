#pragma once

#include "../../input/InputManager.h"

class ScrollHook_interface
{
public:
	virtual void scrollCallback(float xOffset, float yOffset, InputManager& input) = 0;
};
