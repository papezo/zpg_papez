#include "Scene.h"
#include <Graphics/ShaderProgram.h>

auto Scene::addObject(std::unique_ptr<DrawableObject> object) -> void
{
    this->objects.push_back(std::move(object));
}

auto Scene::render() const -> void
{
    for (const auto& model : objects)
    {
        model->draw();
    }
}
