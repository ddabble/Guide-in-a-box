#include "HUDmanager.h"

#include <glm/gtc/type_ptr.hpp>

#include "../../../event/EventHandler.h"
#include "../../../util/graphics/GLSLshaders.h"

#include "objects/Map.h"
#include "objects/Arrow.h"
Arrow* arrow1;
Arrow* arrow2;
Arrow* arrow3;

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

	delete arrow1;
	delete arrow2;
	delete arrow3;
}

void HUDmanager::registerHUDobjects(const GraphicsObjectManager& graphicsObjectManager)
{
	glUseProgram(m_program);

	m_projection_uniformIndex = glGetUniformLocation(m_program, "projection");
	glUniformMatrix4fv(m_projection_uniformIndex, 1, GL_FALSE, glm::value_ptr(graphicsObjectManager.getProjectionMatrix()));

	glActiveTexture(GL_TEXTURE0);
	GLint uniform = glGetUniformLocation(m_program, "tex");
	glUniform1i(uniform, 0);

	Map* map = new Map(m_program, graphicsObjectManager);
	m_objects.push_back(map);

	//arrow1 = new Arrow(graphicsObjectManager, { 100, 200 }, { 100, 650 });
	//arrow2 = new Arrow(graphicsObjectManager, { 200, 200 }, { 500, 500 });
	//arrow3 = new Arrow(graphicsObjectManager, { 200, 100 }, { 999, 100 });

	arrow1 = new Arrow(graphicsObjectManager, *map, { 0.03f, 0.06f }, { 0.03f, 0.2f });

	float mapAspectRatio = 3712.0f / 3333;
	arrow2 = new Arrow(graphicsObjectManager, *map, { 0.06f, 0.06f * mapAspectRatio }, { 0.15f,  0.15f * mapAspectRatio });

	arrow3 = new Arrow(graphicsObjectManager, *map, { 0.06f, 0.03f }, { 0.27f, 0.03f });
}

void HUDmanager::graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager)
{
	glUseProgram(m_program);
	glActiveTexture(GL_TEXTURE0);

	for (auto object : m_objects)
		object->graphicsUpdate(m_program, graphicsObjectManager);

	arrow1->graphicsUpdate(graphicsObjectManager);
	arrow2->graphicsUpdate(graphicsObjectManager);
	arrow3->graphicsUpdate(graphicsObjectManager);
}

void HUDmanager::framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager)
{
	glUseProgram(m_program);
	glUniformMatrix4fv(m_projection_uniformIndex, 1, GL_FALSE, glm::value_ptr(graphicsObjectManager.getProjectionMatrix()));

	for (auto object : m_objects)
		object->onFramebufferResize(lastWidth, lastHeight, newWidth, newHeight, m_program);
}
