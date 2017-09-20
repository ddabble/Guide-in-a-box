#pragma once

#include "HUDobject.h"

class HUDobject_Dynamic : public HUDobject
{
protected:
	bool m_dirtyFlag = false;

protected:
	/*
	Derived class should call setCoords() after delegating to this constructor.
	Texture storage should be handled by the derived class.
	*/
	HUDobject_Dynamic(GLuint program, const GraphicsObjectManager& graphics);

	/* Texture storage should be handled by the derived class. */
	HUDobject_Dynamic(GLuint program, const GraphicsObjectManager& graphics, glm::vec2 pos, GLfloat width, GLfloat height);

public:
	virtual ~HUDobject_Dynamic() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphics) override;

protected:
	/* pos is the position of the lower left corner. */
	virtual void setCoords(glm::vec2 pos, GLfloat width, GLfloat height) { _setCoords(pos, width, height, *this, m_vertexData); }

	virtual GLfloat getWidth() const { return _getWidth(m_vertexData); }
	virtual GLfloat getHeight() const { return _getHeight(m_vertexData); }

	virtual void setWidth(GLfloat width) { _setWidth(width, *this, m_vertexData); }
	virtual void setHeight(GLfloat height) { _setHeight(height, *this, m_vertexData); }

	/* Returns the position of the lower left corner. */
	virtual glm::vec2 getPos() const { return _getPos(m_vertexData); }

	virtual void move(glm::vec2 amount) { _move(amount, *this, m_vertexData); }

	/* pos is the position of the lower left corner. */
	virtual void moveTo(glm::vec2 pos) { _moveTo(pos, *this, m_vertexData); }

	/*
	A percentage of 1.0f leaves the width and height unchanged.
	focus is a point of the HUDobject that should remain in the same place after zoom.
	*/
	virtual void zoom(GLfloat percentage, glm::vec2 focus) { _zoom(percentage, focus, *this, m_vertexData); }

protected:
	static void _setCoords(glm::vec2 pos, GLfloat width, GLfloat height, HUDobject_Dynamic& obj, GLfloat vertexData[8]);

	constexpr static GLfloat _getWidth(const GLfloat vertexData[8]) { return vertexData[2] - vertexData[0]; }
	constexpr static GLfloat _getHeight(const GLfloat vertexData[8]) { return vertexData[5] - vertexData[3]; }

	static void _setWidth(GLfloat width, HUDobject_Dynamic& obj, GLfloat vertexData[8]);
	static void _setHeight(GLfloat height, HUDobject_Dynamic& obj, GLfloat vertexData[8]);

	static glm::vec2 _getPos(const GLfloat vertexData[8]) { return { vertexData[0], vertexData[1] }; }

	static void _move(glm::vec2 amount, HUDobject_Dynamic& obj, GLfloat vertexData[8]);
	static void _moveTo(glm::vec2 pos, HUDobject_Dynamic& obj, GLfloat vertexData[8]);

	static void _zoom(GLfloat percentage, glm::vec2 focus, HUDobject_Dynamic& obj, GLfloat vertexData[8]);

private:
	virtual void onFramebufferResize(int, int, int, int, GLuint) override {}
};
