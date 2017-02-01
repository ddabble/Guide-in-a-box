#pragma once

#include "../../input/InputManager.h"

class ScrollHook_interface
{
public:
	virtual void scrollCallback(float xOffset, float yOffset, const InputManager& input) = 0;

	virtual ~ScrollHook_interface() {}
};
