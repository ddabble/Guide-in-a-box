#pragma once

#include "Mouse.h"
#include "Keyboard.h"

class Game;

// TODO: Rename class? - Doesn't "manage" in the same way HudManager does..
class InputManager
{
	friend class EventHandler;

private:
	Mouse m_mouse;
	Keyboard m_keyboard;

public:
	InputManager(const Game* game) : m_mouse(Mouse(game)), m_keyboard(Keyboard()) {}

	Mouse& getMouse() { return m_mouse; }
	Keyboard& getKeyboard() { return m_keyboard; }
};
