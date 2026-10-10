#include "Model.h"


Model::Model(const float* model, size_t floatCount, int floatsPerVertex) : floatsPerVertex(floatsPerVertex)
{
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
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	// if model has normals load also normals on attribute 2
	if (floatsPerVertex >= 9)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	}
}

auto Model::draw() const -> void
{
	// just to get the number of vertices in the buffer 
	// we can query the buffer size and divide by the size of a single vertex
	GLint buffSize = 0;
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffSize);

	GLsizei count = buffSize / (sizeof(float) * this->floatsPerVertex); 
	glBindVertexArray(this->VAO);
	// Draw a triangles
	glDrawArrays(GL_TRIANGLES, 0, count); //mode,first,count
	glBindVertexArray(0);
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