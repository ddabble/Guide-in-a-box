#pragma once

#include <glm/glm.hpp>

#include "../../GraphicsObject_interface.h"
#include "../../../../event/types/FramebufferSizeHook_interface.h"

#include "../../../../util/graphics/gl.h"

class Map;

class Arrow : public GraphicsObject_interface, FramebufferSizeHook_interface
{
private:
	GLuint m_program;
	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject;

	GLint m_projection_uniformIndex;

	const glm::vec2 m_mapStartPoint;
	const glm::vec2 m_mapEndPoint;

	const GLint m_lineWidth;

private:
	void makeVertices(const Map& map, GLint lineWidth);

public:
	Arrow(const GraphicsObjectManager& graphicsObjectManager, const Map& map, glm::vec2 mapStartPoint, glm::vec2 mapEndPoint, GLint lineWidth = 10);
	~Arrow();

	void updatePosition(const Map& map);

	void graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager) override;

	void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager) override;
};
