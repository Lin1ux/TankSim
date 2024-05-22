#include "game.h"

void Game::InitGLFW()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::Inicjalizacja GLFW nie udana\n";
		glfwTerminate();
	}
}

void Game::InitWindow(const char* title, bool resizable)
{
	//Parametry okna
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::Nie uda³o siê zainicjalizowaæ okna\n";
		glfwTerminate();
	}

	//Pozwala na poprawne zmianê wielkoœci okna w trakcie dzia³ania programu
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
	glfwSetFramebufferSizeCallback(this->window, Game::FrameBufferResize);
	glfwMakeContextCurrent(this->window);
}

void Game::InitGLEW()
{
	//Inicjalizacja bibliotek GLEW
	glewExperimental = GL_TRUE;

	//Obs³uga b³êdu GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::Nie udalo sie zaladowac biblioteki GLEW\n";
		glfwTerminate();
	}
}

void Game::InitOpenGLOptions()
{
	//Opcje OpenGL
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);	//Usuwa nie potrzebne rzeczy
	glCullFace(GL_BACK);	//Usuwa ty³
	glFrontFace(GL_CCW);	//przeciwnie do wskazówek zegara

	glEnable(GL_BLEND);		//Blending colors
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//GL_LINE
	//Input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//Wy³¹czenie kursora
}

void Game::InitMatrices()
{
	this->ViewMatrix = glm::mat4(1.0f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.0f);
	this->ProjectionMatrix = glm::perspective
	(
		glm::radians(this->FOV),
		static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
		this->nearPlane,
		this->farPlane
	);
}

void Game::InitShader()
{
	this->Shaders.push_back(new shader((char*)"Vertex_core.glsl", (char*)"Fragment_Shadder.glsl"));
}

void Game::InitTextures()
{
	//Texture 0
	this->Textures.push_back(new Texture("Textures/bricks.png", GL_TEXTURE_2D));
	
	this->Textures.push_back(new Texture("Textures/bricks_specular.png", GL_TEXTURE_2D));

	//Texture 1
	this->Textures.push_back(new Texture ("Textures/stone-wall.png", GL_TEXTURE_2D));

}

void Game::InitMaterials()
{
	this->Materials.push_back(new Material(glm::vec3(1.0f), glm::vec3(0.5f), glm::vec3(5.0f), 0, 1));
}

void Game::InitMeshes()
{
	//Piramid newQuad = Piramid();
	Piramid newPiramid = Piramid();
	//newPiramid = new Piramid();

	this->Meshes.push_back(new Mesh(&newPiramid,
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(2.0f)
	));

	Quad newQuad = Quad();

	this->Meshes.push_back(new Mesh(&newQuad,
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(2.0f)
	));
}

//Pozycje œwiate³
void Game::InitLights()
{
	//Œwiat³o
	this->Lights.push_back(new glm::vec3(0.0f, 0.0f, 1.f));
}

void Game::InitUniforms()
{
	//Inicjalizacja Uniforms
	this->Shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->Shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	//Pozycja œwiat³a
	this->Shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->Lights[0], "lightPos0");
	this->Shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}

void Game::UpdateUniforms()
{
	//wysy³anie shaderów do karty graficznej
	//this->Shaders[SHADER_CORE_PROGRAM]->set1i(0, "texture0");
	//this->Shaders[SHADER_CORE_PROGRAM]->set1i(1, "texture1");
	//this->Materials[MATERIAL_1]->sendToShader(*this->Shaders[SHADER_CORE_PROGRAM]);

	//Aktualizacja macierzy kamery
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);
	this->Shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");

	//Pozwala na zmianê wielkoœci okna
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);


	this->ProjectionMatrix = glm::perspective
	(
		glm::radians(this->FOV),
		static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
		this->nearPlane,
		this->farPlane
	);

	this->Shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");

}

Game::Game(const char* title,
	const int width, const int height,
	const int GLVerMaj, const int GLVerMin,
	bool resizable)
	: WINDOW_WIDTH(width),
	WINDOW_HEIGHT(height),
	GL_VERSION_MAJOR(GLVerMaj),
	GL_VERSION_MINOR(GLVerMin)

{
	//Init variables
	this->window = nullptr;
	this->frameBufferWidth = this->WINDOW_WIDTH;
	this->frameBufferHeight = this->WINDOW_HEIGHT;

	//Kamera
	this->camPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->camFront = glm::vec3(0.0f, 0.0f, -1.0f);

	this->FOV = 90.0f;			//Pole widzenia
	this->nearPlane = 0.1f;
	this->farPlane = 1000.0f;	//Zasiêg rysowania

	this->dt = 0.0f;
	this->curTime = 0.0f;
	this->lastTime = 0.0f;

	this->lastMouseX = 0.0f;
	this->lastMouseY = 0.0f;
	this->mouseX = 0.0f;
	this->mouseY = 0.0f;
	this->mouseOffsetX = 0.0f;
	this->mouseOffsetY = 0.0f;
	this->firstMouse = true;


	this->InitGLFW();
	this->InitWindow(title,resizable);
	this->InitGLEW();
	this->InitOpenGLOptions();
	this->InitMatrices();
	this->InitShader();
	this->InitTextures();
	this->InitMaterials();
	this->InitMeshes();
	this->InitLights();
	this->InitUniforms();
}

Game::~Game()
{
	//Zwalnianie pamiêci
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->Shaders.size(); i++)
	{
		delete this->Shaders[i];
	}
	for (size_t i = 0; i < this->Textures.size(); i++)
	{
		delete this->Textures[i];
	}
	for (size_t i = 0; i < this->Materials.size(); i++)
	{
		delete this->Materials[i];
	}
	for (size_t i = 0; i < this->Meshes.size(); i++)
	{
		delete this->Meshes[i];
	}
	for (size_t i = 0; i < this->Lights.size(); i++)
	{
		delete this->Lights[i];
	}
}


int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

void Game::updateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Game::UpdateKeyboardInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	//Kamera
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camPosition.z -= 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camPosition.z += 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camPosition.x -= 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camPosition.x += 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS)
	{
		this->camPosition.y -= 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->camPosition.y += 0.05f;
	}
}

void Game::UpdateMouseInput()
{
	//Pobieranie kursora z okna i zapisanie pozycji w mouseX i mouseY
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);
	
	//Sprawdzenie czy kamera ruszy³a siê pierwszy raz
	if (this->firstMouse)
	{
		//Ustawianie ostatniej pozycji kamery
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	//Liczenie offsetu (zmiany pozycji kamery)
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY; //Y jest odwrócone
	
	//Ustawienie ostatnich wspó³rzêdnych X i Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

}

void Game::UpdateInput()
{
	//Wyjœcie
	glfwPollEvents();
	this->UpdateKeyboardInput();
	this->UpdateMouseInput();
	
}

void Game::Update()
{
	//Aktualizacja wydarzeñ (np wy³¹czanie okna X)
	this->updateDt();
	this->UpdateInput();

}

void Game::Render()
{

	//Aktualizowanie (Update)
	//updateInput(window);
	
	//updateInput(window, *this->Meshes[MESH_QUAD]);

	//Czyszczenie ekranu i buforów
	glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Aktualizowanie uniformów (wysy³anie do karty graficznej
	this->UpdateUniforms();

	this->Materials[MATERIAL_1]->sendToShader(*this->Shaders[SHADER_CORE_PROGRAM]);

	this->Shaders[SHADER_CORE_PROGRAM]->use();

	//Aktywacja textur
	this->Textures[TEXTURE_BRICKS0]->bind(0);	//Diffuse texture
	this->Textures[TEXTURE_STONE1]->bind(1);	//Specular texture

	//Rysowanie
	this->Meshes[MESH_QUAD]->render(this->Shaders[SHADER_CORE_PROGRAM]);
	
	//Aktywacja textur
	this->Textures[TEXTURE_BRICKS0]->bind(0);	//Diffuse texture
	this->Textures[TEXTURE_BRICKS_SPEC]->bind(1);	//Specular texture
	
	this->Meshes[1]->render(this->Shaders[SHADER_CORE_PROGRAM]);

	//Koniec rysowania 
	glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


//Statyczne
void Game::FrameBufferResize(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}


/*void Game::updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
//Wykrywanie przycisków
void Game::updateInput(GLFWwindow* window, Mesh& mesh)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mesh.Move(glm::vec3(0.0f, 0.0f, -0.001f * glfwGetTime()));
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
		mesh.Rotate(glm::vec3(0.0f, -0.01f * glfwGetTime(), 0.001f));
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
*/