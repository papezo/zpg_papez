#include "Transformation.h"

auto Transformation::setPosition(float x, float y, float z) -> void
{
	posX = x;
	posY = y;
	posZ = z;
}

auto Transformation::setAngle(float r) -> void
{
	angle = r;
}

auto Transformation::setScale(float s) -> void
{
	scale = s;
}

auto Transformation::move(float dx, float dy, float dz) -> void
{
	posX += dx;
	posY += dy;
	posZ += dz;
}	

auto Transformation::rotate(float dAngle) -> void
{
	angle += dAngle;
}

auto Transformation::apply(ShaderProgram& shader) -> void
{
	shader.setUniform("uTranslation", posX, posY, posZ);
	shader.setUniform("uScale", scale, scale, scale);
	shader.setUniform("uAngle", angle);
}