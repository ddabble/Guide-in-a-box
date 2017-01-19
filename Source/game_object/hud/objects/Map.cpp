#include "Map.h"

#include "../../../Game.h"

#include <GLFW/glfw3.h>

#include "../../../texture/ImageDecompression.h"

Map::Map(GLuint program, const Game* game, EventHandler& eventHandler) : I_HudObject_Animated(game)
{
	eventHandler.addCursorPosHook(this);
	eventHandler.addScrollHook(this);

	int width, height;
	GLenum format;
	unsigned char* imageData = extractImageFrom7zFile("../../Source/map.7z", &width, &height, &format);

	glGenTextures(1, &m_textureObject);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, imageData);
	freeImageData(imageData);

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	constexpr GLint vertexIndices[] = { 0, 1, 2, 3 };

	GLuint buf;
	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);

	// Notice the "I" and the lack of a "normalized" argument
	glVertexAttribIPointer(0, 1, GL_INT, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	//glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	m_vertexDataIndex = glGetUniformLocation(program, "vertexData");

	m_zoomLevel = ZoomLevel();

	this->setFields(width, height, 0, 0, true, 1.0f / 4);
}

void Map::cursorPosCallback(InputManager& input)
{
	if (input.getMouse().m_isLeftMouseButtonDown)
	{
		CursorPos cursorPos = input.getMouse().getCursorPos();
		move(cursorPos.deltaX, cursorPos.deltaY, false);
	}
}

void Map::scrollCallback(float xOffset, float yOffset, InputManager& input)
{
	CursorPos cursorPos = input.getMouse().getCursorPos();

	ZoomLevel oldZoomLevel = m_zoomLevel;
	if (oldZoomLevel == m_zoomLevel.offsetLevel((int)yOffset))
		return;

	Window window = m_game->getWindow();
	zoom(int(m_pixelWidth * m_zoomLevel.getPercentage()), -1, true, (GLfloat)cursorPos.xPos / window.getWidth(), (GLfloat)cursorPos.yPos / window.getHeight());
}

void Map::frameUpdate(GLuint program, const Game* game)
{
	I_HudObject_Animated::frameUpdate(program, game);

	glUniform2fv(m_vertexDataIndex, 8, m_vertexData);

	glBindTexture(GL_TEXTURE_2D, m_textureObject);

	glBindVertexArray(m_vertexArrayObject);
	// TODO: glDrawElements instead?
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
