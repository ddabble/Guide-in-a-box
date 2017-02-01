#include "HudManager.h"

#include "../../../event/EventHandler.h"
#include "../../../SampleCode/LoadShaders.h"

#include "objects/Map.h"

HudManager::HudManager(const GraphicsObjectManager& graphicsObjectManager, EventHandler& eventHandler)
{
	eventHandler.addFramebufferSizeHook(this);
	buildProgram();
	registerHudObjects(graphicsObjectManager, eventHandler);
}

HudManager::~HudManager()
{
	for (int i = 0; i < m_objects.size(); i++)
		delete m_objects[i];
}

void HudManager::buildProgram()
{
	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "../../Source/triangles.vert" },
		{ GL_FRAGMENT_SHADER, "../../Source/triangles.frag" },
		{ GL_NONE, NULL }
	};

	m_program = LoadShaders(shaders);
}

void HudManager::registerHudObjects(const GraphicsObjectManager& graphicsObjectManager, EventHandler& eventHandler)
{
	glUseProgram(m_program);
	glActiveTexture(GL_TEXTURE0);

	GLint uniform = glGetUniformLocation(m_program, "tex");
	glUniform1i(uniform, 0);

	m_objects.push_back(new Map(m_program, graphicsObjectManager, eventHandler));
}

void HudManager::graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager)
{
	glUseProgram(m_program);
	glActiveTexture(GL_TEXTURE0);

	for (auto& object : m_objects)
		object->graphicsUpdate(m_program, graphicsObjectManager);
}

void HudManager::framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager)
{
	for (auto& object : m_objects)
		object->onFramebufferResize(lastWidth, lastHeight, newWidth, newHeight);
}
