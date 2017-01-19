#include "HudManager.h"

#include "../../event/EventHandler.h"
#include "../../SampleCode/LoadShaders.h"

#include "objects/Map.h"

HudManager::HudManager(const Game* game, EventHandler& eventHandler)
{
	eventHandler.addFramebufferSizeHook(this);
	buildProgram();
	registerHudObjects(game, eventHandler);
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

void HudManager::registerHudObjects(const Game* game, EventHandler& eventHandler)
{
	glUseProgram(m_program);
	glActiveTexture(GL_TEXTURE0);

	GLint uniform = glGetUniformLocation(m_program, "tex");
	glUniform1i(uniform, 0);

	m_objects.push_back(new Map(m_program, game, eventHandler));
}

void HudManager::frameUpdate(const Game* game)
{
	glUseProgram(m_program);
	glActiveTexture(GL_TEXTURE0);

	for (auto& object : m_objects)
		object->frameUpdate(m_program, game);
}

void HudManager::physicsUpdate(const Game* game)
{
	for (auto& object : m_objects)
		object->physicsUpdate(game);
}

void HudManager::framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight)
{
	for (auto& object : m_objects)
		object->onFramebufferResize(lastWidth, lastHeight, newWidth, newHeight);
}
