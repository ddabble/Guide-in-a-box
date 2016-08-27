#pragma once

#include "Mouse.h"
#include "Keyboard.h"

class InputManager
{
	friend class EventHandler;

private:
	Mouse m_mouse;
	Keyboard m_keyboard;

public:
	InputManager() : m_mouse(Mouse()), m_keyboard(Keyboard()) {}

	Mouse& getMouse() { return m_mouse; }
	Keyboard& getKeyboard() { return m_keyboard; }
};
