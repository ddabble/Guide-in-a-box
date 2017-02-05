#include "HudManager.h"

#include "../../../event/EventHandler.h"
#include "../../../SampleCode/LoadShaders.h"

#include "objects/Map.h"

HudManager::HudManager(const GraphicsObjectManager& graphicsObjectManager)
{
	EventHandler::addFramebufferSizeHook(this);
	buildProgram();
	registerHudObjects(graphicsObjectManager);
}

HudManager::~HudManager()
{
	EventHandler::removeFramebufferSizeHook(this);

	for (auto object : m_objects) delete object;
}

void HudManager::buildProgram()
{
	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "../../Source/triangles.vert" },
		{ GL_FRAGMENT_SHADER, "../../Source/triangles.frag" },
		{ GL_NONE, nullptr }
	};

	m_program = LoadShaders(shaders);
}

void HudManager::registerHudObjects(const GraphicsObjectManager& graphicsObjectManager)
{
	glUseProgram(m_program);
	glActiveTexture(GL_TEXTURE0);

	GLint uniform = glGetUniformLocation(m_program, "tex");
	glUniform1i(uniform, 0);

	m_objects.push_back(new Map(m_program, graphicsObjectManager));
}

void HudManager::graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager)
{
	glUseProgram(m_program);
	glActiveTexture(GL_TEXTURE0);

	for (auto object : m_objects)
		object->graphicsUpdate(m_program, graphicsObjectManager);
}

void HudManager::framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager)
{
	for (auto object : m_objects)
		object->onFramebufferResize(lastWidth, lastHeight, newWidth, newHeight, m_program);
}
