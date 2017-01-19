#include "Mouse.h"

#include "../Game.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

Mouse::Mouse(const Game* game)
{
	Window window = game->getWindow();
	double xPos, yPos;
	glfwGetCursorPos(window.getGLFWwindow(), &xPos, &yPos);
	m_cursorPos = { (int)glm::floor(xPos), window.getHeight() - (int)glm::floor(yPos) - 1, 0, 0 };
}

void Mouse::updateCursorPos(double xPos, double yPos, Window window)
{
	int xPos_i = (int)glm::floor(xPos);
	int yPos_i = window.getHeight() - (int)glm::floor(yPos) - 1;

	m_cursorPos = { xPos_i, yPos_i, (xPos_i - m_cursorPos.xPos), (yPos_i - m_cursorPos.yPos) };
}
