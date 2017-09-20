#include "HUDobject_Dynamic.h"

#include "../GraphicsObjectManager.h"
#include "../../../screen/Window.h"

static constexpr GLfloat VERTEX_TEMPLATE[] =
{
	0, 0,
	1, 0,
	1, 1,
	0, 1
};

HUDobject_Dynamic::HUDobject_Dynamic(GLuint program, const GraphicsObjectManager& graphics)
	: HUDobject_Dynamic(program, graphics, { 0.0f, 0.0f }, (GLfloat)graphics.getWindow().getWidth(), (GLfloat)graphics.getWindow().getHeight()) {}

HUDobject_Dynamic::HUDobject_Dynamic(GLuint program, const GraphicsObjectManager& graphics, glm::vec2 pos, GLfloat width, GLfloat height) : HUDobject(program, graphics, pos, width, height)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexData), m_vertexData, GL_DYNAMIC_DRAW);
}

void HUDobject_Dynamic::graphicsUpdate(GLuint program, const GraphicsObjectManager& graphics)
{
	if (m_dirtyFlag)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_vertexData) / 2, m_vertexData);
		m_dirtyFlag = false;
	}

	HUDobject::graphicsUpdate(program, graphics);
}

void HUDobject_Dynamic::_setCoords(glm::vec2 pos, GLfloat width, GLfloat height, HUDobject_Dynamic& obj, GLfloat vertexData[])
{
	const GLfloat newVertexData[] =
	{
		pos.x,         pos.y,
		pos.x + width, pos.y,
		pos.x + width, pos.y + height,
		pos.x,         pos.y + height,
	};

	std::memcpy(vertexData, newVertexData, sizeof(newVertexData));

	obj.m_dirtyFlag = true;
}

void HUDobject_Dynamic::_setWidth(GLfloat width, HUDobject_Dynamic& obj, GLfloat vertexData[])
{
	vertexData[2] = vertexData[0] + width;
	vertexData[4] = vertexData[0] + width;

	obj.m_dirtyFlag = true;
}

void HUDobject_Dynamic::_setHeight(GLfloat height, HUDobject_Dynamic& obj, GLfloat vertexData[])
{
	vertexData[5] = vertexData[1] + height;
	vertexData[7] = vertexData[1] + height;

	obj.m_dirtyFlag = true;
}

void HUDobject_Dynamic::_move(glm::vec2 amount, HUDobject_Dynamic& obj, GLfloat vertexData[])
{
	for (int i = 0; i < 8; i += 2)
	{
		vertexData[i] += amount.x;
		vertexData[i + 1] += amount.y;
	}

	obj.m_dirtyFlag = true;
}

void HUDobject_Dynamic::_moveTo(glm::vec2 pos, HUDobject_Dynamic& obj, GLfloat vertexData[])
{
	_setCoords(pos, _getWidth(vertexData), _getHeight(vertexData), obj, vertexData);
}

void HUDobject_Dynamic::_zoom(GLfloat percentage, glm::vec2 focus, HUDobject_Dynamic& obj, GLfloat vertexData[])
{
	glm::vec2 pos = _getPos(vertexData);
	glm::vec2 zoomedFocus = (focus - pos) * percentage + pos;

	_setWidth(_getWidth(vertexData) * percentage, obj, vertexData);
	_setHeight(_getHeight(vertexData) * percentage, obj, vertexData);

	_move(focus - zoomedFocus, obj, vertexData);
}
