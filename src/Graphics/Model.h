#pragma once

#include <glad/gl.h>

class Model
{
public:
	Model(const float* model, size_t floatCount, int floatsPerVertex = 6);
	 ~Model();

	 auto draw() const -> void;

private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	int floatsPerVertex = 6;

};