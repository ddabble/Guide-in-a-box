#include "Mouse.h"

// Must be included before the GLFW header (contains util/graphics/gl.h)
#include "../screen/Window.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

Mouse::Mouse(const Window& window)
{
	double xPos, yPos;
	glfwGetCursorPos(window.getGLFWwindow(), &xPos, &yPos);

	updateCursorPos(xPos, yPos, window);
	m_cursorDelta = { 0, 0 };
}

void Mouse::updateCursorPos(double xPos, double yPos, const Window& window)
{
	//                                              // Converts the cursor position to being relative to the lower left corner
	glm::ivec2 newCursorPos = { (int)glm::floor(xPos), window.getHeight() - (int)glm::floor(yPos) - 1 };

	m_cursorDelta = { newCursorPos - m_cursorPos };
	m_cursorPos = newCursorPos;
}
