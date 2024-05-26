#pragma once

#include<iostream>
#include<vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Vertex.h"
#include"Shader.h"
#include"Texture.h"
#include"Material.h"
#include"Primitive.h"


class Mesh
{
private:
	//std::vector<Vertex> vertices;
	//std::vector<GLuint> indices;
	Vertex* vertexArray;

	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 ModelMatrix;

	bool CanUpdate;

	//void InitVAO(Vertex* vertexArray,
	//	const unsigned& nrOfVertices,
	//	GLuint* indexArray,
	//	const unsigned& nrOfIndicies);
	
	void InitVAO();


	void UpdateUniforms(shader* shader);
	void UpdateModelMatrix();


public:
	Mesh(
		Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndicies,

		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 origin = glm::vec3(0.0f),
		glm::vec3 rotation = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f));

	Mesh(
		Primitive* primitive,

		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 origin = glm::vec3(0.0f),
		glm::vec3 rotation = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f));

	Mesh(const Mesh& obj);

	~Mesh();


	//Metody ustawiania
	void SetModelMatrix(glm::mat4 newMatrix, bool canUpdate);
	void SetPosition(const glm::vec3 position);
	void SetOrigin(const glm::vec3 origin);
	void SetRotation(const glm::vec3 rotation);
	void SetScale(const glm::vec3 scale);
	//Metody aktualizuj¹ce
	void Move(const glm::vec3 position);
	void Rotate(const glm::vec3 rotation);
	void Scale(const glm::vec3 scale);
	void SetColor(glm::vec3 color);

	glm::mat4 GetMatrix();

	void update();
	void render(shader* shader);/*(Shader* shader )*/;
};

