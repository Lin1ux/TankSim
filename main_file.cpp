#include "Game.h"


//#include "Libs.h"

const int WindowWidth = 1600;
const int WindowHeight = 900;

//Kamera
glm::vec3 CamPosition = glm::vec3(0.0f, 1.0f, -5.0f);			//Pozycja kamery
glm::vec3 CamTargetPosition = glm::vec3(0.0f, 0.0f, 0.0f);		//Pozycja celu (punktu na który patrzy kamera)
float camSpeed = 500;											//Prędkość ruchu kamery
float rotateSpeed = 250;										//Prędkość obrotu kamery
int directon = 0;												//Kierunek Prawo/lewo
int forward = 0;												//Kierunek Przód Prawo
int camVertical = 0;											//Obrót kamery wertykalnie
int camHorizontal = 0;											//Obrót kamery horyzontalnie
//Kąt kamery
float Yaw = 0.0f;
float Pitch = 0.0f;
float CamRotateSpeed = 50.0f;

//Wykrywanie przycisków
void updateInput(GLFWwindow* window, Mesh& mesh)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mesh.Move(glm::vec3(0.0f,0.0f,-0.001f * glfwGetTime()));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mesh.Move(glm::vec3(0.0f, 0.0f, 0.001f * glfwGetTime()));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mesh.Move(glm::vec3(-0.001f * glfwGetTime(), 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mesh.Move(glm::vec3(0.001f * glfwGetTime(), 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		mesh.Rotate(glm::vec3(0.0f, -0.01f * glfwGetTime(), 0.001f ));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		mesh.Rotate(glm::vec3(0.0f, 0.01f * glfwGetTime(), 0.001f));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		mesh.Scale(glm::vec3(0.01 * glfwGetTime()));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		mesh.Scale(glm::vec3(-0.01 * glfwGetTime()));
	}
}

//Obsługa przycisków
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	return;
	if (action == GLFW_PRESS)
	{
		std::cout << "PRessed\n";
		//Poruszanie kamery
		if (key == GLFW_KEY_D)
		{
			directon += -1;
		}
		if (key == GLFW_KEY_A)
		{
			directon += 1;
		}
		if (key == GLFW_KEY_W)
		{
			forward += 1;
		}
		if (key == GLFW_KEY_S)
		{
			forward += -1;
		}
		//Obrót kamery
		if (key == GLFW_KEY_UP)
		{
			camVertical += -1;
		}
		if (key == GLFW_KEY_DOWN)
		{
			camVertical += 1;
		}
		if (key == GLFW_KEY_RIGHT)
		{
			camHorizontal += 1;
		}
		if (key == GLFW_KEY_LEFT)
		{
			camHorizontal += -1;
		}
		if (key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_D)
		{
			directon -= -1;
		}
		if (key == GLFW_KEY_A)
		{
			directon -= 1;
		}
		if (key == GLFW_KEY_W)
		{
			forward -= 1;
		}
		if (key == GLFW_KEY_S)
		{
			forward -= -1;
		}
		if (key == GLFW_KEY_UP)
		{
			camVertical -= -1;
		}
		if (key == GLFW_KEY_DOWN)
		{
			camVertical -= 1;
		}
		if (key == GLFW_KEY_RIGHT)
		{
			camHorizontal -= 1;
		}
		if (key == GLFW_KEY_LEFT)
		{
			camHorizontal -= -1;
		}
	}
}

//Pozwala na poprawną zmianę wielkości okna
void FrameBufferResize(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}

//Ładuje shadery
bool loadShaders(GLuint &program)
{
	bool loadSuccess = true;

	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream file;

	//Vertex Shader
	
	//Odczytanie Pliku Vertex
	file.open("Vertex_core.glsl");

	if (file.is_open())
	{
		while (std::getline(file, temp))
		{
			src += temp + "\n";
		}
	}
	else
	{
		std::cout << "ERROR::LOADSHADER::Nie udało się otworzyć folderu\n";
	}
	file.close();
	
	//Kompilowanie Shaderu
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Creates shader in background
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader,1,&vertSrc,NULL);
	glCompileShader(vertexShader);	//Compiles Shader

	//Obsługa błędów
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADER:: Nie udalo się skompilowac vertex shader\n";
		std::cout << infoLog << "\n";
	}
	//Resetowanie danych pomocniczych
	temp = "";
	src = "";

	//Fragment shader
	//Odczytanie Fragment shadera
	file.open("Fragment_Shadder.glsl");

	if (file.is_open())
	{
		while (std::getline(file, temp))
		{
			src += temp + "\n";
		}
	}
	else
	{
		std::cout << "ERROR::LOADSHADER::Nie udalo sie otworzyc folderu\n";
		loadSuccess = false;
	}
	file.close();

	//Kompilowanie Shadera
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Creates shader in background
	vertSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &vertSrc, NULL);
	glCompileShader(fragmentShader);	//Compiles Shader

	//Obsługa błędu
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADER:: Nie udalo się skompilowac fragment shader\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}

	//Tworzenie Programu Shaderów
	program = glCreateProgram();

	//Dodawanie shaderów
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);	//Zalinkowanie wszystkich dodanych shaderów

	//Obsługa błędu
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADER:: nie udalo sie zalinkowac programu\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}

	//Zwolnienie pamięci
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;
}

//Klawiatura
void updateInput(GLFWwindow* window,glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position.z -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position.z += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position.x -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position.x += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		rotation.y -= 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		rotation.y += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		scale += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		scale -= 0.01f;
	}

}

GLFWwindow* createWindow(
	const char* title, 
	const int width, const int height,
	int& fbWidth, int& fbHeight,
	const int GLMajorVer, const int GLMinorVer,
	bool resizable)
{
	//Parametry okna
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLMajorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLMinorVer);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

	//Pozwala na poprawne zmianę wielkości okna w trakcie działania programu
	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
	glfwSetFramebufferSizeCallback(window, Game::FrameBufferResize);
	glfwMakeContextCurrent(window);

	return window;
}

//Główny program
int main()
{
	Game Game("Tank Simulator",1600,900,3,3,false);

	//Pętla Gry
	while (!Game.getWindowShouldClose())
	{
		//Aktualizacja wydarzeń (np wyłączanie okna X)
		Game.Update();
		Game.Render();
	}
	return 0;
}
