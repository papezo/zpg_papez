#pragma once

#include<vector>
#include <memory>
#include "src/Graphics/Model.h"
#include <Graphics/ShaderProgram.h>

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	auto addModel(std::unique_ptr<Model> model) -> void; // Add model to the scene
	auto render(ShaderProgram& shader) -> void; // Render all models in the scene
	auto getModel(int index) -> Model*; // To get a model from the scene by index for control

private:
	std::vector<std::unique_ptr<Model>> models; // vector that holds models


};