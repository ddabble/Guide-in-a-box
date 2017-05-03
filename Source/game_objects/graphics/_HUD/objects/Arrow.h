#pragma once

#include "../../../../gl/gl.h"

#include "../../../../event/types/FramebufferSizeHook_interface.h"

struct Point
{
	float x;
	float y;
};
typedef Point Vector;

class Arrow : public FramebufferSizeHook_interface
{
private:
	GLuint m_program;
	GLuint m_vertexArrayObject;

	GLint resizeUniformIndex;

public:
	Arrow(const GraphicsObjectManager& graphicsObjectManager, Point arrowStartPoint, Point arrowEndPoint, int lineWidth = 10);
	~Arrow();

	void graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager);

	void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager) override;
};
