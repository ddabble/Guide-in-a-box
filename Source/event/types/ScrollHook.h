#pragma once

#include "../../input/InputManager.h"

class ScrollHook
{
public:
	virtual void scrollCallback(float xOffset, float yOffset, const InputManager& input) = 0;

	virtual ~ScrollHook() {}
};
