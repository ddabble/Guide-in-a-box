#include "Map.h"

#include "../../../../texture/ImageDecompression.h"

#include "Arrow.h"

Map::Map(GLuint program, const GraphicsObjectManager& graphicsObjectManager) : HUDobject_Animated(program, graphicsObjectManager)
{
	EventHandler::addCursorPosHook(this);
	EventHandler::addScrollHook(this);

	GLenum format;
	unsigned char* imageData = extractImageFrom7zFile("../../Source/map.7z", &m_originalWidth, &m_originalHeight, &format);

	glGenTextures(1, &m_textureObject);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_originalWidth, m_originalHeight);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_originalWidth, m_originalHeight, format, GL_UNSIGNED_BYTE, imageData);
	freeImageData(imageData);

	//glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	m_zoomLevel = ZoomLevel();

	this->setCoords({ 0.0f, 0.0f }, (GLfloat)m_originalWidth, (GLfloat)m_originalHeight, 0);



	m_arrows.push_back(new Arrow(graphicsObjectManager, *this, { 0.03f, 0.06f }, { 0.03f, 0.2f }));
	float mapAspectRatio = 3712.0f / 3333;
	m_arrows.push_back(new Arrow(graphicsObjectManager, *this, { 0.06f, 0.06f * mapAspectRatio }, { 0.15f,  0.15f * mapAspectRatio }));
	m_arrows.push_back(new Arrow(graphicsObjectManager, *this, { 0.06f, 0.03f }, { 0.27f, 0.03f }));
}

Map::~Map()
{
	EventHandler::removeCursorPosHook(this);
	EventHandler::removeScrollHook(this);

	for (auto arrow : m_arrows) delete arrow;
}

void Map::cursorPosCallback(const InputManager& input)
{
	if (input.getMouse().m_isLeftMouseButtonDown)
	{
		CursorPos cursorPos = input.getMouse().getCursorPos();
		move({ cursorPos.deltaX, cursorPos.deltaY }, 0);
	}
}

void Map::scrollCallback(float xOffset, float yOffset, const InputManager& input)
{
	CursorPos cursorPos = input.getMouse().getCursorPos();

	ZoomLevel oldZoomLevel = m_zoomLevel;
	if (oldZoomLevel == m_zoomLevel.offsetLevel((int)yOffset))
		return;

	GLfloat currentWidth = getWidth();
	GLfloat newWidth = m_originalWidth * m_zoomLevel.getPercentage();

	zoom(newWidth / currentWidth, 1.0f / 4.0f, cursorPos);
}

void Map::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
{
	glBindTexture(GL_TEXTURE_2D, m_textureObject);

	HUDobject_Animated::graphicsUpdate(program, graphicsObjectManager);

	if (m_dirtyFlag)
	{
		for (Arrow* arrow : m_arrows)
			arrow->updatePosition(*this);
	}

	HUDobject_Dynamic::graphicsUpdate(program, graphicsObjectManager);

	for (Arrow* arrow : m_arrows)
		arrow->graphicsUpdate(graphicsObjectManager);
}
