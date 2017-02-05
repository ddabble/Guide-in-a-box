#version 330 core

//layout(location = 0) in vec4 position;
//layout(location = 1) in vec2 in_tex_coord;

uniform vec2[8] vertexData;
uniform mat4 resize;

layout(location = 0) in int i;

out vec2 texCoord;

void main()
{
	gl_Position = resize * vec4(vertexData[i], 0, 1);
	texCoord = vertexData[4 + i];

	//gl_PointSize = 200.0;
}
