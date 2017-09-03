#include "Map.h"

#include "../../../../event/EventHandler.h"
#include "../../../../texture/ImageDecompression.h"

Map::Map(GLuint program, const GraphicsObjectManager& graphicsObjectManager) : HUDobject_Animated_interface(program, graphicsObjectManager)
{
	EventHandler::addCursorPosHook(this);
	EventHandler::addScrollHook(this);

	int width, height;
	GLenum format;
	unsigned char* imageData = extractImageFrom7zFile("../../Source/map.7z", &width, &height, &format);

	glGenTextures(1, &m_textureObject);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, imageData);
	freeImageData(imageData);

	//glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	this->setFields(width, height, 0, 0, true, 1.0f / 4);
}

Map::~Map()
{
	EventHandler::removeCursorPosHook(this);
	EventHandler::removeScrollHook(this);
}

void Map::cursorPosCallback(const InputManager& input)
{
	if (input.getMouse().m_isLeftMouseButtonDown)
	{
		glm::ivec2 cursorDelta = input.getMouse().getCursorDelta();
		move(cursorDelta.x, cursorDelta.y, false);
	}
}

void Map::scrollCallback(float xOffset, float yOffset, const InputManager& input)
{
	glm::ivec2 cursorPos = input.getMouse().getCursorPos();

	ZoomLevel oldZoomLevel = m_zoomLevel;
	if (oldZoomLevel == m_zoomLevel.offsetLevel((int)yOffset))
		return;

	const Window& window = m_graphicsObjectManager.getWindow();
	zoom(int(m_pixelWidth * m_zoomLevel.getPercentage()), -1, true, (GLfloat)cursorPos.x / window.getWidth(), (GLfloat)cursorPos.y / window.getHeight());
}

void Map::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
{
	glBindTexture(GL_TEXTURE_2D, m_textureObject);

	HUDobject_Animated_interface::graphicsUpdate(program, graphicsObjectManager);
	HUDobject_interface::graphicsUpdate(program, graphicsObjectManager);
}
