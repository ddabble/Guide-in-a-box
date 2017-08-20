#include "HUDobject_Dynamic.h"

HUDobject_Dynamic::HUDobject_Dynamic(GLuint program, const GraphicsObjectManager& graphicsObjectManager)
	: HUDobject_Dynamic(program, graphicsObjectManager, { 0.0f, 0.0f }, (GLfloat)graphicsObjectManager.getWindow().getWidth(), (GLfloat)graphicsObjectManager.getWindow().getHeight()) {}

HUDobject_Dynamic::HUDobject_Dynamic(GLuint program, const GraphicsObjectManager& graphicsObjectManager, glm::vec2 pos, GLfloat width, GLfloat height)
	: HUDobject(program, graphicsObjectManager, pos, width, height)
{
	constexpr GLint vertexIndices[] = { 0, 1, 2, 3 };
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_DYNAMIC_DRAW);
}
