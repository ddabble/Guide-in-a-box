#pragma once

#include "../HudObject_Animated_interface.h"
#include "../../../../event/types/CursorPosHook_interface.h"
#include "../../../../event/types/ScrollHook_interface.h"

#include <glm/glm.hpp>

class Map : public HudObject_Animated_interface, CursorPosHook_interface, ScrollHook_interface
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
	Map(GLuint program, const GraphicsObjectManager& graphicsObjectManager, EventHandler& eventHandler);

	void cursorPosCallback(const InputManager& input) override;
	void scrollCallback(float xOffset, float yOffset, const InputManager& input) override;

	void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager) override;
};
