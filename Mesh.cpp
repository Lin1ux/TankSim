#include "Mesh.h"

void Mesh::InitVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndicies)
{
	this->nrOfVertices = nrOfVertices;
	this->nrOfIndices = nrOfIndicies;

	//£adowanie do karty graficznej
	glCreateVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	//Buffor Vertexów
	//VBO
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW - jeœli zmieniane s¹ dane

	//Buffor elementów
	//EBO
	if (this->nrOfIndices > 0)
	{
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
	}
	//Format Zapisywania Vertexów

	//GLuint attribLoc = glGetAttribLocation(coreProgram,"vertex_position");
	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//texCord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcord));
	glEnableVertexAttribArray(2);
	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	//Bind VAO
	glBindVertexArray(0);
}

void Mesh::InitVAO(Primitive* primitive)
{
	this->nrOfVertices = primitive->getNrOfVertices();
	this->nrOfIndices = primitive->getNrOfIndices();

	//£adowanie do karty graficznej
	glCreateVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	//Buffor Vertexów
	//VBO
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW); //GL_DYNAMIC_DRAW - jeœli zmieniane s¹ dane

	//Buffor elementów
	//EBO
	if (this->nrOfIndices > 0)
	{
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW);
	}
	//Format Zapisywania Vertexów

	//GLuint attribLoc = glGetAttribLocation(coreProgram,"vertex_position");
	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//texCord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcord));
	glEnableVertexAttribArray(2);
	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	//Bind VAO
	glBindVertexArray(0);
}

void Mesh::UpdateUniforms(shader* shader)
{
	shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
}

void Mesh::UpdateModelMatrix()
{
	this->ModelMatrix = glm::mat4(1.0f);
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

Mesh::Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndicies, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

	std::cout << "MESH\n";

	this->InitVAO(vertexArray, nrOfVertices, indexArray, nrOfIndicies);
	std::cout << "MATRIX\n";

	this->UpdateModelMatrix();
	
	std::cout << "DONE\n";
}

Mesh::Mesh(Primitive* primitive, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

	std::cout << "MESH\n";

	this->InitVAO(primitive);
	std::cout << "MATRIX\n";

	this->UpdateModelMatrix();

	std::cout << "DONE\n";
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);

	if (this->nrOfIndices > 0)
	{
		glDeleteBuffers(1, &this->EBO);
	}
}

void Mesh::SetPosition(const glm::vec3 position)
{
	this->position = position;
}

void Mesh::SetRotation(const glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Mesh::SetScale(const glm::vec3 scale)
{
	this->scale = scale;
}

void Mesh::Move(const glm::vec3 position)
{
	this->position += position;
}

void Mesh::Rotate(const glm::vec3 rotation)
{
	this->rotation += rotation;
}

void Mesh::Scale(const glm::vec3 scale)
{
	this->scale += scale;
}

void Mesh::update()
{

}

void Mesh::render(shader* shader)
{
	//Update Uniforms
	UpdateModelMatrix();
	
	this->UpdateUniforms(shader);
	shader->use();

	//Bind VAO
	glBindVertexArray(this->VAO);

	//Render
	if (this->nrOfIndices == 0)
	{
		glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
	}
}
