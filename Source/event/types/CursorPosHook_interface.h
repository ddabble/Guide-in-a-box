#pragma once

#include "../../input/InputManager.h"

class CursorPosHook_interface
{
public:
	virtual void cursorPosCallback(InputManager& input) = 0;
};
