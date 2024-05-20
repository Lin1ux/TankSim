#include "Texture.h"

//Konstruktor
Texture::Texture(const char* filename, GLenum type)
{
	this->type = type;
	this->id = readTexture(filename);
}

//Dekonstruktor
Texture::~Texture()
{
	glDeleteTextures(1,&this->id);
}
//Zwraca Id 
GLuint Texture::getID() const
{
	return this->id;
}
//Bindowanie tekstury
void Texture::bind(const GLint texture_unit)
{
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(this->type, this->id);
}
//Od bindowuje tekstury
void Texture::unbind()
{
	glActiveTexture(0);
	glBindTexture(this->type, 0);
}
//Wczytywanie textur 
GLuint Texture::readTexture(const char* filename)
{
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamiêci komputera
	std::vector<unsigned char> image;	//Alokuj wektor do wczytania obrazka
	unsigned width, height;				//Zmienne do których wczytamy wymiary obrazka
	
	//Wczytanie obrazka
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamiêci karty graficznej
	glGenTextures(1, &tex);				//Zainicjuj jeden uchwyt
	glBindTexture(this->type, tex);	//Uaktywnij uchwyt

	//Wczytanie obrazka do pamiêci Karty graficznej
	glTexImage2D(this->type, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glGenerateMipmap(this->type);			//Generowanie mipmapy

	//Opcje
	glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);					//Powtarzanie textury
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	//Antyalliasing						//Powtarzanie textury
	glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}
