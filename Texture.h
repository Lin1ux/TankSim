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
	GLint textureUnit;
	GLuint readTexture(const char* filename);

public:

	//Konstruktor
	Texture(const char* filename,GLenum type,GLint texture_unit);
	//Dekonstruktor
	~Texture();
	GLuint getID() const;
	GLuint getTextureUnit() const;
	void bind();
	void unbind();
};

