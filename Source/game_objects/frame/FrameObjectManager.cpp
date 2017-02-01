#include "FrameObjectManager.h"

#include "FrameObject_interface.h"

FrameObjectManager::FrameObjectManager(const Game& game, EventHandler& eventHandler) : m_game(game)
{

}

FrameObjectManager::~FrameObjectManager()
{
	//for (int i = 0; i < m_objects.size(); i++)
	//	delete m_objects[i];
}

void FrameObjectManager::frameUpdate()
{
	//for (auto& object : m_objects)
	//	object->frameUpdate(game);
}
