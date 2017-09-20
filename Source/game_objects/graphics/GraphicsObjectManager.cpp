#include "GraphicsObjectManager.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../../Game.h"
#include "GraphicsObject.h"
#include "HUD/HUDmanager.h"

GraphicsObjectManager::GraphicsObjectManager(const Game& game) : m_game(game), m_window(game.getWindow())
{
	m_projectionMatrix = glm::ortho(0.0f, (float)m_window.getWidth(), 0.0f, (float)m_window.getHeight());

	//glGenerateMipmap(GL_TEXTURE_2D);

	// Magnification/minification mipmapping
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glEnable(GL_PROGRAM_POINT_SIZE);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	glClearColor(0.3f, 0.3f, 0.3f, 1);

	m_objects.push_back(new HUDmanager(*this));
}

GraphicsObjectManager::~GraphicsObjectManager()
{
	for (auto object : m_objects) delete object;
}

void GraphicsObjectManager::updateFramebufferSize(int newWidth, int newHeight)
{
	m_projectionMatrix = glm::ortho(0.0f, (float)newWidth, 0.0f, (float)newHeight);
}

void GraphicsObjectManager::graphicsUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (GraphicsObject* object : m_objects)
		object->graphicsUpdate(*this);

	// Setup
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
	//glDrawArrays(GL_POINTS, 0, 1);

	glFlush();
}
