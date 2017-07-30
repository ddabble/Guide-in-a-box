﻿#include "Arrow.h"

#include "../../../../Game.h"

#include <iostream>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Map.h"
#include "../../../../util/graphics/GLSLshaders.h"

constexpr math::Point rotatePointWithVector(const math::Point point, const math::Vector vector, const float precomputedVectorLength)
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

	const math::Point rotatedPoint =
	{
		(point.x * vector.x - point.y * vector.y) / precomputedVectorLength,
		(point.x * vector.y + vector.x * point.y) / precomputedVectorLength
	};

	return rotatedPoint;
}

math::Point rotatePointWithVector(const math::Point point, const math::Vector vector)
{
	const float vectorLength = glm::sqrt(vector.x * vector.x + vector.y * vector.y);
	return rotatePointWithVector(point, vector, vectorLength);
}

Arrow::Arrow(const GraphicsObjectManager& graphicsObjectManager, const Map& map, const math::Point mapStartPoint, const math::Point mapEndPoint, const float lineWidth)
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

	const math::Point lowerLeft = map.getLowerLeftCornerPos();
	const math::Point diff = map.getUpperRightCornerPos() - lowerLeft;

	makeVertices(lowerLeft + diff * mapStartPoint,
				 lowerLeft + diff * mapEndPoint, lineWidth);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	m_projection_uniformIndex = glGetUniformLocation(m_program, "projection");
	glUniformMatrix4fv(m_projection_uniformIndex, 1, GL_FALSE, glm::value_ptr(graphicsObjectManager.getResizeMatrix()));

	//glEnable(GL_MULTISAMPLE);
}

void Arrow::makeVertices(const math::Point startPoint, const math::Point endPoint, const float lineWidth)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

	const math::Vector rotationVector = endPoint - startPoint;
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
	math::Point s1 = rotatePointWithVector({ 0, lineWidth / 2.0f },                                 rotationVector, length);
	math::Point s2 = rotatePointWithVector({ 0, -lineWidth / 2.0f },                                rotationVector, length);

	// Relative to endPoint:
	math::Point m1 = rotatePointWithVector({ -lineWidth / 2.0f - diagonal, lineWidth / 2.0f },      rotationVector, length);
	math::Point m2 = rotatePointWithVector({ -lineWidth / 2.0f - diagonal, -lineWidth / 2.0f },     rotationVector, length);
	math::Point m3 = rotatePointWithVector({ -diagonal, 0 },                                        rotationVector, length);
	//                                 TODO: + 1 pixel is apparently needed to make the lines look perfectly straight
	math::Point l1 = rotatePointWithVector({ -(lineWidth * 2.0f) - diagonal, (lineWidth * 2.0f) },  rotationVector, length);
	math::Point r1 = rotatePointWithVector({ -(lineWidth * 2.0f) - diagonal, -(lineWidth * 2.0f) }, rotationVector, length);
	math::Point l2 = rotatePointWithVector({ -(lineWidth * 2.0f), (lineWidth * 2.0f) },             rotationVector, length);
	math::Point r2 = rotatePointWithVector({ -(lineWidth * 2.0f), -(lineWidth * 2.0f) },            rotationVector, length);

	s1 += startPoint;
	s2 += startPoint;
	m1 += endPoint;
	m2 += endPoint;
	m3 += endPoint;
	l1 += endPoint;
	r1 += endPoint;
	l2 += endPoint;
	r2 += endPoint;

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
