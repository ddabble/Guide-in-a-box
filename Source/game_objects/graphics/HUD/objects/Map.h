#pragma once

#include "../HUDobject_Animated_interface.h"
#include "../../../../event/types/CursorPosHook.h"
#include "../../../../event/types/ScrollHook.h"

#include <glm/glm.hpp>

class Map : public HUDobject_Animated_interface, CursorPosHook, ScrollHook
{
private:
	class ZoomLevel
	{
		static constexpr uint8_t LEVELS[6] = { 25, 37, 50, 75, 100, 200 };

		static int clamp(const int levelIndex) { return glm::clamp(levelIndex, 0, int(sizeof(LEVELS) / sizeof(uint8_t)) - 1); }

	private:
		int m_levelIndex;

	public:
		ZoomLevel(int levelIndex = 4) : m_levelIndex(clamp(levelIndex)) {}

		uint8_t getLevel() const { return LEVELS[m_levelIndex]; }

		float getPercentage() const { return LEVELS[m_levelIndex] / 100.0f; }

		void setLevel(int levelIndex) { m_levelIndex = clamp(levelIndex); }

		ZoomLevel offsetLevel(int indexOffset)
		{
			m_levelIndex = clamp(m_levelIndex + indexOffset);
			return *this;
		}

		bool operator==(const ZoomLevel& other) const { return m_levelIndex == other.m_levelIndex; }
	};

private:
	GLuint m_textureObject;

	ZoomLevel m_zoomLevel;

public:
	Map(GLuint program, const GraphicsObjectManager& graphicsObjectManager);
	~Map();

	void cursorPosCallback(const InputManager& input) override;
	void scrollCallback(float xOffset, float yOffset, const InputManager& input) override;

	void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager) override;
};
