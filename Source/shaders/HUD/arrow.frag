#version 330 core

//uniform sampler2D tex;
//in vec2 texCoord;
//in vec4 worldCoord;

out vec4 color;

void main()
{
	//color = texture(tex, texCoord);
	//if (worldCoord.y > 0) color = vec4(0.0, 0.0, 1.0, 1);

	if (!gl_FrontFacing)
		color = vec4(0.0, 0.0, 1.0, 1);
	else
		color = vec4(1.0, 0.0, 0.0, 1);
}
