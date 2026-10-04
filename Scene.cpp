#include "Scene.h"
#include <Graphics/ShaderProgram.h>


auto Scene::addModel(std::unique_ptr<Model> model) -> void
{
	this->models.push_back(std::move(model));
}

auto Scene::render(ShaderProgram& shader) -> void
{
	for (const auto& model : models)
	{
		model->draw(shader);
	}
}

auto Scene::getModel(int index) -> Model*
{
	if (index >= 0 && index < models.size())
	{
		return models[index].get();
	}

	return nullptr;
}