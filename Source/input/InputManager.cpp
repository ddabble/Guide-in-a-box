#include "InputManager.h"

#include "../Game.h"

InputManager::InputManager(const Game& game) : m_mouse(Mouse(game.getWindow())), m_keyboard(Keyboard())
{

}
