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

    auto getModelMatrix() -> glm::mat4 override {
        glm::mat4 result(1.0f);

        for (const auto& t : transformations) {
            result = result * t->getModelMatrix();
        }

        return result;
    }

private:
	std::vector<std::shared_ptr<Transformation>> transformations;

};