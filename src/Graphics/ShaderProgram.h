#pragma once
#include <glad/gl.h>
#include <string>

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	~ShaderProgram();
	auto use() -> void;

	auto setUniform(const std::string& name, float value) -> void;
	auto setUniform(const std::string& name, float x, float y, float z) -> void;
private:
	GLuint id;
	auto createShaderFromFile(GLenum shaderType, const char* shaderFile) -> GLuint;

};