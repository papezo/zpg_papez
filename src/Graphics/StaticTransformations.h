#pragma once
#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>



class Translate : public Transformation
{
public:
	Translate(const glm::vec3& t) : translation(t) {}
	Translate(float x, float y, float z) : translation(x, y, z) {}

	auto getModelMatrix() -> glm::mat4 override {
		return glm::translate(glm::mat4(1.0f), translation);
	}

private:
	glm::vec3 translation;
};


class Scale : public Transformation
{
public:
	Scale(float s) : scale(s) {}
	Scale(const glm::vec3& s) : scale(s) {}

	auto getModelMatrix() -> glm::mat4 override {
		return glm::scale(glm::mat4(1.0f), scale);
	}

private:
	glm::vec3 scale;
};


class Rotate : public Transformation
{
public:
	Rotate(float angleDeg, const glm::vec3& axis) : angle(angleDeg), axis(axis) {}

	auto getModelMatrix() -> glm::mat4 override {
		return glm::rotate(glm::mat4(1.0f), angle, axis);
	}
protected:
	glm::vec3 axis;
	float angle;
};