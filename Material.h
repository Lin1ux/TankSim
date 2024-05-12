#pragma once

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffuseTex;
	GLint specularTex;

public:
	//Konstruktor
	Material(glm::vec3 ambient, glm::vec3 diffuse,glm::vec3 specular,GLint diffuseTex,GLint specularTex);
	~Material();
	void sendToShader(shader& program);
};

