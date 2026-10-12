#include "DrawableObject.h"

auto DrawableObject::draw() -> void
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
	shader->setUniform("modelMatrix", M);
	this->model->draw();
}


auto DrawableObject::setTransformation(std::shared_ptr<Transformation> t) -> void
{
	this->transformation = std::move(t);
}
