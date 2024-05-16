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
		const unsigned& nrOfIndicies);

	void UpdateUniforms(shader* shader);
	void UpdateModelMatrix();

public:
	Mesh(
		Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndicies,

		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 rotation = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f));

	~Mesh();
	//Metody ustawiania
	void SetPosition(const glm::vec3 position);
	void SetRotation(const glm::vec3 rotation);
	void SetScale(const glm::vec3 scale);
	//Metody aktualizuj¹ce
	void Move(const glm::vec3 position);
	void Rotate(const glm::vec3 rotation);
	void Scale(const glm::vec3 scale);

	void update();
	void render(shader* shader);/*(Shader* shader )*/;
};

