#include "Map.h"

#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>

Map::Map(GLuint program, const Game* game) : I_HudObject(game)
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

	m_zoomPercentage = 100;
	m_transformationProgress = TRANSFORMATION_DURATION;

	this->setFields(width, height, 0, 0, true);
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
		move(cursorPos.deltaX, cursorPos.deltaY);
	}
}

enum zoomPercentages
{
	_25,
	_37,
	_50,
	_75,
	_100,
	_200
};

void Map::scrollCallback(float xOffset, float yOffset, InputManager& input)
{
#define MIN_ZOOM_PERCENTAGE 10
#define MAX_ZOOM_PERCENTAGE 200

	short newZoomPercentage = glm::clamp(m_zoomPercentage + (int)yOffset * 10, MIN_ZOOM_PERCENTAGE, MAX_ZOOM_PERCENTAGE);
	if (newZoomPercentage == m_zoomPercentage)
		return;
	else
		m_zoomPercentage = newZoomPercentage;

	CursorPos cursorPos = input.getMouse().getCursorPos();

	GLfloat oldVertexData[4 * 2 + 4 * 2];
	memcpy(oldVertexData, m_vertexData, sizeof(m_vertexData));

	zoom(int(m_pixelWidth * (m_zoomPercentage / 100.0f)), -1, (GLfloat)cursorPos.xPos / m_game->getWindowWidth(), (GLfloat)cursorPos.yPos / m_game->getWindowHeight());

	memcpy(m_vertexDataTransformationDestination, m_vertexData, sizeof(m_vertexData));
	memcpy(m_vertexData, oldVertexData, sizeof(oldVertexData));

	m_transformationProgress = 0;
}

void Map::frameUpdate(GLuint program, const Game* game)
{
	glUniform2fv(m_vertexDataIndex, 8, m_vertexData);

	glBindVertexArray(m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Map::physicsUpdate(const Game* game)
{
	if (m_transformationProgress < TRANSFORMATION_DURATION)
	{
		for (int i = 0; i < 8; i += 2)
		{
			m_vertexData[i] = m_vertexDataTransformationDestination[i] * m_transformationProgress / TRANSFORMATION_DURATION;
			m_vertexData[i + 1] = m_vertexDataTransformationDestination[i + 1] * m_transformationProgress / TRANSFORMATION_DURATION;
		}

		m_transformationProgress++;
	}
}
