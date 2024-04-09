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

static std::vector<Vertex> loadOBJ(const char* fileName)
{
	//Vertex
	std::vector<glm::fvec3> vertexPositions;
	std::vector<glm::fvec2> vertexTexCords;
	std::vector<glm::fvec3> vertexNormals;

	//Faces 
	std::vector<GLint> vertexPositionIndicies;
	std::vector<GLint> vertexTexCordIndicies;
	std::vector<GLint> vertexNormalIndicies;

	//Vertex array
	std::vector<Vertex> vertices;

	//Opening File
	std::stringstream ss;
	std::ifstream file(fileName);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 tempVec3;
	glm::vec3 tempVec2;
	GLint tempGLInt = 0;

	//Open error check
	if (!file.is_open())
	{
		throw "ERROR::OBJLOADER:: Nie uda³o siê otworzyæ pliku";
	}
	//Read one line at time
	while (std::getline(file, line))
	{
		//Getting prefix
		ss.clear();
		ss.str(line);
		ss >> prefix;
		if (prefix == "v")	//Vertex Position
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexPositions.push_back(tempVec3);
		}
		else if (prefix == "vt")	//Texture Cordinates
		{
			ss >> tempVec2.x >> tempVec2.y;
			vertexTexCords.push_back(tempVec2);
		}
		else if (prefix == "vn")	//Normals
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexNormals.push_back(tempVec3);
		}
		else if (prefix == "f")	//Faces
		{
			int counter = 0;
			while (ss >> tempGLInt)
			{
				//pushes indices into correct vectors
				if (counter == 0)
				{
					vertexPositionIndicies.push_back(tempGLInt);
					std::cout << "V: " << tempGLInt << " T: ";
				}
				else if (counter == 1)
				{
					vertexTexCordIndicies.push_back(tempGLInt);
					std::cout << tempGLInt << " N: ";
				}
				else if (counter == 2)
				{
					vertexNormalIndicies.push_back(tempGLInt);
					std::cout << tempGLInt << "\n";
				}
				//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}
				//Reset Counter
				if (counter > 2)
				{
					counter = 0;
				}
			}
		}
		else
		{

		}
		
		//Build final vertex
		vertices.resize(vertexPositionIndicies.size(), Vertex()); //Fill vector with empty Vertexes


		//Load in all indices
		for (size_t i = 0; i < vertices.size(); ++i)
		{
			vertices[i].position = vertexPositions[vertexPositionIndicies[i] - 1];
			vertices[i].texcord = vertexTexCords[vertexTexCordIndicies[i] - 1];
			vertices[i].normal = vertexNormals[vertexNormalIndicies[i] - 1];
			vertices[i].color = glm::vec3(1.0f, 1.0f, 1.0f);
		}

	}
	std::cout << "OBJ LOADED\n";
	//Load success
	return vertices;
}

