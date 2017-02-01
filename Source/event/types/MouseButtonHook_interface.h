#pragma once

#include "../../input/InputManager.h"

class MouseButtonHook_interface
{
public:
	virtual void mouseButtonCallback(const InputManager& input) = 0;

	virtual ~MouseButtonHook_interface() {}
};
