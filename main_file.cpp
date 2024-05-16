#include "Libs.h"

const int WindowWidth = 1600;
const int WindowHeight = 900;

//Trójkąt

Vertex vertices[] =
{
	//Position							//Color								//TexCord					//Normals
	glm::vec3(-0.5f,0.5f,0.0f),			glm::vec3(1.0f,0.0f,0.0f),			glm::vec2(0.0f,1.0f),		glm::vec3(0.0f,0.0f,1.0f),
	glm::vec3(-0.5f,-0.5f,0.0f),		glm::vec3(0.0f,1.0f,0.0f),			glm::vec2(0.0f,0.0f),		glm::vec3(0.0f,0.0f,1.0f),
	glm::vec3(0.5f,-0.5f,0.0f),			glm::vec3(0.0f,0.0f,1.0f),			glm::vec2(1.0f,0.0f),		glm::vec3(0.0f,0.0f,1.0f),
	glm::vec3(0.5f,0.5f,0.0f),			glm::vec3(1.0f,1.0f,0.0f),			glm::vec2(1.0f,1.0f),		glm::vec3(0.0f,0.0f,1.0f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);	//Liczba vertices

GLuint indices[] =
{
	0, 1, 2,	//1 Trójkąt
	0, 2, 3		//2 Trójkąt
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);	//Liczba punktów


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

//Główny program
int main()
{
	//Inicjalizacja biblioteki GLFW
	glfwInit();

	//Tworzenie okna
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	//Parametry okna
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight,"Tank Simulator",NULL,NULL);

	//Pozwala na poprawne zmianę wielkości okna w trakcie działania programu
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, FrameBufferResize); 
	glfwMakeContextCurrent(window);

	//Inicjalizacja biblioteki GLEW (Wymaga okna do poprawnego działania)

	glewExperimental = GL_TRUE;

	//Obsługa błędu GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::main_file.cpp - Nie udalo sie zaladowac biblioteki GLEW\n";
		glfwTerminate();
	}

	//Opcje OpenGL
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);	//Usuwa nie potrzebne rzeczy
	glCullFace(GL_BACK);	//Usuwa tył
	glFrontFace(GL_CCW);	//przeciwnie do wskazówek zegara

	glEnable(GL_BLEND);		//Blending colors
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//GL_LINE

	//Inicjalizacja wykrywania klawiszy
	glfwSetKeyCallback(window, key_callback);

	//Inicjalizacja Shaderów
	shader coreProgram((char*)"Vertex_core.glsl", (char*)"Fragment_Shadder.glsl");

	//Model (Mesh)
	Mesh testMesh(vertices, nrOfVertices, indices, nrOfIndices,
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(2.0f)
		);

	//Texture 0
	Texture texture_0("Textures/bricks.png",GL_TEXTURE_2D,0);

	//Texture 1
	Texture texture_1("Textures/stone-wall.png",GL_TEXTURE_2D,1);

	//Materiał 0
	Material material0(glm::vec3(1.0f), glm::vec3(0.5f), glm::vec3(5.0f), texture_0.getTextureUnit(), texture_1.getTextureUnit());

	//Inicjalizacja Macierzy
	

	//Kamera

	glm::vec3 camPosition(0.0f,0.0f,1.0f);
	glm::vec3 worldUp(0.0f,1.0f,0.0f);
	glm::vec3 camFront(0.0f, 0.0f, -1.0f);
	glm::mat4 ViewMatrix(1.0f);
	ViewMatrix = glm::lookAt(camPosition,camPosition + camFront,worldUp);

	float FOV = 90.0f;			//Pole widzenia
	float nearPlane = 0.1f;
	float farPlane = 100.0f;	//Zasięg rysowania
	glm::mat4 ProjectionMatrix(1.0f);
	ProjectionMatrix = glm::perspective
	(
		glm::radians(FOV),
		static_cast<float>(framebufferWidth) / framebufferHeight,
		nearPlane,
		farPlane
	);

	//Światło
	glm::vec3 lightPos0(0.0f, 0.0f, 1.f); //Pozycja światła

	//Inicjalizacja Uniforms
	coreProgram.setMat4fv(ViewMatrix, "ViewMatrix");
	coreProgram.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
	
	//Pozycja światła
	coreProgram.setVec3f(lightPos0, "lightPos0");
	coreProgram.setVec3f(camPosition, "cameraPos");


	//Pętla Gry
	while (!glfwWindowShouldClose(window))
	{
		//Aktualizacja wydarzeń (np wyłączanie okna X)
		glfwPollEvents();
		updateInput(window, testMesh);

		//Aktualizowanie (Update)
		updateInput(window,testMesh);

		//Czyszczenie ekranu i buforów
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//wysyłanie shaderów do karty graficznej
		coreProgram.set1i(texture_0.getTextureUnit(), "texture0");
		coreProgram.set1i(texture_1.getTextureUnit(), "texture1");
		material0.sendToShader(coreProgram);

		//transformacje (move, rotate, scale)

		//coreProgram.setMat4fv(ModelMatrix, "ModelMatrix");

		//Pozwala na zmianę wielkości okna
		
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
		ProjectionMatrix = glm::mat4(1.0f);
		ProjectionMatrix = glm::perspective
		(
			glm::radians(FOV),
			static_cast<float>(framebufferWidth) / framebufferHeight,
			nearPlane,
			farPlane
		);

		coreProgram.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

		coreProgram.use();

		//Aktywacja textur
		texture_0.bind();
		texture_1.bind();

		testMesh.render(&coreProgram);

		//glDrawArrays(GL_TRIANGLES, 0 , nrOfVertices);

		//Koniec rysowania 
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//Zwalnianie pamięci
	glfwDestroyWindow(window);
	glfwTerminate();

	system("Pause");

	return 0;
}
