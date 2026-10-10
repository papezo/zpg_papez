#pragma once
#include "ShaderProgram.h"
#include "../../libs/glm/glm/glm.hpp"
#include "../../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../../libs/glm/glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>

class Transformation
{
public:
	auto draw(ShaderProgram& shader) -> void;

	auto setScale(float s) -> void;
	auto setPosition(float x, float y, float z) -> void;
	auto setAngle(float a) -> void;
	auto setColor(float r, float g, float b) -> void;

	auto applyUniforms(ShaderProgram& shader) -> void;
	auto getMatrix() const -> glm::mat4;

private:
	float posX = 0.0f, posY = 0.0f, posZ = 0.0f;
	float scale = 1.0f;
	float angle = 0.0f; // in rads
	float colorR = 1.0f, colorG = 1.0f, colorB = 1.0f;
};