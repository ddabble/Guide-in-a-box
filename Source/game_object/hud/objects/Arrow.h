#pragma once

#include <stb_image.h>
#include <glm/gtc/type_ptr.hpp>
#include "../../../Game.h"

class Arrow
{
private:
	GLuint m_program;
	GLuint m_vertexArrayObject;

	GLint resizeUniformIndex;

public:
	void compileProgram()
	{
		const GLchar* vShader =
		{
			"#version 330 core\n"
			"layout(location = 0) in vec4 vertexCoord;"
			"uniform mat4 resize;"
			//"layout(location = 1) in vec2 texCoord_in;"
			//"out vec2 texCoord;"
			//"out vec4 worldCoord;"
			"void main() {"
			//"gl_Position = vertexCoord; texCoord = texCoord_in;"
			//"worldCoord = vertexCoord;"
			// Scaling matrix: mat4(mat3(1.5))
			"gl_Position = resize * vertexCoord;"
			"}"
		};

		const GLchar* fShader =
		{
			"#version 330 core\n"
			//"uniform sampler2D tex;"
			//"in vec2 texCoord;"
			"out vec4 color;"
			//"in vec4 worldCoord;"
			"void main() {"
			//"color = texture(tex, texCoord);"
			//"if (worldCoord.y > 0) color = vec4(0.0, 0.0, 1.0, 1);"
			"if (!gl_FrontFacing) color = vec4(0.0, 0.0, 1.0, 1);"
			"else color = vec4(1.0, 0.0, 0.0, 1);"
			"}"
		};

		m_program = glCreateProgram();

		GLuint shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shader, 1, &vShader, NULL);
		glCompileShader(shader);
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			std::cerr << "Shader compilation failed: " << log << std::endl;
			delete[] log;
		}
		glAttachShader(m_program, shader);

		shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shader, 1, &fShader, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			std::cerr << "Shader compilation failed: " << log << std::endl;
			delete[] log;
		}
		glAttachShader(m_program, shader);

		glLinkProgram(m_program);
		GLint linked;
		glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLsizei len;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(m_program, len, &len, log);
			std::cerr << "Shader linking failed: " << log << std::endl;
			delete[] log;
		}
	}

	struct Point
	{
		float x;
		float y;
	};
	typedef Point Vector;

	Point rotatePointWithVector(Point point, Vector vector, float vectorLength = -1.0f)
	{
		/*
		vector1 = (x1, y1), vector2 = (x2, y2), rotatedVector = (x', y')

		Complex multiplication:
		  (x1 + y1*i) * (x2 + y2*i)
		= x1*x2 + x1*y2*i + x2*y1*i + y1*y2*i^2
		= (x1*x2 - y1*y2) + (x1*y2 + x2*y1)*i

		x' = x1*x2 - y1*y2
		y' = x1*y2 + x2*y1

		|rotatedVector| = |vector1| * |vector2|
		|vector1| = |rotatedVector| / |vector2|
		*/

		if (vectorLength == -1.0f)
			vectorLength = glm::sqrt(vector.x * vector.x + vector.y * vector.y);

		Point rotatedPoint =
		{
			(point.x * vector.x - point.y * vector.y) / vectorLength,
			(point.x * vector.y + vector.x * point.y) / vectorLength
		};

		return rotatedPoint;
	}

	glm::mat4 resizeMatrix;

	Arrow(const Game* game, Point arrowStartPoint, Point arrowEndPoint, int lineWidth = 10)
	{
		compileProgram();
		glUseProgram(m_program);

		//glActiveTexture(GL_TEXTURE0 + 1);
		//GLint uniform = glGetUniformLocation(m_program, "tex");
		//// Sets the sampler to sample from texture unit 1
		//glUniform1i(uniform, 1);

		glGenVertexArrays(1, &m_vertexArrayObject);
		glBindVertexArray(m_vertexArrayObject);

		GLuint buf;
		glGenBuffers(1, &buf);
		glBindBuffer(GL_ARRAY_BUFFER, buf);

		const Vector rotationVector = { arrowEndPoint.x - arrowStartPoint.x, arrowEndPoint.y - arrowStartPoint.y };
		const float length = glm::sqrt(rotationVector.x * rotationVector.x + rotationVector.y * rotationVector.y);
		
		const float diagonal = (float)glm::sqrt(2 * lineWidth * lineWidth);

		/*
		 *                                    l1------------l2
		 *                                       \          \
		 *                                        \          \
		 *                                       m1\          \
		 *              s1--------------------------\          \
		 *                |          /\              \ diagonal \
		 * arrowStartPoint|          || lineWidth   m3⟩ <------> ⟩ arrowEndPoint
		 *                |          \/              /          /
		 *              s2--------------------------/          /
		 *                                       m2/          /
		 *                                        /          /
		 *                                       /          /
		 *                                    r1------------r2
		 */

		// Relative to arrowStartPoint:
		Point s1 = rotatePointWithVector({ 0, lineWidth / 2.0f },                                 rotationVector, length);
		Point s2 = rotatePointWithVector({ 0, -lineWidth / 2.0f },                                rotationVector, length);
		
		// Relative to arrowEndPoint:
		Point m1 = rotatePointWithVector({ -lineWidth / 2.0f - diagonal + 1, lineWidth / 2.0f },  rotationVector, length);
		Point m2 = rotatePointWithVector({ -lineWidth / 2.0f - diagonal + 1, -lineWidth / 2.0f }, rotationVector, length);
		Point m3 = rotatePointWithVector({ -diagonal, 0 },                                        rotationVector, length);
		//                                     + 1 pixel is apparently needed to make the lines look perfectly straight:
		Point l1 = rotatePointWithVector({ -20 - diagonal + 1, 20 },                              rotationVector, length);
		Point r1 = rotatePointWithVector({ -20 - diagonal + 1, -20 },                             rotationVector, length);
		Point l2 = rotatePointWithVector({ -20 + 1, 20 },                                         rotationVector, length);
		Point r2 = rotatePointWithVector({ -20 + 1, -20 },                                        rotationVector, length);

		s1 = { arrowStartPoint.x + s1.x, arrowStartPoint.y + s1.y };
		s2 = { arrowStartPoint.x + s2.x, arrowStartPoint.y + s2.y };
		m1 = { arrowEndPoint.x + m1.x, arrowEndPoint.y + m1.y };
		m2 = { arrowEndPoint.x + m2.x, arrowEndPoint.y + m2.y };
		m3 = { arrowEndPoint.x + m3.x, arrowEndPoint.y + m3.y };
		l1 = { arrowEndPoint.x + l1.x, arrowEndPoint.y + l1.y };
		r1 = { arrowEndPoint.x + r1.x, arrowEndPoint.y + r1.y };
		r2 = { arrowEndPoint.x + r2.x, arrowEndPoint.y + r2.y };
		l2 = { arrowEndPoint.x + l2.x, arrowEndPoint.y + l2.y };

		// TODO: the arrows have curvature proportional to how far away from the center of the window they are
		GLfloat vertexData[] =
		{
			// Shaft, left half:
			arrowStartPoint.x, arrowStartPoint.y,
			s1.x, s1.y,
			m1.x, m1.y,
			m3.x, m3.y,
			// Shaft, right half:
			arrowStartPoint.x, arrowStartPoint.y,
			s2.x, s2.y,
			m2.x, m2.y,
			m3.x, m3.y,

			// Head, left half:
			arrowEndPoint.x, arrowEndPoint.y,
			m3.x, m3.y,
			l1.x, l1.y,
			l2.x, l2.y,
			// Head, right half:
			arrowEndPoint.x, arrowEndPoint.y,
			m3.x, m3.y,
			r1.x, r1.y,
			r2.x, r2.y
		};
		for (int i = 0; i < sizeof(vertexData) / sizeof(GLfloat); i += 2)
		{
			vertexData[i] = pixelCoordsToWindowCoords_x(vertexData[i], game);
			vertexData[i + 1] = pixelCoordsToWindowCoords_y(vertexData[i + 1], game);
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);

		resizeMatrix = glm::mat4(1.0f);
		resizeUniformIndex = glGetUniformLocation(m_program, "resize");
		glUniformMatrix4fv(resizeUniformIndex, 1, GL_FALSE, glm::value_ptr(resizeMatrix));

		//glEnable(GL_MULTISAMPLE);
	}

	void frameUpdate(const Game* game)
	{
		glUseProgram(m_program);

		//glActiveTexture(GL_TEXTURE0 + 1);
		//glBindTexture(GL_TEXTURE_2D, m_textureObject);

		glBindVertexArray(m_vertexArrayObject);

		/*
		pixelPos = Xp, windowPos = Xw, windowWidth = width

		Xp = (Xw + 1)/2 * width

		On window resize:
		pixelPosBefore/After = Xp0/1, windowPosBefore/After = Xw0/1, windowWidthBefore/After = width0/1

		Xp0 = Xp1
		(Xw0 + 1)/2 * width0 = (Xw1 + 1)/2 * width1
		(Xw0 + 1) * width0/width1 = (Xw1 + 1)
		Xw1 = (Xw0 + 1) * width0/width1 - 1
		Xw1 = Xw0 * (width0/width1) + (width0/width1 - 1)
		*/

		// TODO: Make resizeMatrix available from Game

		float widthRatio = (float)Game::INITIAL_WINDOW_WIDTH / game->getWindowWidth();
		float heightRatio = (float)Game::INITIAL_WINDOW_HEIGHT / game->getWindowHeight();

		resizeMatrix = glm::translate(glm::mat4(1.0f), { widthRatio - 1, heightRatio - 1, 0.0f });
		resizeMatrix = glm::scale(resizeMatrix,        { widthRatio,     heightRatio,     1.0f });

		// TODO: Set this uniform on window resize instead
		glUniformMatrix4fv(resizeUniformIndex, 1, GL_FALSE, glm::value_ptr(resizeMatrix));

		constexpr GLint firsts[] = { 0, 4, 8, 12 };
		constexpr GLint counts[] = { 4, 4, 4, 4 };
		glMultiDrawArrays(GL_TRIANGLE_FAN, firsts, counts, 4);
	}

	// TODO: pixelCoordsToWindowCoords_x vs pixelsToWindowCoord_Width_
	GLfloat pixelCoordsToWindowCoords_x(GLfloat pixels, const Game* game)
	{
		return 2 * pixels / game->getWindowWidth() - 1;
	}

	GLfloat pixelCoordsToWindowCoords_y(GLfloat pixels, const Game* game)
	{
		return 2 * pixels / game->getWindowHeight() - 1;
	}
};
