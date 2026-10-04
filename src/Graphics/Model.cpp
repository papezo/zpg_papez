#include "src/Graphics/Model.h"
#include "ShaderProgram.h"


Model::Model(const float* model, size_t floatCount)
{
	vertexCount = floatCount / 6; // 6 floats per vertex (3 for position, 3 for normal)

	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, floatCount * sizeof(float), model, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// index, number of components, data type, normalized, vertex stride, offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

auto Model::draw(ShaderProgram& shader) -> void
{
	shader.setUniform("uTranslation", this->posX, this->posY, this->posZ);
	shader.setUniform("uScale", this->scale, this->scale, this->scale);
	shader.setUniform("uAngle", this->angle);
	shader.setUniform("fragmentColor", this->colorR, this->colorG, this->colorB);

	glBindVertexArray(this->VAO);
	// Draw a triangles
	glDrawArrays(GL_TRIANGLES, 0, this->vertexCount); //mode,first,count
	glBindVertexArray(0);
}

auto Model::setScale(float s) -> void
{
	this->scale = s;
}

auto Model::setPosition(float x, float y, float z) -> void
{
	this->posX = x;
	this->posY = y;
	this->posZ = z;
}

auto Model::setAngle(float a) -> void
{
	this->angle = a;
}

auto Model::setColor(float r, float g, float b) -> void
{
	this->colorR = r;	
	this->colorG = g;
	this->colorB = b;
	
}

Model::~Model()
{
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
	}
	
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
	}
}