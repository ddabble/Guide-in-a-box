#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../HUDobject_Animated.h"
#include "../../../../event/types/CursorPosHook.h"
#include "../../../../event/types/ScrollHook.h"

class Arrow;

class Map : public HUDobject_Animated, CursorPosHook, ScrollHook
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
	int m_originalWidth;
	int m_originalHeight;

	ZoomLevel m_zoomLevel;

	std::vector<Arrow*> m_arrows;

public:
	Map(GLuint program, const GraphicsObjectManager& graphics);
	~Map();

	glm::vec2 getLowerLeftCornerPos() const { return { m_vertexData[0], m_vertexData[1] }; }
	glm::vec2 getUpperRightCornerPos() const { return { m_vertexData[4], m_vertexData[5] }; }

	void cursorPosCallback(const InputManager& input) override;
	void scrollCallback(float xOffset, float yOffset, const InputManager& input) override;

	void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphics) override;
};
