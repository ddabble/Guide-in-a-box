#pragma once

#include "HUDobject.h"

class HUDobject_Dynamic : public HUDobject
{
protected:
	/* User should call setCoords() after calling this constructor. */
	HUDobject_Dynamic(GLuint program, const GraphicsObjectManager& graphicsObjectManager);

	HUDobject_Dynamic(GLuint program, const GraphicsObjectManager& graphicsObjectManager, glm::vec2 pos, GLfloat width, GLfloat height);

public:
	virtual ~HUDobject_Dynamic() {}
};
