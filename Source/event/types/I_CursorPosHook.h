#pragma once

#include "../../input/InputManager.h"

class I_CursorPosHook
{
public:
	virtual void cursorPosCallback(InputManager& input) = 0;
};
