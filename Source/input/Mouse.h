#pragma once

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
	friend class Game;
	friend class EventHandler;

private:
	CursorPos m_cursorPos;

	void init(GLFWwindow* window, int windowHeight);

	void updateCursorPos(double _xPos, double _yPos, int windowHeight);

public:
	const CursorPos& getCursorPos() { return m_cursorPos; }

	// TODO:
	bool m_isLeftMouseButtonDown = 0;
};
