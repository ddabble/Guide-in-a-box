#version 330 core

uniform vec3 rainbow;
//uniform sampler2DArray tex;

uniform sampler2D tex;
in vec2 texCoord;

out vec4 color;

void main()
{
	color = texture(tex, texCoord);

	//color = texture(tex, vec3(vs_tex_coord, 0));
	//color = vec4(rainbow, 1.0);
	//color = texture(sprite_texture, gl_PointCoord);
}
