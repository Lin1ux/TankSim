#include "Quads.h"
#include "Primitive.h"

Quad::Quad() : Primitive()
{
	Vertex vertices[] =
	{
		//Position							//Color								//TexCord					//Normals
		glm::vec3(-0.5f,0.5f,0.0f),			glm::vec3(1.0f,0.0f,0.0f),			glm::vec2(0.0f,1.0f),		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(-0.5f,-0.5f,0.0f),		glm::vec3(0.0f,1.0f,0.0f),			glm::vec2(0.0f,0.0f),		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(0.5f,-0.5f,0.0f),			glm::vec3(0.0f,0.0f,1.0f),			glm::vec2(1.0f,0.0f),		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(0.5f,0.5f,0.0f),			glm::vec3(1.0f,1.0f,0.0f),			glm::vec2(1.0f,1.0f),		glm::vec3(0.0f,0.0f,1.0f)
	};
	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);	//Liczba vertices

	GLuint indices[] =
	{
		0, 1, 2,	//1 Trójk¹t
		0, 2, 3		//2 Trójk¹t
	};
	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, nrOfVertices, indices, nrOfIndices);

}

bool Quad::operator==(const Quad& other) const
{
	return false;
}
