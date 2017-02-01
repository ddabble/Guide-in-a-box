#pragma once

#include "../../input/InputManager.h"

class CursorPosHook_interface
{
public:
	virtual void cursorPosCallback(const InputManager& input) = 0;

	virtual ~CursorPosHook_interface() {}
};
