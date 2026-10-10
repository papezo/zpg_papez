#include "ShaderProgram.h"
#include "Transformation.h"

#include "../../libs/glm/glm/glm.hpp"
#include "../../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../../libs/glm/glm/gtc/type_ptr.hpp"

#include <GLFW/glfw3.h>

auto Transformation::applyUniforms(ShaderProgram& shader) -> void {
	glm::mat4 M = this->getMatrix();
	shader.setUniform("modelMatrix", M);
	shader.setUniform("fragmentColor", this->colorR, this->colorG, this->colorB);
}

auto Transformation::setScale(float s) -> void
{
	this->scale = s;
}

auto Transformation::setPosition(float x, float y, float z) -> void
{
	this->posX = x;
	this->posY = y;
	this->posZ = z;
}

auto Transformation::setAngle(float a) -> void
{
	this->angle = a;
}

auto Transformation::setColor(float r, float g, float b) -> void
{
	this->colorR = r;
	this->colorG = g;
	this->colorB = b;

}

auto Transformation::getMatrix() const -> glm::mat4
{
	glm::mat4 M = glm::mat4(1.0f); // construct identity matrix

	M = glm::translate(M, glm::vec3(this->posX, this->posY, this->posZ));
	M = glm::rotate(M, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(this->scale));

	return M;
}