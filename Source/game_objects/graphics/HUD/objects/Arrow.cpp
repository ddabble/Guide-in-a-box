#include "Arrow.h"

#include "../../../../Game.h"

#include <iostream>
#include <stb_image.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Map.h"
#include "../../../../util/graphics/GLSLshaders.h"

glm::vec2 rotatePointWithVector(const glm::vec2 point, const glm::vec2 vector, const float precomputedVectorLength)
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

	const glm::vec2 rotatedPoint =
	{
		(point.x * vector.x - point.y * vector.y) / precomputedVectorLength,
		(point.x * vector.y + vector.x * point.y) / precomputedVectorLength
	};

	return rotatedPoint;
}

glm::vec2 rotatePointWithVector(const glm::vec2 point, const glm::vec2 vector)
{
	const float vectorLength = glm::sqrt(vector.x * vector.x + vector.y * vector.y);
	return rotatePointWithVector(point, vector, vectorLength);
}

Arrow::Arrow(const GraphicsObjectManager& graphics, const Map& map, const glm::vec2 mapStartPoint, const glm::vec2 mapEndPoint, const GLint lineWidth)
	: m_mapStartPoint(mapStartPoint), m_mapEndPoint(mapEndPoint), m_lineWidth(lineWidth)
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

	makeVertices(map, m_lineWidth);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	m_projection_uniformIndex = glGetUniformLocation(m_program, "projection");
	glUniformMatrix4fv(m_projection_uniformIndex, 1, GL_FALSE, glm::value_ptr(graphics.getProjectionMatrix()));

	//glEnable(GL_MULTISAMPLE);
}

void Arrow::makeVertices(const Map& map, const GLint lineWidth)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

	const glm::vec2 lowerLeft = map.getLowerLeftCornerPos();
	const glm::vec2 diff = map.getUpperRightCornerPos() - lowerLeft;

	const glm::vec2 startPoint = lowerLeft + diff * m_mapStartPoint;
	const glm::vec2 endPoint = lowerLeft + diff * m_mapEndPoint;

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

	const glm::vec2 rotationVector = endPoint - startPoint;
	const float length = glm::sqrt(rotationVector.x * rotationVector.x + rotationVector.y * rotationVector.y);

	const float diagonal = glm::sqrt(2.0f * lineWidth * lineWidth);

	glm::vec2 s1 = startPoint + rotatePointWithVector({ 0.0f,  lineWidth / 2.0f },                           rotationVector, length);
	glm::vec2 s2 = startPoint + rotatePointWithVector({ 0.0f, -lineWidth / 2.0f },                           rotationVector, length);

	glm::vec2 m1 = endPoint + rotatePointWithVector({ -lineWidth / 2.0f - diagonal,  lineWidth / 2.0f },     rotationVector, length);
	glm::vec2 m2 = endPoint + rotatePointWithVector({ -lineWidth / 2.0f - diagonal, -lineWidth / 2.0f },     rotationVector, length);
	glm::vec2 m3 = endPoint + rotatePointWithVector({ -diagonal, 0.0f },                                     rotationVector, length);

	glm::vec2 l1 = endPoint + rotatePointWithVector({ -(lineWidth * 2.0f) - diagonal,  (lineWidth * 2.0f) }, rotationVector, length);
	glm::vec2 r1 = endPoint + rotatePointWithVector({ -(lineWidth * 2.0f) - diagonal, -(lineWidth * 2.0f) }, rotationVector, length);
	glm::vec2 l2 = endPoint + rotatePointWithVector({ -(lineWidth * 2.0f),             (lineWidth * 2.0f) }, rotationVector, length);
	glm::vec2 r2 = endPoint + rotatePointWithVector({ -(lineWidth * 2.0f),            -(lineWidth * 2.0f) }, rotationVector, length);

	// TODO: the arrows have curvature proportional to how far away from the center of the window they are (using a geometry shader..?)
	const GLfloat vertexData[] =
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

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);
}

Arrow::~Arrow()
{
	EventHandler::removeFramebufferSizeHook(this);
}

void Arrow::updatePosition(const Map& map)
{
	makeVertices(map, m_lineWidth);
}

void Arrow::graphicsUpdate(const GraphicsObjectManager& graphics)
{
	glUseProgram(m_program);

	//glActiveTexture(GL_TEXTURE0 + 1);
	//glBindTexture(GL_TEXTURE_2D, m_textureObject);

	glBindVertexArray(m_vertexArrayObject);

	constexpr GLint firsts[] = { 0, 4, 8, 12 };
	constexpr GLint counts[] = { 4, 4, 4, 4 };
	glMultiDrawArrays(GL_TRIANGLE_FAN, firsts, counts, 4);
}

void Arrow::framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight, const GraphicsObjectManager& graphics)
{
	glUseProgram(m_program);
	glUniformMatrix4fv(m_projection_uniformIndex, 1, GL_FALSE, glm::value_ptr(graphics.getProjectionMatrix()));
}
