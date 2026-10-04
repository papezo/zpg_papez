#pragma once

#include <memory>
#include "Graphics/ShaderProgram.h"

class Transformation
{
public:
	Transformation() = default; // Default constructor

	auto setPosition(float x, float y, float z) -> void;
	auto setAngle(float radians) -> void;
	auto setScale(float scale) -> void;

	auto move(float dx, float dy, float dz) -> void;
	auto rotate(float dAngle) -> void;

	auto apply(ShaderProgram& shader) -> void; // Apply the transformation to the shader

private:
	float posX = 0.0f, posY = 0.0f, posZ = 0.0f;	float angle = 0.0f; // radians
	float scale = 0.5f;

};