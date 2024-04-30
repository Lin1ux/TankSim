#include "shader.h"

std::string shader::loadShaderSource(char* fileName)
{
	std::string temp = "";
	std::string src = "";

	std::ifstream file;

	//Vertex Shader

	//Odczytanie Pliku Vertex
	file.open(fileName);

	if (file.is_open())
	{
		while (std::getline(file, temp))
		{
			src += temp + "\n";
		}
	}
	else
	{
		std::cout << "ERROR::SHADER::Nie uda³o siê otworzyæ folderu: " << fileName << "\n";
	}
	file.close();

	return src;
}

GLuint shader::loadShader(GLenum type, char*  fileName)
{
	char infoLog[512];
	GLint success;

	//Kompilowanie Shaderu
	GLuint shader = glCreateShader(type); //Creates shader in background
	std::string str_src = this->loadShaderSource(fileName);
	const GLchar* src = str_src.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);	//Compiles Shader

	//Obs³uga b³êdów
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:: Nie udalo siê skompilowac vertex shader: "<< fileName<<"\n";
		std::cout << infoLog << "\n";
	}
	return shader;
}

void shader::linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
{
	char infoLog[512];
	GLint success;

	this->id = glCreateProgram();

	glAttachShader(this->id, vertexShader);

	if (geometryShader)
	{
		glAttachShader(this->id, geometryShader);
	}
	glAttachShader(this->id, fragmentShader);

	glLinkProgram(this->id);

	//Obs³uga b³êdu
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:: nie udalo sie zalinkowac programu: "<<"\n";
		std::cout << infoLog << "\n";
	}

	glUseProgram(0);
}

shader::shader(char* vertexFile, char* fragmentFile)
{
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;

	vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);
	
	//if (geometryFile != "")
	//{
	//	geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
	//}
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

	this->linkProgram(vertexShader, geometryShader, fragmentShader);

	//Zwolnienie pamiêci
	
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
}

shader::~shader()
{
	glDeleteProgram(this->id);
}

void shader::use()
{
	glUseProgram(this->id);
}

void shader::unuse()
{
	glUseProgram(0);
}

void shader::set1i(GLint value, const GLchar* name)
{
	this->use();

	glUniform1i(glGetUniformLocation(this->id, name), value);

	this->unuse();
}

void shader::setVec1f(GLfloat value, const GLchar* name)
{
	this->use();

	glUniform1f(glGetUniformLocation(this->id, name), value);

	this->unuse();
}

void shader::setVec2f(glm::fvec2 value, const GLchar* name)
{
	this->use();

	glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	this->unuse();
}

void shader::setVec3f(glm::fvec3 value, const GLchar* name)
{
	this->use();

	glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	this->unuse();
}

void shader::setVec4f(glm::fvec4 value, const GLchar* name)
{
	this->use();

	glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	this->unuse();
}

void shader::setMat3fv(glm::mat4 value, const GLchar* name, GLboolean transpose)
{
	this->use();

	glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

	this->unuse();
}

void shader::setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose)
{
	this->use();

	glUniformMatrix4fv(glGetUniformLocation(this -> id, name), 1, transpose, glm::value_ptr(value));

	this->unuse();
}
