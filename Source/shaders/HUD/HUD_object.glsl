/*** VERTEX SHADER ***/
#version 330 core

//layout(location = 0) in vec4 position;
//layout(location = 1) in vec2 in_tex_coord;

uniform mat4 projection;

layout(location = 0) in vec4 vert;
layout(location = 1) in vec2 texCoord;

out vec2 vs_texCoord;

void main()
{
	gl_Position = projection * vert;
	vs_texCoord = texCoord;

	//gl_PointSize = 200.0;
}


/*** FRAGMENT SHADER ***/
#version 330 core

uniform vec3 rainbow;
//uniform sampler2DArray tex;

uniform sampler2D tex;
in vec2 vs_texCoord;

out vec4 color;

void main()
{
	color = texture(tex, vs_texCoord);

	//color = texture(tex, vec3(vs_tex_coord, 0));
	//color = vec4(rainbow, 1.0);
	//color = texture(sprite_texture, gl_PointCoord);
}
