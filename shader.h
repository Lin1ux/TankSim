#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class shader
{
private:
	GLuint id;

	
	std::string loadShaderSource(char* fileName);
	GLuint loadShader(GLenum type, char* fileName);
	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);

public: 
	//Konstruktor
	shader(char* vertexFile, char* fragmentFile);
	//Dekonstruktor
	~shader();

	void use();
	void unuse();
	void set1i(GLint value, const GLchar* name);
	void setVec1f(GLfloat value, const GLchar* name);
	void setVec2f(glm::fvec2 value, const GLchar* name);
	void setVec3f(glm::fvec3 value, const GLchar* name);
	void setVec4f(glm::fvec4 value, const GLchar* name);
	void setMat3fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);


};

