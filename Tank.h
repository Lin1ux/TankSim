#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>

class Tank
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
public:
	Tank();
	void LoadHull();
};

bool loadOBJ(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals);
