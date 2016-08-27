#pragma once

#include "../../input/InputManager.h"

class I_MouseButtonHook
{
public:
	virtual void mouseButtonCallback(InputManager& input) = 0;
};
