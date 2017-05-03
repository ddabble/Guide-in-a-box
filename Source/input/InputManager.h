#pragma once

#include "Mouse.h"
#include "Keyboard.h"

// TODO: Rename class? - Doesn't "manage" in the same way HUDmanager does..
class InputManager
{
	friend class Game;
	friend class EventHandler;

private:
	Mouse m_mouse;
	Keyboard m_keyboard;

private:
	InputManager(const Game& game);

public:
	const Mouse& getMouse() const { return m_mouse; }
	const Keyboard& getKeyboard() const { return m_keyboard; }
};
