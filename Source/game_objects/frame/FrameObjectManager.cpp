#include "FrameObjectManager.h"

#include "../../Game.h"
#include "FrameObject.h"

FrameObjectManager::FrameObjectManager(const Game& game) : m_game(game)
{

}

FrameObjectManager::~FrameObjectManager()
{
	//for (auto object : m_objects) delete object;
}

void FrameObjectManager::frameUpdate()
{
	//for (auto object : m_objects)
	//	object->frameUpdate(m_game);
}
