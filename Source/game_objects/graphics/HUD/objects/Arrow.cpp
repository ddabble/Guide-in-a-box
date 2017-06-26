#include "Arrow.h"

#include "../../../../Game.h"

#include <iostream>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../../../SampleCode/LoadShaders.h"

constexpr Point rotatePointWithVector(Point point, Vector vector, float precomputedVectorLength)
{
	/*
	 * vector1 = (x1, y1), vector2 = (x2, y2), rotatedVector = (x', y')
	 *
	 * Complex multiplication:
	 *   (x1 + y1*i) * (x2 + y2*i)
	 * = x1*x2 + x1*y2*i + x2*y1*i + y1*y2*i^2
	 * = (x1*x2 - y1*y2) + (x1*y2 + x2*y1)*i
	 *
	 * x' = x1*x2 - y1*y2
	 * y' = x1*y2 + x2*y1
	 *
	 * |rotatedVector| = |vector1| * |vector2|
	 * |vector1| = |rotatedVector| / |vector2|
	 */

	Point rotatedPoint =
	{
		(point.x * vector.x - point.y * vector.y) / precomputedVectorLength,
		(point.x * vector.y + vector.x * point.y) / precomputedVectorLength
	};

	return rotatedPoint;
}

Point rotatePointWithVector(Point point, Vector vector)
{
	const float vectorLength = glm::sqrt(vector.x * vector.x + vector.y * vector.y);
	return rotatePointWithVector(point, vector, vectorLength);
}

Arrow::Arrow(const GraphicsObjectManager& graphicsObjectManager, Point arrowStartPoint, Point arrowEndPoint, int lineWidth)
{
	EventHandler::addFramebufferSizeHook(this);

	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "../../Source/shaders/HUD/arrow.vert" },
		{ GL_FRAGMENT_SHADER, "../../Source/shaders/HUD/arrow.frag" },
		{ GL_NONE, nullptr }
	};

	m_program = LoadShaders(shaders);
	glUseProgram(m_program);

	//glActiveTexture(GL_TEXTURE0 + 1);
	//GLint uniform = glGetUniformLocation(m_program, "tex");
	//// Sets the sampler to sample from texture unit 1
	//glUniform1i(uniform, 1);

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	GLuint buf;
	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);

	const Vector rotationVector = { arrowEndPoint.x - arrowStartPoint.x, arrowEndPoint.y - arrowStartPoint.y };
	const float length = glm::sqrt(rotationVector.x * rotationVector.x + rotationVector.y * rotationVector.y);

	const float diagonal = (float)glm::sqrt(2 * lineWidth * lineWidth);

	/*
	 *                                    l1------------l2
	 *                                       \          \
	 *                                        \          \
	 *                                       m1\          \
	 *              s1--------------------------\          \
	 *                |          /\              \ diagonal \
	 * arrowStartPoint|          || lineWidth   m3⟩ <------> ⟩ arrowEndPoint
	 *                |          \/              /          /
	 *              s2--------------------------/          /
	 *                                       m2/          /
	 *                                        /          /
	 *                                       /          /
	 *                                    r1------------r2
	 */

	// Relative to arrowStartPoint:
	Point s1 = rotatePointWithVector({ 0, lineWidth / 2.0f },                                 rotationVector, length);
	Point s2 = rotatePointWithVector({ 0, -lineWidth / 2.0f },                                rotationVector, length);

	// Relative to arrowEndPoint:
	Point m1 = rotatePointWithVector({ -lineWidth / 2.0f - diagonal + 1, lineWidth / 2.0f },  rotationVector, length);
	Point m2 = rotatePointWithVector({ -lineWidth / 2.0f - diagonal + 1, -lineWidth / 2.0f }, rotationVector, length);
	Point m3 = rotatePointWithVector({ -diagonal, 0 },                                        rotationVector, length);
	//                                 + 1 pixel is apparently needed to make the lines look perfectly straight
	Point l1 = rotatePointWithVector({ -20 - diagonal + 1, 20 },                              rotationVector, length);
	Point r1 = rotatePointWithVector({ -20 - diagonal + 1, -20 },                             rotationVector, length);
	Point l2 = rotatePointWithVector({ -20 + 1, 20 },                                         rotationVector, length);
	Point r2 = rotatePointWithVector({ -20 + 1, -20 },                                        rotationVector, length);

	s1 = { arrowStartPoint.x + s1.x, arrowStartPoint.y + s1.y };
	s2 = { arrowStartPoint.x + s2.x, arrowStartPoint.y + s2.y };
	m1 = { arrowEndPoint.x + m1.x, arrowEndPoint.y + m1.y };
	m2 = { arrowEndPoint.x + m2.x, arrowEndPoint.y + m2.y };
	m3 = { arrowEndPoint.x + m3.x, arrowEndPoint.y + m3.y };
	l1 = { arrowEndPoint.x + l1.x, arrowEndPoint.y + l1.y };
	r1 = { arrowEndPoint.x + r1.x, arrowEndPoint.y + r1.y };
	r2 = { arrowEndPoint.x + r2.x, arrowEndPoint.y + r2.y };
	l2 = { arrowEndPoint.x + l2.x, arrowEndPoint.y + l2.y };

	// TODO: the arrows have curvature proportional to how far away from the center of the window they are (using a geometry shader..?)
	GLfloat vertexData[] =
	{
		// Shaft, left half:
		arrowStartPoint.x, arrowStartPoint.y,
		s1.x, s1.y,
		m1.x, m1.y,
		m3.x, m3.y,
		// Shaft, right half:
		arrowStartPoint.x, arrowStartPoint.y,
		s2.x, s2.y,
		m2.x, m2.y,
		m3.x, m3.y,

		// Head, left half:
		arrowEndPoint.x, arrowEndPoint.y,
		m3.x, m3.y,
		l1.x, l1.y,
		l2.x, l2.y,
		// Head, right half:
		arrowEndPoint.x, arrowEndPoint.y,
		m3.x, m3.y,
		r1.x, r1.y,
		r2.x, r2.y
	};
	Window window = graphicsObjectManager.getWindow();
	for (int i = 0; i < sizeof(vertexData) / sizeof(GLfloat); i += 2)
	{
		vertexData[i] = window.pixelCoordsToWindowCoords_x(vertexData[i]);
		vertexData[i + 1] = window.pixelCoordsToWindowCoords_y(vertexData[i + 1]);
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	m_projection_uniformIndex = glGetUniformLocation(m_program, "projection");
	glUniformMatrix4fv(m_projection_uniformIndex, 1, GL_FALSE, glm::value_ptr(graphicsObjectManager.getResizeMatrix()));

	//glEnable(GL_MULTISAMPLE);
}

Arrow::~Arrow()
{
	EventHandler::removeFramebufferSizeHook(this);
}

void Arrow::graphicsUpdate(const GraphicsObjectManager& graphicsObjectManager)
{
	glUseProgram(m_program);

	//glActiveTexture(GL_TEXTURE0 + 1);
	//glBindTexture(GL_TEXTURE_2D, m_textureObject);

	glBindVertexArray(m_vertexArrayObject);

	constexpr GLint firsts[] = { 0, 4, 8, 12 };
	constexpr GLint counts[] = { 4, 4, 4, 4 };
	glMultiDrawArrays(GL_TRIANGLE_FAN, firsts, counts, 4);
}

void Arrow::framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphicsObjectManager)
{
	glUseProgram(m_program);
	glUniformMatrix4fv(m_projection_uniformIndex, 1, GL_FALSE, glm::value_ptr(graphicsObjectManager.getResizeMatrix()));
}
