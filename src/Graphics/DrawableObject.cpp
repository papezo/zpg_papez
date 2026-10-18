#include "DrawableObject.h"
#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

auto DrawableObject::draw(const Camera& camera) -> void
{
    if (!this->shader || !this->model)
    {
        return;
    }

    this->shader->use();

    glm::mat4 M = glm::mat4(1.0f);

    if (transformation) {
        M = transformation->getModelMatrix();
    }

    float t = static_cast<float>(glfwGetTime() * 5); // multiplying with 5 to speed it up little bit

    hourMatrix = glm::rotate(glm::mat4(1.0f), -t * (glm::two_pi<float>() / 43200.0f), glm::vec3(0, 0, 1));
    minuteMatrix = glm::rotate(glm::mat4(1.0f), -t * (glm::two_pi<float>() / 3600.0f), glm::vec3(0, 0, 1));
    secondMatrix = glm::rotate(glm::mat4(1.0f), -t * (glm::two_pi<float>() / 60.0f), glm::vec3(0, 0, 1));

    shader->setUniform("modelMatrix", M);
    shader->setUniform("projectionMatrix", camera.matrixProjection());

    shader->setUniform("hourMatrix", hourMatrix);
    shader->setUniform("minuteMatrix", minuteMatrix);
    shader->setUniform("secondMatrix", secondMatrix);

    this->model->draw();
}

auto DrawableObject::setTransformation(std::shared_ptr<Transformation> t) -> void
{
	this->transformation = std::move(t);
}
