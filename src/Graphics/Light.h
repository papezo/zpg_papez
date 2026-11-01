//
// Created by Ondřej Papež on 30.10.2026.
//

#pragma once
#include "ShaderProgram.h"
#include "glm/vec3.hpp"


class Light {
public:
    Light(glm::vec3 pos, glm::vec3 color, float c, float l, float q) : lightPos(pos), lightColor(color), constant(c), linear(l), quadratic(q) {}
    auto applyLight(const ShaderProgram& shader) const -> void;

private:
    glm::vec3 lightPos { 0.0f, 0.0f, 0.0f };
    glm::vec3 lightColor { 0.0f, 0.0f, 0.0f };

    float constant { 1.0f };
    float linear { 0.0f };
    float quadratic { 0.0f };

};
