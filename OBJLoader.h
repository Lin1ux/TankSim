#pragma once

//STD
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

//GLEW
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//OpenGL
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//Own
#include "Vertex.h"

class OBJModel
{
public:
	static std::vector<Vertex> loadOBJ(const char* fileName);
};

