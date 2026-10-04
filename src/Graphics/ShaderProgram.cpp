#include "src/Graphics/ShaderProgram.h"

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iterator>
#include <iostream>



auto ShaderProgram::use() -> void
{
	glUseProgram(this->id);
}

auto ShaderProgram::setUniform(const std::string& name, float value) -> void
{
	GLint location = glGetUniformLocation(this->id, name.c_str());
	if (location == -1) {
		std::cout << "Uniform '" << name << "' not found in shader program";
		return;
	}
	glUniform1f(location, value);
}

auto ShaderProgram::setUniform(const std::string& name, float x, float y, float z) -> void
{
	GLint location = glGetUniformLocation(this->id, name.c_str());
	if (location == -1) {
		std::cout << "Uniform " << name << " not found in shader program";
		return;
	}
	glUniform3f(location, x, y, z);
}
ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, vertexFile);
	GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, fragmentFile);

	this->id = glCreateProgram();
	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);
	glLinkProgram(this->id);

	GLint success;
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);

	if (!success) {
		char infoLog[1024];
		glGetProgramInfoLog(this->id, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "Shader Linking Error:\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint ShaderProgram::createShaderFromFile(GLenum shaderType, const char* shaderFile) {
	GLuint shaderID = glCreateShader(shaderType);
	if (shaderID == 0) {
		std::cout << "Unable to create shader" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::ifstream file(shaderFile);
	if (!file.is_open()) {
		std::cout << "Unable to open file " << shaderFile << std::endl;
		glDeleteShader(shaderID);
		exit(-1);
	}

	std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	const char* source = shaderCode.c_str();

	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[1024];
		glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
		std::cout << "Shader compilation failed (" << shaderFile << "):\n" << infoLog << std::endl;
		glDeleteShader(shaderID);
		exit(1);
	}
	return shaderID;
}


ShaderProgram::~ShaderProgram()
{
	if (this->id != 0)
	{
		glDeleteProgram(this->id);
	}
	
}