#pragma once
#include <glad/gl.h>
#include <string>
#include "../../libs/glm/glm/glm.hpp"
#include "../../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../../libs/glm/glm/gtc/type_ptr.hpp"

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	~ShaderProgram();

	auto use() const -> void;

	auto setUniform(const std::string& name, float value) -> void;
	auto setUniform(const std::string& name, float x, float y, float z) -> void;
	auto setUniform(const std::string& name, const glm::mat4& matrix) -> void;
private:
	GLuint id;
	auto createShaderFromFile(GLenum shaderType, const char* shaderFile) -> GLuint;

};