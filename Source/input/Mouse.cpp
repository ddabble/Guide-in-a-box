#include "Mouse.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void Mouse::init(GLFWwindow* window, int windowHeight)
{
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	m_cursorPos = { (int)glm::floor(xPos), windowHeight - (int)glm::floor(yPos) - 1, 0, 0 };
}

void Mouse::updateCursorPos(double _xPos, double _yPos, int windowHeight)
{
	int xPos = (int)glm::floor(_xPos);
	int yPos = windowHeight - (int)glm::floor(_yPos) - 1;

	m_cursorPos = { xPos, yPos, (xPos - m_cursorPos.xPos), (yPos - m_cursorPos.yPos) };
}
