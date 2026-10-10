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

	auto draw() -> void;
	auto setShader(std::shared_ptr<ShaderProgram> shaderProgram) -> void;
	Transformation transformation;

private:
	std::shared_ptr<Model> model;
	std::shared_ptr<ShaderProgram> shader;

};