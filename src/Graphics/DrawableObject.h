#pragma once
#include <memory>
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject
{
public:
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram = nullptr)
		: model(std::move(model)), shader(std::move(shaderProgram)) {
	};

	auto setTransformation(std::shared_ptr<Transformation> t) -> void;
	auto draw() -> void;

private:
	std::shared_ptr<Model> model;
	std::shared_ptr<ShaderProgram> shader;
	std::shared_ptr<Transformation> transformation;

};