#include "HUDmanager.h"

#include "../../../event/EventHandler.h"
#include "../../../util/graphics/GLSLshaders.h"

#include "objects/Map.h"

HUDmanager::HUDmanager(const GraphicsObjectManager& graphicsObjectManager)
{
	EventHandler::addFramebufferSizeHook(this);

	m_program = glsl::loadShaders("../../Source/shaders/HUD/HUD_object.glsl");
	glUseProgram(m_program);

	glActiveTexture(GL_TEXTURE0);
	GLint uniform = glGetUniformLocation(m_program, "sampler");
	glUniform1i(uniform, 0);

	registerHUDobjects(graphicsObjectManager);
}

HUDmanager::~HUDmanager()
{
	EventHandler::removeFramebufferSizeHook(this);

	for (auto object : m_objects) delete object;
}

void HUDmanager::registerHUDobjects(const GraphicsObjectManager& graphicsObjectManager)
{
	m_objects.push_back(new Map(m_program, graphicsObjectManager));
}

void HUDmanager::graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager)
{
	glUseProgram(m_program);
	glActiveTexture(GL_TEXTURE0);

	for (auto object : m_objects)
		object->graphicsUpdate(m_program, graphicsObjectManager);
}

void HUDmanager::framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager)
{
	for (auto object : m_objects)
		object->onFramebufferResize(lastWidth, lastHeight, newWidth, newHeight, m_program);
}
