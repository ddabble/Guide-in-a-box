#include "GraphicsObjectManager.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../../Game.h"
#include "GraphicsObject_interface.h"
#include "hud/HudManager.h"


#include "hud/objects/Arrow.h"
Arrow* arrow1;
Arrow* arrow2;

GraphicsObjectManager::GraphicsObjectManager(const Game& game) : m_resizeMatrix(glm::mat4(1.0f)), m_game(game), m_window(game.getWindow())
{
	//glGenerateMipmap(GL_TEXTURE_2D);

	// Magnification/minification mipmapping
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glEnable(GL_PROGRAM_POINT_SIZE);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	glClearColor(0.3f, 0.3f, 0.3f, 1);

	m_objects.push_back(new HudManager(*this));

	arrow1 = new Arrow(*this, { 320, 192 }, { 960, 384 });
	arrow2 = new Arrow(*this, { 120, 192 }, { 460, 384 });
}

GraphicsObjectManager::~GraphicsObjectManager()
{
	for (auto object : m_objects) delete object;

	delete arrow1;
	delete arrow2;
}

void GraphicsObjectManager::graphicsUpdate()
{
	/*
	 * pixelPos = Xp, windowPos = Xw, windowWidth = width
	 *
	 * Xp = (Xw + 1)/2 * width
	 *
	 * On window resize:
	 * pixelPosBefore/After = Xp0/1, windowPosBefore/After = Xw0/1, windowWidthBefore/After = width0/1
	 *
	 * Xp0 = Xp1
	 * (Xw0 + 1)/2 * width0 = (Xw1 + 1)/2 * width1
	 * (Xw0 + 1) * width0/width1 = (Xw1 + 1)
	 * Xw1 = (Xw0 + 1) * width0/width1 - 1
	 * Xw1 = Xw0 * (width0/width1) + (width0/width1 - 1)
	 */

	float widthRatio = (float)Window::INITIAL_WINDOW_WIDTH / m_window.getWidth();
	float heightRatio = (float)Window::INITIAL_WINDOW_HEIGHT / m_window.getHeight();

	m_resizeMatrix = glm::translate(glm::mat4(1.0f), { widthRatio - 1, heightRatio - 1, 0.0f });
	m_resizeMatrix = glm::scale(m_resizeMatrix,      { widthRatio,     heightRatio,     1.0f });

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto object : m_objects)
		object->graphicsUpdate(*this);

	arrow1->graphicsUpdate(*this);
	arrow2->graphicsUpdate(*this);

	// Setup
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
	//glDrawArrays(GL_POINTS, 0, 1);

	glFlush();
}
