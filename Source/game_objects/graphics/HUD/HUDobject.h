#pragma once

#include <glm/glm.hpp>
#include "../../../util/graphics/gl.h"

class GraphicsObjectManager;

class HUDobject
{
protected:
	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject;

	GLfloat m_vertexData[2 * 4 + 2 * 4];

protected:
	/* User should call setCoords() after calling this constructor. */
	HUDobject(GLuint program, const GraphicsObjectManager& graphicsObjectManager);

	HUDobject(GLuint program, const GraphicsObjectManager& graphicsObjectManager, glm::vec2 pos, GLfloat width, GLfloat height);

public:
	virtual ~HUDobject() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager);

	/* Should be called whenever the framebuffer is resized. */
	virtual void onFramebufferResize(int lastWidth, int lastHeight, int newWidth, int newHeight, GLuint program) { throw "Not implemented exception"; }
};
