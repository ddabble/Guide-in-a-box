#pragma once

#include "../../input/InputManager.h"

class I_ScrollHook
{
public:
	virtual void scrollCallback(float xOffset, float yOffset, InputManager& input) = 0;
};
