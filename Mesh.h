#pragma once

#include<iostream>
#include<vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Vertex.h"


//TO DO
//#include"Shader.h"
//#include"Texture.h"
//#include"Material.h"


class Mesh
{
private:
	//std::vector<Vertex> vertices;
	//std::vector<GLuint> indices;
	unsigned nrOfVertices;
	unsigned nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 ModelMatrix;

	void InitVAO(Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndicies)
	{
		this->nrOfVertices = nrOfVertices;
		this->nrOfIndices = nrOfIndicies;

		//Init VAO
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(VAO);

		//Vertex buffer object
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

		//Gen EBO
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(Vertex), indexArray, GL_STATIC_DRAW);
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//Tex Cord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcord));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	void initModelMatrix()
	{
		this->ModelMatrix = glm::mat4(1.0f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
	}

	void UpdateUniforms(/*Shaders* shader*/)
	{
		//shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}
	void UpdateModelMatrix()
	{
		this->ModelMatrix = glm::mat4(1.0f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
	}

public:
	Mesh(
		Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndicies,

		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 rotation = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f))
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
	~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}
	//Set Methods
	void SetPosition(const glm::vec3 position)
	{
		this->position = position;
	}

	void SetRotation(const glm::vec3 rotation)
	{
		this->rotation = rotation;
	}
	void SetScale (const glm::vec3 scale)
	{
		this->scale = scale;
	}
	//Change Methods
	void Move(const glm::vec3 position)
	{
		this->position += position;
	}

	void Rotate(const glm::vec3 rotation)
	{
		this->rotation += rotation;
	}

	void Scale(const glm::vec3 scale)
	{
		this->scale += scale;
	}

	void update();
	void render()/*(Shader* shader )*/
	{
		//Update Uniforms
		UpdateModelMatrix();
		//this->UpdateUniforms(/*shader)

		//shader->use();

		//Bind VAO
		glBindVertexArray(this->VAO);

		//Render
		glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);

	}
};

