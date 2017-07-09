#include "GLSLshaders.h"

#include <vector>
#include <regex>
#include <iostream>

#include "../util.h"
#include "gl.h"

struct Shader
{
	int type;
	std::string source;
};

std::vector<Shader*> parseShaders(const std::string& filePath);

int glsl::loadShaders(const char filePath[])
{
	std::vector<Shader*> shaders = parseShaders(filePath);

	GLuint program = glCreateProgram();

	for (Shader* shader : shaders)
	{
		GLuint shaderObject = glCreateShader(shader->type);

		const char* source = shader->source.c_str();
		glShaderSource(shaderObject, 1, &source, NULL);
		glCompileShader(shaderObject);

		GLint compiled;
		glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLsizei logLength;
			glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &logLength);

			GLchar* log = new GLchar[logLength + 1];
			glGetShaderInfoLog(shaderObject, logLength, &logLength, log);
			std::cerr << log << std::endl;
			delete[] log;
		}

		glAttachShader(program, shaderObject);

		delete shader;
	}

	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLsizei logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		GLchar* log = new GLchar[logLength + 1];
		glGetProgramInfoLog(program, logLength, &logLength, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

	return program;
}

Shader* parseShaderTypeDeclaration(std::string& shaderTypeDeclaration);

std::vector<Shader*> parseShaders(const std::string& filePath)
{
	const std::string* source = util::readFile(filePath);

	std::vector<Shader*> shaders;

	size_t shaderTypeIndex = source->find("/***");
	if (shaderTypeIndex == std::string::npos)
	{
		std::cerr << util::getLinkToCharInFile(filePath, *source, 0) << ": Could not find any shader type declarations." << std::endl;
		delete source;
		return shaders;
	}

	do
	{
		size_t endIndex = source->find("*/", shaderTypeIndex + 4); // 4 is the length of the /*** token
		if (endIndex == std::string::npos)
		{
			std::cerr << util::getLinkToCharInFile(filePath, *source, shaderTypeIndex) << ": Missing comment end token */ for the shader type declaration." << std::endl;
			break;
		}

		std::string shaderTypeDeclaration = source->substr(shaderTypeIndex + 4, endIndex - (shaderTypeIndex + 4)); // 4 is the length of the /*** token

		Shader* shader = parseShaderTypeDeclaration(shaderTypeDeclaration);
		if (shader == nullptr)
		{
			std::cerr << util::getLinkToCharInFile(filePath, *source, shaderTypeIndex) << ": Could not find a valid shader type in the shader type declaration." << std::endl;
			break;
		}

		size_t nextShaderTypeIndex = source->find("/***", shaderTypeIndex + 4); // 4 is the length of the /*** token
		if (nextShaderTypeIndex != std::string::npos)
			shader->source = source->substr(endIndex + 2, nextShaderTypeIndex - (endIndex + 2));  // 2 is the length of the */ token
		else
			shader->source = source->substr(endIndex + 2); // 2 is the length of the */ token

		shaders.push_back(shader);

		shaderTypeIndex = nextShaderTypeIndex;
	} while (shaderTypeIndex != std::string::npos);

	delete source;

	return shaders;
}

Shader* parseShaderTypeDeclaration(std::string& shaderTypeDeclaration)
{
	Shader* shader = nullptr;

	const std::regex separators("[^a-zA-Z]");
	std::regex_token_iterator<std::string::iterator> tokenIterator(shaderTypeDeclaration.begin(), shaderTypeDeclaration.end(), separators, -1);
	std::regex_token_iterator<std::string::iterator> tokenIterator_end;

	while (tokenIterator != tokenIterator_end)
	{
		if (tokenIterator->str().length() < 4)
		{
			tokenIterator++;
			continue;
		}

		std::string token = util::toLowerCase(tokenIterator->str().substr(0, 4));

		if (token == "vert")
		{
			shader = new Shader{ GL_VERTEX_SHADER };
			break;
		} else if (token == "frag")
		{
			shader = new Shader{ GL_FRAGMENT_SHADER };
			break;
		} else if (token == "geom")
		{
			shader = new Shader{ GL_GEOMETRY_SHADER };
			break;
		} else if (token == "tess")
		{
			if (++tokenIterator != tokenIterator_end)
				token += util::toLowerCase(tokenIterator->str());

			if (token.find("cont") != std::string::npos)
			{
				shader = new Shader{ GL_TESS_CONTROL_SHADER };
				break;
			} else if (token.find("eval") != std::string::npos)
			{
				shader = new Shader{ GL_TESS_EVALUATION_SHADER };
				break;
			}

			continue; // because tokenIterator has already been incremented
		}

		tokenIterator++;
	}

	return shader;
}
