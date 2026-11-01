//
// Created by Ondřej Papež on 30.10.2026.
//

#include "Light.h"

auto Light::applyLight(const ShaderProgram& shader)  const -> void {
    shader.use();

    shader.setUniform("lightPosition", lightPos.x, lightPos.y, lightPos.z);
    shader.setUniform("lightColor", lightColor.x, lightColor.y, lightColor.z);

    shader.setUniform("attenuationConstant", constant);
    shader.setUniform("attenuationLinear", linear);
    shader.setUniform("attenuationQuadratic", quadratic);

}
