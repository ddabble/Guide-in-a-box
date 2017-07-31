#pragma once

#include "../HUDobject_Animated_interface.h"
#include "../../../../event/types/CursorPosHook_interface.h"
#include "../../../../event/types/ScrollHook_interface.h"

#include <glm/glm.hpp>

// TODO: Make Map observable
class Map : public HUDobject_Animated_interface, CursorPosHook_interface, ScrollHook_interface
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
	GLuint m_textureObject;

	ZoomLevel m_zoomLevel;

public:
	Map(GLuint program, const GraphicsObjectManager& graphicsObjectManager);
	~Map();

	glm::vec2 getLowerLeftCornerPos() const { return { m_vertexData[0], m_vertexData[1] }; }
	glm::vec2 getUpperRightCornerPos() const { return { m_vertexData[4], m_vertexData[5] }; }

	void cursorPosCallback(const InputManager& input) override;
	void scrollCallback(float xOffset, float yOffset, const InputManager& input) override;

	void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager) override;
};
