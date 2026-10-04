#pragma once

#include <glad/gl.h>

class Model
{
public:
	Model(const float* model, size_t floatCount);
	 ~Model();

	auto draw(ShaderProgram& shader) -> void;
private:
	GLsizei vertexCount = 0;
	GLuint VAO = 0;
	GLuint VBO = 0;

};