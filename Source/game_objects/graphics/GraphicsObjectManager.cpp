#include "GraphicsObjectManager.h"

#include "../../Game.h"
#include "GraphicsObject_interface.h"
#include "hud/HudManager.h"


#include "hud/objects/Arrow.h"
Arrow* arrow1;
Arrow* arrow2;

GraphicsObjectManager::GraphicsObjectManager(const Game& game, EventHandler& eventHandler) : m_game(game), m_window(game.getWindow())
{
	//glGenerateMipmap(GL_TEXTURE_2D);

	// Magnification/minification mipmapping
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glEnable(GL_PROGRAM_POINT_SIZE);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	glClearColor(0.3f, 0.3f, 0.3f, 1);

	m_objects.push_back(new HudManager(*this, eventHandler));

	arrow1 = new Arrow(*this, { 320, 192 }, { 960, 384 });
	arrow2 = new Arrow(*this, { 120, 192 }, { 460, 384 });
}

GraphicsObjectManager::~GraphicsObjectManager()
{
	for (int i = 0; i < m_objects.size(); i++)
		delete m_objects[i];

	delete arrow1;
	delete arrow2;
}

void GraphicsObjectManager::graphicsUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& object : m_objects)
		object->graphicsUpdate(*this);

	arrow1->graphicsUpdate(*this);
	arrow2->graphicsUpdate(*this);

	// Setup
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
	//glDrawArrays(GL_POINTS, 0, 1);

	glFlush();
}
