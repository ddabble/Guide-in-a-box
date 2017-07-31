#pragma once

#include <glm/glm.hpp>

#include "../../../../util/graphics/gl.h"
#include "../../../../event/types/FramebufferSizeHook_interface.h"

class Map;

class Arrow : public FramebufferSizeHook_interface
{
private:
	GLuint m_program;
	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject;

	GLint m_projection_uniformIndex;

private:
	void makeVertices(glm::vec2 startPoint, glm::vec2 endPoint, float lineWidth);

public:
	Arrow(const GraphicsObjectManager& graphicsObjectManager, const Map& map, glm::vec2 mapStartPoint, glm::vec2 mapEndPoint, float lineWidth = 0.025f);
	~Arrow();

	void graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager);

	void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager) override;
};
