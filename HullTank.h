#pragma once

#include <vector>
#include <string>
#include "model.h"
#include "Vertex.h"


namespace Models 
{
	namespace HullInternal 
	{
		extern float vertices[];
		extern float normals[];
		extern float vertexNormals[];
		extern float texCoords[];
		extern float colors[];
		extern unsigned int vertexCount;
	}

	class HullTank : public Model 
	{
		std::vector<float> v;			//Vertices
		std::vector<float> vn;			//Normals
		std::vector<float> vt;			//For Textures
		std::vector<float> col;			//Colors
		std::vector<unsigned int> f;	//Faces
		std::vector<Vertex> Vertexes;	//Vertex
		std::vector<glm::vec3> VertexPos;	//Vertices

	public:
		HullTank();
		virtual ~HullTank();
		virtual void drawSolid(bool smooth = false);
		float round4(float a);
		bool loadModel();
	};

	extern HullTank hullTank;
}



