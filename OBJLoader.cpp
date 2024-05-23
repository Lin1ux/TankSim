#include "OBJLoader.h"

std::vector<Vertex> OBJModel::loadOBJ(const char* fileName)
{
	//Vertex
	std::vector<glm::fvec3> vertexPositions;
	std::vector<glm::fvec2> vertexTexCords;
	std::vector<glm::fvec3> vertexNormals;

	//Œciany 
	std::vector<GLint> vertexPositionIndicies;
	std::vector<GLint> vertexTexCordIndicies;
	std::vector<GLint> vertexNormalIndicies;

	//Tabela Vertexów
	std::vector<Vertex> vertices;
	//Tabela Indeksów

	//Opening File
	std::stringstream ss;
	std::ifstream file(fileName);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 tempVec3;
	glm::vec3 tempVec2;
	GLint tempGLInt = 0;

	//Sprawdzenie czy uda³o siê otworzyæ plik
	if (!file.is_open())
	{
		throw "ERROR::OBJLOADER:: Nie uda³o siê otworzyæ pliku";
	}
	//Czytanie linia po linia na raz
	while (std::getline(file, line))
	{
		//Odczyt prefixu
		ss.clear();
		ss.str(line);
		ss >> prefix;
		if (prefix == "v")	//Pozycja Vertexów
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexPositions.push_back(tempVec3);
		}
		else if (prefix == "vt")	//Wspó³rzêdne textóry (Texture Cordinates)
		{
			ss >> tempVec2.x >> tempVec2.y;
			vertexTexCords.push_back(tempVec2);
		}
		else if (prefix == "vn")	//Normalne
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexNormals.push_back(tempVec3);
		}
		else if (prefix == "f")	//Œciany
		{
			int counter = 0;
			while (ss >> tempGLInt)
			{
				//Wrzuca indexy (indieces) w odpowniednie miejsce
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
				//Radzenie z znakami
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
				//Reset licznika
				if (counter > 2)
				{
					counter = 0;
				}
			}
		}
		else
		{

		}
	}

	//Budowanie fina³owej tabeli vertexów (do Mesha)
	vertices.resize(vertexPositionIndicies.size(), Vertex()); //zape³nienie tablicy pustymi Vertexami


	//Wczytanie wszystkich indeksów
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i].position = vertexPositions[vertexPositionIndicies[i] - 1];
		vertices[i].texcord = vertexTexCords[vertexTexCordIndicies[i] - 1];
		vertices[i].normal = vertexNormals[vertexNormalIndicies[i] - 1];
		vertices[i].color = glm::vec3(1.0f, 1.0f, 1.0f);

		//indexes.push_back(vertexPositionIndicies[i], vertexPositionIndicies[i], vertexPositionIndicies[i]);
		//std::cout << vertices[i].position.x << " " << vertices[i].position.y << " " << vertices[i].position.z << "\n";
	}

	std::cout << "OBJ LOADED\n";
	//£adowanie zakoñczone sukcesem
	return vertices;
}
