#pragma once

#include <glm/glm.hpp>

class Window;
struct GLFWwindow;

class Mouse
{
	friend class EventHandler;

private:
	glm::ivec2 m_cursorPos;
	glm::ivec2 m_cursorDelta;

	/* Should be called every time the cursor is moved. */
	void updateCursorPos(double xPos, double yPos, const Window& window);

public:
	Mouse(const Window& window);

	/* Returns the cursor position in pixels relative to the lower left corner of the window. */
	const glm::ivec2& getCursorPos() const { return m_cursorPos; }

	/* Returns the difference between the current cursor position and the last one. */
	const glm::ivec2& getCursorDelta() const { return m_cursorDelta; }

	// TODO:
	bool m_isLeftMouseButtonDown = 0;
};
