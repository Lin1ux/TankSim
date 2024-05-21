#include "Piramid.h"
#include "Primitive.h"

Piramid::Piramid() : Primitive()
{
	Vertex vertices[] =
	{
		//Position							//Color								//TexCord					//Normals
		glm::vec3(0.0f,0.5f,0.0f),			glm::vec3(1.0f,0.0f,0.0f),			glm::vec2(0.5f,1.0f),		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(-0.5f,-0.5f,0.5f),		glm::vec3(0.0f,1.0f,0.0f),			glm::vec2(0.0f,0.0f),		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(0.5f,-0.5f,0.5f),			glm::vec3(0.0f,0.0f,1.0f),			glm::vec2(1.0f,0.0f),		glm::vec3(0.0f,0.0f,1.0f),

		//Position							//Color								//TexCord					//Normals
		glm::vec3(0.0f,0.5f,0.0f),			glm::vec3(1.0f,1.0f,0.0f),			glm::vec2(0.5f,1.0f),		glm::vec3(-1.0f,0.0f,0.0f),
		glm::vec3(-0.5f,-0.5f,-0.5f),		glm::vec3(0.0f,1.0f,1.0f),			glm::vec2(0.0f,0.0f),		glm::vec3(-1.0f,0.0f,0.0f),
		glm::vec3(-0.5f,-0.5f,0.5f),		glm::vec3(0.0f,0.0f,1.0f),			glm::vec2(1.0f,0.0f),		glm::vec3(-1.0f,0.0f,0.0f),

		//Position							//Color								//TexCord					//Normals
		glm::vec3(0.0f,0.5f,0.0f),			glm::vec3(1.0f,1.0f,0.0f),			glm::vec2(0.5f,1.0f),		glm::vec3(0.0f,0.0f,-1.0f),
		glm::vec3(0.5f,-0.5f,-0.5f),		glm::vec3(0.0f,0.0f,1.0f),			glm::vec2(0.0f,0.0f),		glm::vec3(0.0f,0.0f,-1.0f),
		glm::vec3(-0.5f,-0.5f,-0.5f),		glm::vec3(0.0f,0.0f,1.0f),			glm::vec2(1.0f,0.0f),		glm::vec3(0.0f,0.0f,-1.0f),
	
		//Position							//Color								//TexCord					//Normals
		glm::vec3(0.0f,0.5f,0.0f),			glm::vec3(1.0f,1.0f,0.0f),			glm::vec2(0.5f,1.0f),		glm::vec3(1.0f,0.0f,0.0f),
		glm::vec3(0.5f,-0.5f,0.5f),			glm::vec3(0.0f,0.0f,1.0f),			glm::vec2(0.0f,0.0f),		glm::vec3(1.0f,0.0f,0.0f),
		glm::vec3(0.5f,-0.5f,-0.5f),		glm::vec3(0.0f,0.0f,1.0f),			glm::vec2(1.0f,0.0f),		glm::vec3(1.0f,0.0f,0.0f)

	};
	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);	//Liczba vertices

	this->set(vertices, nrOfVertices, nullptr, 0);

}
