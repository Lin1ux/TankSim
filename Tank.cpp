#pragma warning(disable : 4996)

#include "Tank.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>

std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals; // Won't be used at the moment.

void Tank::LoadHull()
{
	std::cout << "test\n";
	// Odczytanie pliku .obj
	//bool res = loadOBJ("TankHull.obj", vertices, uvs, normals);
	//std::cout << res << "\n";;
	//Rysowanie
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
}

Tank::Tank()
{
	std::cout << "Tworzenie Czołgu";
	bool res = loadOBJ("TankHull.obj", vertices, uvs, normals);
	std::cout << res << "\n";;
	std::cout << "Ukończono";
}
bool loadOBJ(const char* path, std::vector<glm::vec3> &out_vertices, std::vector <glm::vec2> &out_uvs, std::vector <glm::vec3> &out_normals)
{
	//dane obiektu
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	
	//Sprawdzenie czy plik istnieje
	FILE* file = fopen(path, "r");
	if (file == NULL) 
	{
		printf("Nie udało się otworzyć pliku\n");
		return false;
	}
	while (1) 
	{
		char lineHeader[128];
		//Czytanie pierwszego słowa
		int res = fscanf(file, "%s", lineHeader);
		//Koniec pliku i wyjście z pętli
		if (res == EOF)
		{
			break; 
		}
		//Czytanie Vertexów
		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		//Czytanie vt
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		//Czytanie vn
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		//Czytanie F
		else if (strcmp(lineHeader, "f") == 0) 
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) 
			{
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	//Indeksowanie
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
	

}

//Ogarnąć
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/