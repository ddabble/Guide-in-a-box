#pragma once

#include <glm/glm.hpp>
#include "../../../util/graphics/gl.h"

#include "../../../Game.h"
#include "../GraphicsObjectManager.h"

class HUDobject
{
protected:
	GLuint m_vertexArrayObject;

	GLint m_vertexData_uniformIndex;
	GLfloat m_vertexData[4 * 2 + 4 * 2];

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
