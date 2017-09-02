#pragma once

#include "../../input/InputManager.h"

class MouseButtonHook
{
public:
	virtual void mouseButtonCallback(const InputManager& input) = 0;

	virtual ~MouseButtonHook() {}
};
