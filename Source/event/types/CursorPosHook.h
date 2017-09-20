#pragma once

#include "../../input/InputManager.h"

class CursorPosHook
{
public:
	virtual void cursorPosCallback(const InputManager& input) = 0;

	virtual ~CursorPosHook() {}
};
