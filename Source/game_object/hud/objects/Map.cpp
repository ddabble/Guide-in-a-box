#include "Map.h"

#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Map::Map(GLuint program, const Game* game) : I_HudObject_Animated(game)
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, components;
	unsigned char* imageData = stbi_load("../../Source/map.png", &width, &height, &components, 0);
	GLenum format = (components == 4) ? GL_RGBA : GL_RGB;

	GLuint mapTexture;
	glGenTextures(1, &mapTexture);
	glBindTexture(GL_TEXTURE_2D, mapTexture);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, imageData);
	stbi_image_free(imageData);

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

void Map::addEventHooks(EventHandler& eventHandler)
{
	eventHandler.addCursorPosHook(this);
	eventHandler.addScrollHook(this);
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

	zoom(int(m_pixelWidth * m_zoomLevel.getPercentage()), -1, true, (GLfloat)cursorPos.xPos / m_game->getWindowWidth(), (GLfloat)cursorPos.yPos / m_game->getWindowHeight());
}

void Map::frameUpdate(GLuint program, const Game* game)
{
	I_HudObject_Animated::frameUpdate(program, game);

	glUniform2fv(m_vertexDataIndex, 8, m_vertexData);

	glBindVertexArray(m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
