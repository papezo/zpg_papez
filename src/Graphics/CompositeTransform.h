#pragma once
#include "Transformation.h"
#include <vector>
#include <memory>


class CompositeTransform : public Transformation
{
public:
	void add(std::shared_ptr<Transformation> t) {
		transformations.push_back(t);
	}

	glm::mat4 getModelMatrix() override {
		glm::mat4 result = glm::mat4(1.0f);
		for (const auto& t : transformations) {
			result = result * t->getModelMatrix();
		}
		return result;
	}

private:
	std::vector<std::shared_ptr<Transformation>> transformations;

};