#pragma once

#include "../../input/InputManager.h"

class MouseButtonHook_interface
{
public:
	virtual void mouseButtonCallback(InputManager& input) = 0;
};
