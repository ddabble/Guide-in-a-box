#version 330 core

//layout(location = 1) in vec2 texCoord_in;
//out vec2 texCoord;
//out vec4 worldCoord;

layout(location = 0) in vec4 vertexCoord;

uniform mat4 resize;

void main()
{
	//gl_Position = vertexCoord; texCoord = texCoord_in;
	//worldCoord = vertexCoord;

	/* Scaling matrix: mat4(mat3(1.5)) */

	gl_Position = resize * vertexCoord;
}
