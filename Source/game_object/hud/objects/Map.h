#pragma once

#include "../../../Game.h"
#include "../I_HudObject.h"
#include "../../../event/types/I_CursorPosHook.h"
#include "../../../event/types/I_ScrollHook.h"

class Map : public I_HudObject, I_CursorPosHook, I_ScrollHook
{
private:
	GLuint m_vertexArrayObject;

	GLint m_vertexDataIndex;

	short m_zoomPercentage;

	GLfloat m_vertexDataTransformationDestination[4 * 2 + 4 * 2];
	uint8_t m_transformationProgress;
	static constexpr uint8_t TRANSFORMATION_DURATION = Game::PHYSICS_UPDATES_PER_SECOND /*/ 2*/ * 3;

public:
	Map(GLuint program, const Game* game);

	void addEventHooks(EventHandler& eventHandler) override;

	void cursorPosCallback(InputManager& input) override;
	void scrollCallback(float xOffset, float yOffset, InputManager& input) override;

	void frameUpdate(GLuint program, const Game* game) override;
	void physicsUpdate(const Game* game) override;
};
