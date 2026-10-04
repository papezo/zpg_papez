#include "src/Graphics/Model.h"


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

auto Model::draw() -> void
{
	glBindVertexArray(VAO);
	// Draw a triangles
	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //mode,first,count
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