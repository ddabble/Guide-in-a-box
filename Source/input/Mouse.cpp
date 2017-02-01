#include "Mouse.h"

// Must be included before the GLFW header (contains gl/gl.h)
#include "../screen/Window.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

Mouse::Mouse(const Window& window)
{
	double xPos, yPos;
	glfwGetCursorPos(window.getGLFWwindow(), &xPos, &yPos);
	m_cursorPos = { (int)glm::floor(xPos), window.getHeight() - (int)glm::floor(yPos) - 1, 0, 0 };
}

void Mouse::updateCursorPos(double xPos, double yPos, const Window& window)
{
	int xPos_i = (int)glm::floor(xPos);
	int yPos_i = window.getHeight() - (int)glm::floor(yPos) - 1;

	m_cursorPos = { xPos_i, yPos_i, (xPos_i - m_cursorPos.xPos), (yPos_i - m_cursorPos.yPos) };
}
