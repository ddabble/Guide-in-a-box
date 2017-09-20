/*** VERTEX SHADER ***/
#version 330 core

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

//uniform vec3 rainbow;

//uniform sampler2DArray sampler;
uniform sampler2D sampler;

in vec2 vs_texCoord;

out vec4 fs_color;

void main()
{
	fs_color = texture(sampler, vs_texCoord);

	//fs_color = texture(sampler, vec3(vs_texCoord, 0));
	//fs_color = vec4(rainbow, 1.0);
	//fs_color = texture(sprite_texture, gl_PointCoord);
}
