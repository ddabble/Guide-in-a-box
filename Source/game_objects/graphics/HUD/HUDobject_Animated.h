#pragma once

#include "HUDobject_Dynamic.h"

class HUDobject_Animated : public HUDobject_Dynamic
{
private:
	double m_animationStartTime;

protected:
	double m_animationEndTime;
	bool m_isAnimating = false;

	GLfloat m_vertexDataAnimationOrigin[4 * 2];
	GLfloat m_vertexDataAnimationDestination[4 * 2];

protected:
	/*
	Derived class should call setCoords() after delegating to this constructor.
	Texture storage should be handled by the derived class.
	*/
	HUDobject_Animated(GLuint program, const GraphicsObjectManager& graphicsObjectManager) : HUDobject_Dynamic(program, graphicsObjectManager) {}

	/* Texture storage should be handled by the derived class. */
	HUDobject_Animated(GLuint program, const GraphicsObjectManager& graphicsObjectManager, glm::vec2 pos, GLfloat width, GLfloat height)
		: HUDobject_Dynamic(program, graphicsObjectManager, pos, width, height) {}

public:
	virtual ~HUDobject_Animated() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager) override;

protected:
	/* pos is the position of the lower left corner. */
	void setCoords(glm::vec2 pos, GLfloat width, GLfloat height, float animationDuration);

	/* The return value is from the state the HUDobject will have after it has finished its current animation. */
	virtual GLfloat getWidth() const override { return (m_isAnimating ? _getWidth(m_vertexDataAnimationDestination) : HUDobject_Dynamic::getWidth()); }

	/* The return value is from the state the HUDobject will have after it has finished its current animation. */
	virtual GLfloat getHeight() const override { return (m_isAnimating ? _getHeight(m_vertexDataAnimationDestination) : HUDobject_Dynamic::getHeight()); }

	void setWidth(GLfloat width, float animationDuration);
	void setHeight(GLfloat height, float animationDuration);

	/*
	Returns the position of the lower left corner.
	The return value is from the state the HUDobject will have after it has finished its current animation.
	*/
	virtual glm::vec2 getPos() const override { return (m_isAnimating ? _getPos(m_vertexDataAnimationDestination) : HUDobject_Dynamic::getPos()); }

	void move(glm::vec2 amount, float animationDuration);

	/* pos is the position of the lower left corner. */
	void moveTo(glm::vec2 pos, float animationDuration);

	/*
	A percentage of 1.0f leaves the width and height unchanged.
	focus is a point of the HUDobject that should remain in the same place after zoom.
	*/
	void zoom(GLfloat percentage, float animationDuration, glm::vec2 focus);

private:
	enum animationFunction
	{
		SET_COORDS, SET_WIDTH, SET_HEIGHT, MOVE, MOVE_TO, ZOOM
	};

	void animate(animationFunction func, void* args[], float animationDuration);

	constexpr static void invoke(animationFunction func, void* args[], HUDobject_Dynamic& obj, GLfloat vertexData[8]);

private:
	using HUDobject_Dynamic::setCoords;
	using HUDobject_Dynamic::setWidth;
	using HUDobject_Dynamic::setHeight;
	using HUDobject_Dynamic::move;
	using HUDobject_Dynamic::moveTo;
	using HUDobject_Dynamic::zoom;
};
