#pragma once

class Window;
struct GLFWwindow;

struct CursorPos
{
	int xPos;
	int yPos;

	int deltaX;
	int deltaY;
};

class Mouse
{
	friend class EventHandler;

private:
	CursorPos m_cursorPos;

	/* Should be called every time the cursor is moved. */
	void updateCursorPos(double xPos, double yPos, const Window& window);

public:
	Mouse(const Window& window);

	const CursorPos& getCursorPos() const { return m_cursorPos; }

	// TODO:
	bool m_isLeftMouseButtonDown = 0;
};
