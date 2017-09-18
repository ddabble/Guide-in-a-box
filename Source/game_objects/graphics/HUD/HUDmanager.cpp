#include "HUDmanager.h"

#include <glm/gtc/type_ptr.hpp>

#include "../../../event/EventHandler.h"
#include "../../../util/graphics/GLSLshaders.h"

#include "objects/Map.h"

HUDmanager::HUDmanager(const GraphicsObjectManager& graphicsObjectManager)
{
	EventHandler::addFramebufferSizeHook(this);
	m_program = glsl::loadShaders("../../Source/shaders/HUD/HUD_object.glsl");
	registerHUDobjects(graphicsObjectManager);
}

HUDmanager::~HUDmanager()
{
	EventHandler::removeFramebufferSizeHook(this);

	for (auto object : m_objects) delete object;
}

void HUDmanager::registerHUDobjects(const GraphicsObjectManager& graphicsObjectManager)
{
	glUseProgram(m_program);

	m_projection_uniformIndex = glGetUniformLocation(m_program, "projection");
	glUniformMatrix4fv(m_projection_uniformIndex, 1, GL_FALSE, glm::value_ptr(graphicsObjectManager.getProjectionMatrix()));

	glActiveTexture(GL_TEXTURE0);
	GLint uniform = glGetUniformLocation(m_program, "tex");
	glUniform1i(uniform, 0);

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
	glUseProgram(m_program);
	glUniformMatrix4fv(m_projection_uniformIndex, 1, GL_FALSE, glm::value_ptr(graphicsObjectManager.getProjectionMatrix()));

	for (auto object : m_objects)
		object->onFramebufferResize(lastWidth, lastHeight, newWidth, newHeight, m_program);
}
