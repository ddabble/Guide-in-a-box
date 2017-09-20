#pragma once

#include <glm/glm.hpp>

#include "../../../util/graphics/gl.h"

class GraphicsObjectManager;

class HUDobject
{
protected:
	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject;
	GLuint m_textureObject;

	GLfloat m_vertexData[2 * 4 + 2 * 4];

protected:
	/*
	Derived class should call setCoords() after delegating to this constructor.
	Texture storage should be handled by the derived class.
	*/
	HUDobject(GLuint program, const GraphicsObjectManager& graphics);

	/* Texture storage should be handled by the derived class. */
	HUDobject(GLuint program, const GraphicsObjectManager& graphics, glm::vec2 pos, GLfloat width, GLfloat height);

public:
	virtual ~HUDobject() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphics);

	/* Should be called whenever the framebuffer is resized. */
	virtual void onFramebufferResize(int lastWidth, int lastHeight, int newWidth, int newHeight, GLuint program) { throw "Not implemented exception"; }
};
