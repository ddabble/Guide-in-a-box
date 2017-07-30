#pragma once

#include "../../../../util/graphics/gl.h"

#include "../../../../event/types/FramebufferSizeHook_interface.h"

struct Point
{
	float x;
	float y;
};
typedef Point Vector;
class Map;

class Arrow : public FramebufferSizeHook_interface
{
private:
	GLuint m_program;
	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject;

	GLint m_projection_uniformIndex;

private:
	void makeVertices(Point startPoint, Point endPoint, float lineWidth);

public:
	Arrow(const GraphicsObjectManager& graphicsObjectManager, const Map& map, Point mapStartPoint, Point mapEndPoint, float lineWidth = 0.025f);
	~Arrow();

	void graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager);

	void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager) override;
};
