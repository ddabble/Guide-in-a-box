#pragma once

#include "../I_HudObject_Animated.h"
#include "../../../event/types/I_CursorPosHook.h"
#include "../../../event/types/I_ScrollHook.h"

#include <glm/glm.hpp>

class Game;

class Map : public I_HudObject_Animated, I_CursorPosHook, I_ScrollHook
{
private:
	class ZoomLevel
	{
		static constexpr uint8_t LEVELS[6] = { 25, 37, 50, 75, 100, 200 };

	private:
		int m_levelIndex;

	public:
		ZoomLevel(int levelIndex = 4) : m_levelIndex(glm::clamp(levelIndex, 0, (int)sizeof(LEVELS) - 1)) {}

		uint8_t getLevel() { return LEVELS[m_levelIndex]; }

		float getPercentage() { return LEVELS[m_levelIndex] / 100.0f; }

		void setLevel(int levelIndex) { m_levelIndex = glm::clamp(levelIndex, 0, (int)sizeof(LEVELS) - 1); }

		ZoomLevel offsetLevel(int indexOffset)
		{
			m_levelIndex = glm::clamp(m_levelIndex + indexOffset, 0, (int)sizeof(LEVELS) - 1);
			return *this;
		}

		bool operator==(const ZoomLevel& other) { return m_levelIndex == other.m_levelIndex; }
	};

private:
	GLuint m_vertexArrayObject;

	GLuint m_textureObject;

	GLint m_vertexDataIndex;

	ZoomLevel m_zoomLevel;

public:
	Map(GLuint program, const Game* game, EventHandler& eventHandler);

	void cursorPosCallback(InputManager& input) override;
	void scrollCallback(float xOffset, float yOffset, InputManager& input) override;

	void frameUpdate(GLuint program, const Game* game) override;
};
