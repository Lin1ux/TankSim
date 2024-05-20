#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "lodepng.h"

class Texture
{
private:
	GLuint id;
	unsigned int type;

	GLuint readTexture(const char* filename);

public:

	//Konstruktor
	Texture(const char* filename,GLenum type);
	//Dekonstruktor
	~Texture();
	GLuint getID() const;
	void bind(const GLint texture_unit);
	void unbind();
};

