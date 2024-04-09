


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "HullTank.h"
#include "OBJLoader.h"

namespace Models
{

	HullTank hullTank;

	HullTank::HullTank()
	{
		Vertexes = loadOBJ("test.obj");
		vertexCount = Vertexes.size();
		for (int i = 0; i < vertexCount; i++)
		{
			VertexPos.push_back(Vertexes[i].position);
		}

		//loadModel();
		//vertices = v.data();
		//vertexNormals = vn.data();
		//normals = vn.data();
		//colors = col.data();
		//texCoords = vt.data();
		//vertexCount = v.size()/4;
		
		//vertices = HullInternal::vertices;
		//normals = HullInternal::normals;
		//vertexNormals = HullInternal::vertexNormals;
		//texCoords = HullInternal::texCoords;
		//colors = HullInternal::colors;
		//vertexCount = HullInternal::vertexCount;


		//std::vector<glm::vec3> vertices;
		//std::vector<glm::vec2> uvs;
		//std::vector<glm::vec3> normals; // Won't be used at the moment.
		/*bool res = loadOBJ("test.obj", vertices, uvs, normals);

		
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		
		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);*/

	}

	HullTank::~HullTank() 
	{

	}

	void HullTank::drawSolid(bool smooth)
	{
		//VAO
		/**/

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);



		glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices);
		if (!smooth) glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals);
		else glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, vertexNormals);
		glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords);
		glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, colors);

		//glDrawElements(GL_TRIANGLES, f.size(), GL_UNSIGNED_INT, 0);


		glDrawElements(GL_TRIANGLES, f.size(), GL_UNSIGNED_INT, f.data());
		//glDrawElements(GL_TRIANGLES, f.size(), GL_UNSIGNED_INT, f.data());

		//glDrawArrays(GL_TRIANGLES, 0, vertexCount);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
	}

	float HullTank::round4(float a)
	{
		return round(a * 10000) / 10000;
	}

	bool HullTank::loadModel()
	{
		std::string data;
		float x;
		float y;
		float z;
		std::string E1;
		std::string E2;
		std::string E3;
		std::ifstream file;
		//file.open("test.obj");
		file.open("Test.obj");
		if (!file.good())
		{
			std::cout << "Can't Open file\n";
			return false;
		}
		while (!file.eof())
		{
			file >> data;
			//std::cout << data << "\n";
			if (data == "v")
			{
				file >> x;
				file >> y;
				file >> z;
				v.push_back(round4(x));
				v.push_back(round4(y));
				v.push_back(round4(z));
				v.push_back(1.0f);
				//std::cout << data<<" "<< x << " " << y << " " << z << "\n";
				col.push_back(1.0f);
				col.push_back(1.0f);
				col.push_back(1.0f);
				col.push_back(1.0f);
			}
			else if (data == "vn")
			{
				file >> x;
				file >> y;
				file >> z;
				vn.push_back(x);
				vn.push_back(y);
				vn.push_back(z);
				vn.push_back(1.0f);
				//std::cout << data << " " << x << " " << y << " " << z << "\n";
			}
			else if (data == "vt")
			{
				file >> x;
				file >> y;
				vt.push_back(x);
				vt.push_back(y);
				vt.push_back(1.0f);
				//std::cout << data << " " << x << " " << y << "\n";
			}
			else if (data == "f")
			{
				//Reseting variables
				x = -1;
				y = -1;
				z = -1;
				std::string str = "";
				//Reading Data
				file >> E1;
				file >> E2;
				file >> E3;
				//Spliting Faces data
				for (int i = 0; i < E1.length(); i++)
				{
					if (E1[i] == '/' && x == -1)
					{
						x = std::stoi(str);		
						str = "";
						continue;
					}
					if (E1[i] == '/' && y == -1)
					{
						y = std::stoi(str);
						str = "";
						continue;
					}
					str += E1[i];
				}
				z = std::stoi(str);
				//Adding to vector
				f.push_back(round4(x));
				f.push_back(round4(y));
				f.push_back(round4(z));
				//std::cout << data << " " << x << "/" << y << "/" << z;
				//Reseting variables
				str = "";
				x = -1;
				y = -1;
				z = -1;
				//Spliting Faces data
				for (int i = 0; i < E2.length(); i++)
				{
					if (E2[i] == '/' && x == -1)
					{
						x = std::stoi(str);
						str = "";
						continue;
					}
					if (E2[i] == '/' && y == -1)
					{
						y = std::stoi(str);
						str = "";
						continue;
					}
					str += E2[i];
				}
				z = std::stoi(str);
				//Adding to vector
				f.push_back(round4(x));
				f.push_back(round4(y));
				f.push_back(round4(z));
				//std::cout << " " << x << "/" << y << "/" << z << " ";
				//Resting variables
				str = "";
				x = -1;
				y = -1;
				z = -1;
				//Spliting Faces data
				for (int i = 0; i < E3.length(); i++)
				{
					if (E3[i] == '/' && x == -1)
					{
						x = std::stoi(str);
						str = "";
						continue;
					}
					if (E3[i] == '/' && y == -1)
					{
						y = std::stoi(str);
						str = "";
						continue;
					}
					str += E3[i];
				}
				z = std::stoi(str);
				//Adding to vector
				f.push_back(round4(x));
				f.push_back(round4(y));
				f.push_back(round4(z));
				//std::cout << " " << x << "/" << y << "/" << z << "\n";
				//Resting variables
				str = "";
				x = -1;
				y = -1;
				z = -1;
				data = "";
			}
		}
		for (int i = 0; i < f.size(); i++)
		{
			//std::cout << f[i] << "\n";
		}
		//std::cout << f.size()<<"\n";
	}

	namespace HullInternal {
		unsigned int vertexCount = 36;

		float vertices[] = {
			1.0f,-1.0f,-1.0f,1.0f,
			-1.0f, 1.0f,-1.0f,1.0f,
			-1.0f,-1.0f,-1.0f,1.0f,

			1.0f,-1.0f,-1.0f,1.0f,
			1.0f, 1.0f,-1.0f,1.0f,
			-1.0f, 1.0f,-1.0f,1.0f,


			-1.0f,-1.0f, 1.0f,1.0f,
			1.0f, 1.0f, 1.0f,1.0f,
			1.0f,-1.0f, 1.0f,1.0f,

			-1.0f,-1.0f, 1.0f,1.0f,
			-1.0f, 1.0f, 1.0f,1.0f,
			1.0f, 1.0f, 1.0f,1.0f,

			1.0f,-1.0f, 1.0f,1.0f,
			1.0f, 1.0f,-1.0f,1.0f,
			1.0f,-1.0f,-1.0f,1.0f,

			1.0f,-1.0f, 1.0f,1.0f,
			1.0f, 1.0f, 1.0f,1.0f,
			1.0f, 1.0f,-1.0f,1.0f,

			-1.0f,-1.0f,-1.0f,1.0f,
			-1.0f, 1.0f, 1.0f,1.0f,
			-1.0f,-1.0f, 1.0f,1.0f,

			-1.0f,-1.0f,-1.0f,1.0f,
			-1.0f, 1.0f,-1.0f,1.0f,
			-1.0f, 1.0f, 1.0f,1.0f,

			-1.0f,-1.0f,-1.0f,1.0f,
			1.0f,-1.0f, 1.0f,1.0f,
			1.0f,-1.0f,-1.0f,1.0f,

			-1.0f,-1.0f,-1.0f,1.0f,
			-1.0f,-1.0f, 1.0f,1.0f,
			1.0f,-1.0f, 1.0f,1.0f,

			-1.0f, 1.0f, 1.0f,1.0f,
			1.0f, 1.0f,-1.0f,1.0f,
			1.0f, 1.0f, 1.0f,1.0f,

			-1.0f, 1.0f, 1.0f,1.0f,
			-1.0f, 1.0f,-1.0f,1.0f,
			1.0f, 1.0f,-1.0f,1.0f,

		};

		float colors[] = {
			1.0f,0.0f,0.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,

			1.0f,0.0f,0.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,

			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,

			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,

			0.0f,0.0f,1.0f,1.0f,
			0.0f,0.0f,1.0f,1.0f,
			0.0f,0.0f,1.0f,1.0f,

			0.0f,0.0f,1.0f,1.0f,
			0.0f,0.0f,1.0f,1.0f,
			0.0f,0.0f,1.0f,1.0f,

			1.0f,1.0f,0.0f,1.0f,
			1.0f,1.0f,0.0f,1.0f,
			1.0f,1.0f,0.0f,1.0f,

			1.0f,1.0f,0.0f,1.0f,
			1.0f,1.0f,0.0f,1.0f,
			1.0f,1.0f,0.0f,1.0f,

			0.0f,1.0f,1.0f,1.0f,
			0.0f,1.0f,1.0f,1.0f,
			0.0f,1.0f,1.0f,1.0f,

			0.0f,1.0f,1.0f,1.0f,
			0.0f,1.0f,1.0f,1.0f,
			0.0f,1.0f,1.0f,1.0f,

			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,

			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
		};

		float normals[] = {
			0.0f, 0.0f,-1.0f,0.0f,
			0.0f, 0.0f,-1.0f,0.0f,
			0.0f, 0.0f,-1.0f,0.0f,

			0.0f, 0.0f,-1.0f,0.0f,
			0.0f, 0.0f,-1.0f,0.0f,
			0.0f, 0.0f,-1.0f,0.0f,

			0.0f, 0.0f, 1.0f,0.0f,
			0.0f, 0.0f, 1.0f,0.0f,
			0.0f, 0.0f, 1.0f,0.0f,

			0.0f, 0.0f, 1.0f,0.0f,
			0.0f, 0.0f, 1.0f,0.0f,
			0.0f, 0.0f, 1.0f,0.0f,

			1.0f, 0.0f, 0.0f,0.0f,
			1.0f, 0.0f, 0.0f,0.0f,
			1.0f, 0.0f, 0.0f,0.0f,

			1.0f, 0.0f, 0.0f,0.0f,
			1.0f, 0.0f, 0.0f,0.0f,
			1.0f, 0.0f, 0.0f,0.0f,

			-1.0f, 0.0f, 0.0f,0.0f,
			-1.0f, 0.0f, 0.0f,0.0f,
			-1.0f, 0.0f, 0.0f,0.0f,

			-1.0f, 0.0f, 0.0f,0.0f,
			-1.0f, 0.0f, 0.0f,0.0f,
			-1.0f, 0.0f, 0.0f,0.0f,

			0.0f,-1.0f, 0.0f,0.0f,
			0.0f,-1.0f, 0.0f,0.0f,
			0.0f,-1.0f, 0.0f,0.0f,

			0.0f,-1.0f, 0.0f,0.0f,
			0.0f,-1.0f, 0.0f,0.0f,
			0.0f,-1.0f, 0.0f,0.0f,

			0.0f, 1.0f, 0.0f,0.0f,
			0.0f, 1.0f, 0.0f,0.0f,
			0.0f, 1.0f, 0.0f,0.0f,

			0.0f, 1.0f, 0.0f,0.0f,
			0.0f, 1.0f, 0.0f,0.0f,
			0.0f, 1.0f, 0.0f,0.0f,
		};

		float vertexNormals[] = {
			1.0f,-1.0f,-1.0f,0.0f,
			-1.0f, 1.0f,-1.0f,0.0f,
			-1.0f,-1.0f,-1.0f,0.0f,

			1.0f,-1.0f,-1.0f,0.0f,
			1.0f, 1.0f,-1.0f,0.0f,
			-1.0f, 1.0f,-1.0f,0.0f,


			-1.0f,-1.0f, 1.0f,0.0f,
			1.0f, 1.0f, 1.0f,0.0f,
			1.0f,-1.0f, 1.0f,0.0f,

			-1.0f,-1.0f, 1.0f,0.0f,
			-1.0f, 1.0f, 1.0f,0.0f,
			1.0f, 1.0f, 1.0f,0.0f,

			1.0f,-1.0f, 1.0f,0.0f,
			1.0f, 1.0f,-1.0f,0.0f,
			1.0f,-1.0f,-1.0f,0.0f,

			1.0f,-1.0f, 1.0f,0.0f,
			1.0f, 1.0f, 1.0f,0.0f,
			1.0f, 1.0f,-1.0f,0.0f,

			-1.0f,-1.0f,-1.0f,0.0f,
			-1.0f, 1.0f, 1.0f,0.0f,
			-1.0f,-1.0f, 1.0f,0.0f,

			-1.0f,-1.0f,-1.0f,0.0f,
			-1.0f, 1.0f,-1.0f,0.0f,
			-1.0f, 1.0f, 1.0f,0.0f,

			-1.0f,-1.0f,-1.0f,0.0f,
			1.0f,-1.0f, 1.0f,0.0f,
			1.0f,-1.0f,-1.0f,0.0f,

			-1.0f,-1.0f,-1.0f,0.0f,
			-1.0f,-1.0f, 1.0f,0.0f,
			1.0f,-1.0f, 1.0f,0.0f,

			-1.0f, 1.0f, 1.0f,0.0f,
			1.0f, 1.0f,-1.0f,0.0f,
			1.0f, 1.0f, 1.0f,0.0f,

			-1.0f, 1.0f, 1.0f,0.0f,
			-1.0f, 1.0f,-1.0f,0.0f,
			1.0f, 1.0f,-1.0f,0.0f,
		};

		float texCoords[] = {
			1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
			1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

			1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
			1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

			1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
			1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

			1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
			1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

			1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
			1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

			1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
			1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
		};
	}
}


