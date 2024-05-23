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
		std::cout << "ERROR::Nie uda�o si� zainicjalizowa� okna\n";
		glfwTerminate();
	}

	//Pozwala na poprawne zmian� wielko�ci okna w trakcie dzia�ania programu
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
	glfwSetFramebufferSizeCallback(this->window, Game::FrameBufferResize);
	glfwMakeContextCurrent(this->window);
}

void Game::InitGLEW()
{
	//Inicjalizacja bibliotek GLEW
	glewExperimental = GL_TRUE;

	//Obs�uga b��du GLEW
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

	//glEnable(GL_CULL_FACE);	//Usuwa nie potrzebne rzeczy
	//glCullFace(GL_FRONT);	//Usuwa ty�
	glFrontFace(GL_CCW);	//przeciwnie do wskaz�wek zegara

	glEnable(GL_BLEND);		//Blending colors
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//GL_LINE
	//Input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//Wy��czenie kursora
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
	this->Materials.push_back(new Material(glm::vec3(1.0f), glm::vec3(0.5f), glm::vec3(2.0f), 0, 1));
}

void Game::InitOBJModels()
{

}

void Game::InitModels()
{
	std::vector<Mesh*> Meshes;
	//Inicjalizacja meshy w modelu
	/*Piramid newPiramid = Piramid();
	Piramid newPiramid2 = Piramid();

	Meshes.push_back(new Mesh(&newPiramid,
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(1.0f)
	));
	Meshes.push_back(new Mesh(&newPiramid,
		glm::vec3(1.0f,1.0f,0.0f),
		glm::vec3(1.0f,0.5f,1.0f),
		glm::vec3(1.0f),
		glm::vec3(1.0f)
	));*/
	//Inicjalizacja modelu

	this->Models.push_back(new Model(
		glm::vec3(3.0f, 0.0f, 0.0f),
		this->Materials[MATERIAL_1],
		this->Textures[TEXTURE_BRICKS0],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"TankHull2.obj"
	));

	this->Models.push_back(new Model(
		glm::vec3(3.0f, 0.0f, 0.0f),
		this->Materials[MATERIAL_1],
		this->Textures[TEXTURE_BRICKS0],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Turret.obj"
	));

	this->Models.push_back(new Model(
		glm::vec3(3.0f, 0.0f, 0.0f),
		this->Materials[MATERIAL_1],
		this->Textures[TEXTURE_BRICKS0],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Tracks.obj"
	));
	
	this->Models.push_back(new Model(
		glm::vec3(-1.0f, 0.636f, 0.422f),
		this->Materials[MATERIAL_1],
		this->Textures[TEXTURE_BRICKS0],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Cannon.obj"
	));

	for (int i = 10; i < 10; i++)	//Doko�czy� zmieni� (int i = 1)
	{
		std::string name = "WheelL" + std::to_string(i) + ".obj";
		std::cout << name << "\n";
		this->Models.push_back(new Model(
			glm::vec3(3.0f, 0.0f, 0.0f),
			this->Materials[MATERIAL_1],
			this->Textures[TEXTURE_BRICKS0],
			this->Textures[TEXTURE_BRICKS_SPEC],
			name.c_str()
		));
	}


	for (auto*& i : Meshes)
		delete i;


}

//Pozycje �wiate�
void Game::InitLights()
{
	//�wiat�o
	this->Lights.push_back(new glm::vec3(0.0f, 0.0f, 1.f));
}

void Game::InitUniforms()
{
	//Inicjalizacja Uniforms
	this->Shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->Shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	//Pozycja �wiat�a
	this->Shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->Lights[0], "lightPos0");
	//this->Shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}

void Game::UpdateUniforms()
{
	//wysy�anie shader�w do karty graficznej
	//this->Shaders[SHADER_CORE_PROGRAM]->set1i(0, "texture0");
	//this->Shaders[SHADER_CORE_PROGRAM]->set1i(1, "texture1");
	//this->Materials[MATERIAL_1]->sendToShader(*this->Shaders[SHADER_CORE_PROGRAM]);

	//Aktualizacja macierzy kamery
	this->ViewMatrix = this->camera.GetViewMatrix();
	
	this->Shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->Shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.GetPosition(), "cameraPos");

	//Pozwala na zmian� wielko�ci okna
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
	GL_VERSION_MINOR(GLVerMin),
	camera(glm::vec3(0.0f,0.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f),glm::vec3(0.0f,1.0f,0.0f))
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
	this->farPlane = 1000.0f;	//Zasi�g rysowania

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

	this->TankSpeed = 0;
	this->TankRotate = 0;
	this->TurretRotate = 0;
	this->CannonRotate = 0;
	this->Rotation = 0;
	this->TurretRotation = 0;

	this->x = 0;
	this->z = 0;


	this->InitGLFW();
	this->InitWindow(title,resizable);
	this->InitGLEW();
	this->InitOpenGLOptions();
	this->InitMatrices();
	this->InitShader();
	this->InitTextures();
	this->InitMaterials();
	this->InitOBJModels();
	this->InitModels();
	this->InitLights();
	this->InitUniforms();
}

Game::~Game()
{
	//Zwalnianie pami�ci
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
	for (size_t i = 0; i < this->Models.size(); i++)
	{
		delete this->Models[i];
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
		this->camera.Move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.Move(this->dt, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.Move(this->dt, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.Move(this->dt, RIGHT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS)
	{
		this->camPosition.y -= 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->camPosition.y += 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		this->TankSpeed = 1.0f;
	}
	else if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		this->TankSpeed = -1.0f;
	}
	else
	{
		this->TankSpeed = 0.0f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		this->TankRotate = 1.0f * dt /3.14*180;
		//this->TurretRotate = TankRotate;
		this->Rotation += 1.0f * dt;
	}
	else if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		this->TankRotate = -1.0f * dt / 3.14 * 180;
		//this->TurretRotate = TankRotate;
		this->Rotation -= 1.0f * dt;
	}
	else
	{
		this->TankRotate = 0.0f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_KP_4) == GLFW_PRESS)
	{
		this->TurretRotate = 1.0f * dt / 3.14 * 180;
		TurretRotation += 1.0f * dt;
	}
	else if (glfwGetKey(this->window, GLFW_KEY_KP_6) == GLFW_PRESS)
	{
		this->TurretRotate = -1.0f * dt / 3.14 * 180;
		TurretRotation -= 1.0f * dt;
	}
	else
	{
		this->TurretRotate = 0.0f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_KP_5) == GLFW_PRESS)
	{
		this->CannonRotate = 1.0f * dt / 3.14 * 180;
		this->CannonRotation += 1.0f * dt;
		this->CannonRotation = glm::clamp(CannonRotation, glm::radians(-30.0f), glm::radians(5.0f));
	}
	else if (glfwGetKey(this->window, GLFW_KEY_KP_8) == GLFW_PRESS)
	{
		this->CannonRotate = -1.0f * dt / 3.14 * 180;
		this->CannonRotation -= 1.0f * dt;
		this->CannonRotation = glm::clamp(CannonRotation, glm::radians(-30.0f),glm::radians(5.0f));
	}
	else
	{
		this->CannonRotate = 0.0f;
	}
	
}

void Game::UpdateMouseInput()
{
	//Pobieranie kursora z okna i zapisanie pozycji w mouseX i mouseY
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);
	
	//Sprawdzenie czy kamera ruszy�a si� pierwszy raz
	if (this->firstMouse)
	{
		//Ustawianie ostatniej pozycji kamery
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	//Liczenie offsetu (zmiany pozycji kamery)
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY; //Y jest odwr�cone
	
	//Ustawienie ostatnich wsp�rz�dnych X i Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

}

void Game::UpdateInput()
{
	//Wyj�cie
	glfwPollEvents();
	this->UpdateKeyboardInput();
	this->UpdateMouseInput();
	this->camera.UpdateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
	
}

void Game::Update()
{
	//Aktualizacja wydarze� (np wy��czanie okna X)
	this->updateDt();
	this->UpdateInput();

	this->x += TankSpeed * dt * -cos(Rotation+PI/2);
	this->z += TankSpeed * dt * sin(Rotation + PI/2);
	std::cout << Rotation << "\n";

	glm::mat4 CannonMatrix = glm::mat4(1.0f);
	CannonMatrix = glm::translate(CannonMatrix, glm::vec3(x, 0.0f, z));
	CannonMatrix = glm::rotate(CannonMatrix, Rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	CannonMatrix = glm::translate(CannonMatrix, glm::vec3(0.0f, 0.636f, 0.0f));
	CannonMatrix = glm::rotate(CannonMatrix, TurretRotation, glm::vec3(0.0f, 1.0f, 0.0f));
	CannonMatrix = glm::translate(CannonMatrix, glm::vec3(0.0f, 0.0f, 0.422f));
	CannonMatrix = glm::rotate(CannonMatrix, CannonRotation, glm::vec3(1.0f, 0.0f, 0.0f));
	//this->Models[TANK_CANNON]->Rotate(glm::vec3(1.0f, 0.0f, 0.0f));
	// glm::vec3(4.0f, -0.636f, -0.422f)
	//Set TankPosition
	this->Models[TANK_HULL]->SetPosition(glm::vec3(x, 0.0f, z));
	this->Models[TANK_TURRET]->SetPosition(glm::vec3(x, 0.0f, z));
	this->Models[TANK_TRACKS]->SetPosition(glm::vec3(x, 0.0f, z));
	this->Models[TANK_CANNON]->SetMatrix(CannonMatrix);

	//this->Models[TANK_CANNON]->SetPosition(glm::vec3(x +0.422f * -cos(Rotation + PI / 2), 0.636f, z + 0.422f * sin(Rotation + PI / 2)));
	//Set TankRotation
	this->Models[TANK_HULL]->Rotate(glm::vec3(0.0f, TankRotate, 0.0f));
	this->Models[TANK_TURRET]->Rotate(glm::vec3(0.0f, TankRotate, 0.0f));
	this->Models[TANK_TRACKS]->Rotate(glm::vec3(0.0f, TankRotate, 0.0f));
	//this->Models[TANK_CANNON]->Rotate(glm::vec3(0.0f, TankRotate + TurretRotate, 0.0f));
	//Rotation of Turret
	this->Models[TANK_TURRET]->Rotate(glm::vec3(0.0f, TurretRotate, 0.0f));
	//this->Models[TANK_CANNON]->Rotate(glm::vec3(0.0f, TurretRotate, 0.0f));

	//this->Models[TANK_HULL]->Move(glm::vec3(0.0f, 0.0f, TankSpeed * 1.0f * dt));
	//this->Models[TANK_HULL]->SetPosition(glm::vec3(x, 0.0f, z));
	//this->Models[TANK_HULL]->Move(glm::vec3(TankSpeed * dt * cos(Rotation), 0.0f, -TankSpeed * dt * sin(Rotation)));
	//this->Models[TANK_HULL]->Rotate(glm::vec3(0.0f, TankRotate*Rotation, 0.0f));
	//this->Models[TANK_HULL]->Move(glm::vec3(0.0f, 0.0f, TankSpeed * dt * 1.0f));
	//this->Models[TANK_TURRET]->Move(glm::vec3(0.0f, 0.0f, TankSpeed * dt * 1.0f));
	//this->Models[TANK_TURRET]->Rotate(glm::vec3(0.0f, 0.4f, 0.0f));
	//this->Models[0]->Rotate(glm::vec3(0.0f, 0.1f, 0.0f));
	//this->Models[1]->Rotate(glm::vec3(0.1f, 0.0f, 0.0f));
	//this->Models[2]->Rotate(glm::vec3(0.0f, -0.1f, 0.0f));
}

void Game::Render()
{

	//Aktualizowanie (Update)
	//updateInput(window);
	
	//updateInput(window, *this->Meshes[MESH_QUAD]);

	//Czyszczenie ekranu i bufor�w
	glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Aktualizowanie uniform�w (wysy�anie do karty graficznej
	this->UpdateUniforms();

	//Renderowanie modeli
	for (auto& i : this->Models)
	{
		i->Render(this->Shaders[SHADER_CORE_PROGRAM]);
	}

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