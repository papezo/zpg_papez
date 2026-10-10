#pragma once
#include "StaticTransformations.h"

class DynamicRotate : public Rotate
{
public:
	DynamicRotate(float initialAngle, float stepPerFrame, const glm::vec3& axis)
		: Rotate(initialAngle, axis), step(stepPerFrame) { }

	glm::mat4 getModelMatrix() override{
		this->angle += this->step;

		return glm::rotate(glm::mat4(1.0f), glm::radians(this->angle), this->axis);
	}

private:
	float step;
};