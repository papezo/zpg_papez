#pragma once

#include <glad/gl.h>
#include "ShaderProgram.h"

class Model
{
public:
	Model(const float* model, size_t floatCount);
	 ~Model();

	auto draw(ShaderProgram& shader) -> void;

	auto setScale(float s) -> void;
	auto setPosition(float x, float y, float z) -> void;
	auto setAngle(float a) -> void;
	auto setColor(float r, float g, float b) -> void;
private:
	GLsizei vertexCount = 0;
	GLuint VAO = 0;
	GLuint VBO = 0;

	float posX = 0.0f, posY = 0.0f, posZ = 0.0f;
	float scale = 1.0f;
	float angle = 0.0f; // in rads
	float colorR = 1.0f, colorG = 1.0f, colorB = 1.0f;

};