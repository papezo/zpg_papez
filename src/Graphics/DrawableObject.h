#pragma once
#include <memory>
#include "Model.h"
#include "../Transformations/Transformation.h"
#include "ShaderProgram.h"
#include "../Camera/Camera.h"

#include <glm/glm.hpp>

class DrawableObject
{
public:
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram = nullptr)
		: model(std::move(model)), shader(std::move(shaderProgram)) {
	};

	auto setTransformation(std::shared_ptr<Transformation> t) -> void;
	auto draw(const Camera& camera) -> void;

private:
	std::shared_ptr<Model> model;
	std::shared_ptr<ShaderProgram> shader;
	std::shared_ptr<Transformation> transformation;
	std::shared_ptr<Camera> camera;

	glm::mat4 hourMatrix{ 1.0f };
	glm::mat4 minuteMatrix{ 1.0f };
	glm::mat4 secondMatrix{ 1.0f };

};