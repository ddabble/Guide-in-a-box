#include "Arrow.h"

#include "../../../../Game.h"

#include <iostream>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Map.h"
#include "../../../../util/graphics/GLSLshaders.h"

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

Arrow::Arrow(const GraphicsObjectManager& graphicsObjectManager, const Map& map, Point mapStartPoint, Point mapEndPoint, int lineWidth)
{
	EventHandler::addFramebufferSizeHook(this);

	m_program = glsl::loadShaders("../../Source/shaders/HUD/arrow.glsl");
	glUseProgram(m_program);

	//glActiveTexture(GL_TEXTURE0 + 1);
	//GLint uniform = glGetUniformLocation(m_program, "tex");
	//// Sets the sampler to sample from texture unit 1
	//glUniform1i(uniform, 1);

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(1, &m_vertexBufferObject);

	Point lowerLeft = map.getLowerLeftCornerPos();
	Point diff = map.getUpperRightCornerPos() - lowerLeft;

	makeVertices(lowerLeft + diff * mapStartPoint,
				 lowerLeft + diff * mapEndPoint, lineWidth);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	m_projection_uniformIndex = glGetUniformLocation(m_program, "projection");
	glUniformMatrix4fv(m_projection_uniformIndex, 1, GL_FALSE, glm::value_ptr(graphicsObjectManager.getResizeMatrix()));

	//glEnable(GL_MULTISAMPLE);
}

void Arrow::makeVertices(Point startPoint, Point endPoint, int lineWidth)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

	const Vector rotationVector = { endPoint.x - startPoint.x, endPoint.y - startPoint.y };
	const float length = glm::sqrt(rotationVector.x * rotationVector.x + rotationVector.y * rotationVector.y);

	const float diagonal = glm::sqrt(2.0f * lineWidth * lineWidth);

	/*
	 *                               l1------------l2
	 *                                  \          \
	 *                                   \          \
	 *                                  m1\          \
	 *         s1--------------------------\          \
	 *           |          /\              \ diagonal \
	 * startPoint|          || lineWidth   m3⟩ <------> ⟩ endPoint
	 *           |          \/              /          /
	 *         s2--------------------------/          /
	 *                                  m2/          /
	 *                                   /          /
	 *                                  /          /
	 *                               r1------------r2
	 */

	// Relative to startPoint:
	Point s1 = rotatePointWithVector({ 0, lineWidth / 2.0f },                                 rotationVector, length);
	Point s2 = rotatePointWithVector({ 0, -lineWidth / 2.0f },                                rotationVector, length);

	// Relative to endPoint:
	Point m1 = rotatePointWithVector({ -lineWidth / 2.0f - diagonal, lineWidth / 2.0f },      rotationVector, length);
	Point m2 = rotatePointWithVector({ -lineWidth / 2.0f - diagonal, -lineWidth / 2.0f },     rotationVector, length);
	Point m3 = rotatePointWithVector({ -diagonal, 0 },                                        rotationVector, length);
	//                           TODO: + 1 pixel is apparently needed to make the lines look perfectly straight
	Point l1 = rotatePointWithVector({ -(lineWidth * 2.0f) - diagonal, (lineWidth * 2.0f) },  rotationVector, length);
	Point r1 = rotatePointWithVector({ -(lineWidth * 2.0f) - diagonal, -(lineWidth * 2.0f) }, rotationVector, length);
	Point l2 = rotatePointWithVector({ -(lineWidth * 2.0f), (lineWidth * 2.0f) },             rotationVector, length);
	Point r2 = rotatePointWithVector({ -(lineWidth * 2.0f), -(lineWidth * 2.0f) },            rotationVector, length);

	s1 = { startPoint.x + s1.x, startPoint.y + s1.y };
	s2 = { startPoint.x + s2.x, startPoint.y + s2.y };
	m1 = { endPoint.x + m1.x, endPoint.y + m1.y };
	m2 = { endPoint.x + m2.x, endPoint.y + m2.y };
	m3 = { endPoint.x + m3.x, endPoint.y + m3.y };
	l1 = { endPoint.x + l1.x, endPoint.y + l1.y };
	r1 = { endPoint.x + r1.x, endPoint.y + r1.y };
	r2 = { endPoint.x + r2.x, endPoint.y + r2.y };
	l2 = { endPoint.x + l2.x, endPoint.y + l2.y };

	// TODO: the arrows have curvature proportional to how far away from the center of the window they are (using a geometry shader..?)
	GLfloat vertexData[] =
	{
		// Shaft, left half:
		startPoint.x, startPoint.y,
		s1.x, s1.y,
		m1.x, m1.y,
		m3.x, m3.y,
		// Shaft, right half:
		startPoint.x, startPoint.y,
		s2.x, s2.y,
		m2.x, m2.y,
		m3.x, m3.y,

		// Head, left half:
		endPoint.x, endPoint.y,
		m3.x, m3.y,
		l1.x, l1.y,
		l2.x, l2.y,
		// Head, right half:
		endPoint.x, endPoint.y,
		m3.x, m3.y,
		r1.x, r1.y,
		r2.x, r2.y
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
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
