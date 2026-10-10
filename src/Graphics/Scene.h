#pragma once
#include <vector>
#include <memory>
#include "src/Graphics/Model.h"
#include <Graphics/ShaderProgram.h>
#include "DrawableObject.h"


class Scene
{
public:
    Scene() = default;

    auto addObject(std::unique_ptr<DrawableObject> object) -> void;
    auto render() const -> void;

private:
    std::vector<std::unique_ptr<DrawableObject>> objects;
};