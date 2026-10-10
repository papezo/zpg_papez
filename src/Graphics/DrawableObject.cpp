#include "DrawableObject.h"

auto DrawableObject::draw() -> void
{
	if (!this->shader || !this->model)
	{
		return;
	}
	this->shader->use();
	this->transformation.applyUniforms(*this->shader);
	this->model->draw();
}

auto DrawableObject::setShader(std::shared_ptr<ShaderProgram> shaderProgram) -> void
{
	this->shader = std::move(shaderProgram);
}