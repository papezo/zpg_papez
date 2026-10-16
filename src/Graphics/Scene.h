#pragma once
#include <vector>
#include <memory>
#include "src/Graphics/Model.h"
#include <Graphics/ShaderProgram.h>
#include "DrawableObject.h"
#include "Camera.h"


class Scene
{
public:
    Scene() = default;

    auto addObject(std::unique_ptr<DrawableObject> object) -> void;
    auto render(const Camera& camera) const -> void;

private:
    std::vector<std::unique_ptr<DrawableObject>> objects;
};