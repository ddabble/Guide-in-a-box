/*** VERTEX SHADER ***/
#version 330 core

//out vec4 worldCoord;

uniform mat4 projection;

layout(location = 0) in vec4 vert;

void main()
{
	//worldCoord = vertexCoord;

	/* Scaling matrix: mat4(mat3(1.5)) */

	gl_Position = projection * vert;
}


/*** GEOMETRY SHADER ***/
#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 9) out;

void main()
{
	for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();

		//vec4 nextPos = gl_in[(i + 1) % 3].gl_Position;
		//gl_Position = (gl_in[i].gl_Position + nextPos) / 2;
		////gl_Position += vec4(0, 0.1, 0, 0);
		//EmitVertex();

		//gl_Position = nextPos;
		//EmitVertex();

		//EndPrimitive();
	}
}


/*** FRAGMENT SHADER ***/
#version 330 core

//in vec4 worldCoord;

out vec4 fs_color;

void main()
{
	//if (worldCoord.y > 0) color = vec4(0.0, 0.0, 1.0, 1);

	if (!gl_FrontFacing)
		fs_color = vec4(0.0, 0.0, 1.0, 1);
	else
		fs_color = vec4(1.0, 0.0, 0.0, 1);
}
