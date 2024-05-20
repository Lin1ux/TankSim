#pragma once

#include<vector>
#include<string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include"Vertex.h"


class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	Primitive();
	virtual ~Primitive();

	void set(const Vertex* vertices,
		const unsigned nrOfVertices,
		const GLuint* indices,
		const unsigned nrOfIndices);


	Vertex* getVertices();
	GLuint* getIndices();
	const unsigned getNrOfVertices();
	const unsigned getNrOfIndices();
};

/*class Quad : public Primitive
{
public:
	Quad();
};*/
