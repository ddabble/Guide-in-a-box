#include "util/graphics/gl.h"
#include "SampleCode/LoadShaders.h"

void triangles()
{
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//GLfloat vertices[][2] =
	//{
	//	// Triangle 1
	//	{ -0.90f, -0.90f },
	//	{  0.85f, -0.90f },
	//	{ -0.90f,  0.85f },
	//	// Triangle 2
	//	{  0.90f, -0.85f },
	//	{  0.90f,  0.90f },
	//	{ -0.85f,  0.90f }
	//};

	//GLuint buf;
	//glGenBuffers(1, &buf);
	//glBindBuffer(GL_ARRAY_BUFFER, buf);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0,					// index
	//					  2,					// size (number of components per vertex)
	//					  GL_FLOAT,				// type (of each element in array)
	//					  GL_FALSE,				// normalization
	//					  0,					// stride (byte offset between elements in array)
	//					  BUFFER_OFFSET(0));	// offset (from start of buffer object)
	//glEnableVertexAttribArray(0);

	//glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

void arrayTextures()
{
	//static const GLfloat quad_data[] =
	//{
	//	// Vertex positions
	//	-0.75f, -0.75f,
	//	 0.75f, -0.75f,
	//	 0.75f,  0.75f,
	//	-0.75f,  0.75f,
	//	// Texture coordinates
	//	0, 1,
	//	1, 1,
	//	1, 0,
	//	0, 0
	//};

	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//GLuint buf;
	//glGenBuffers(1, &buf);
	//glBindBuffer(GL_ARRAY_BUFFER, buf);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(8 * sizeof(GLfloat)));

	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

	//int width, height, comp;
	//unsigned char* data = stbi_load("../../Source/Turtle1.jpg", &width, &height, &comp, 0);

	//GLuint texture;
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
	//glTexStorage3D(GL_TEXTURE_2D_ARRAY,	// target
	//			   1,					// mipmap levels
	//			   GL_RGB8,				// internal format
	//			   width, height, 2);	// width, height and depth
	//glTexSubImage3D(GL_TEXTURE_2D_ARRAY,		// target
	//				0,							// mipmap level
	//				0, 0, 0,					// x, y and z offset
	//				width, height, 1,			// width, height and depth
	//				GL_RGB, GL_UNSIGNED_BYTE,	// format and type
	//				data);						// data
	//stbi_image_free(data);

	//data = stbi_load("../../Source/Turtle2.jpg", &width, &height, &comp, 0);
	//glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
	//				0,
	//				0, 0, 1,
	//				width, height, 1,
	//				GL_RGB, GL_UNSIGNED_BYTE,
	//				data);
	//stbi_image_free(data);
}

void simplestDrawingCode()
{
	//const GLchar* vShader =
	//{
	//	"#version 330 core\n"
	//	"layout(location = 0) in vec4 position;"
	//	"void main() { gl_Position = position; }"
	//};

	//const GLchar* fShader =
	//{
	//	"#version 330 core\n"
	//	"out vec4 color;"
	//	"void main() { color = vec4(1, 0, 1, 1); }"
	//};

	//GLuint program = glCreateProgram();

	//GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(shader, 1, &vShader, NULL);
	//glCompileShader(shader);
	//glAttachShader(program, shader);

	//shader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(shader, 1, &fShader, NULL);
	//glCompileShader(shader);
	//glAttachShader(program, shader);

	//glLinkProgram(program);
	//glUseProgram(program);

	//GLuint vao;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//GLuint buf;
	//glGenBuffers(1, &buf);
	//glBindBuffer(GL_ARRAY_BUFFER, buf);
	//const GLfloat pointVertex[] = { 0, 0 };
	//glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertex), pointVertex, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	//glEnableVertexAttribArray(0);

	//glPointSize(20);

	//glDrawArrays(GL_POINTS, 0, 1);
	//glFlush();
}
