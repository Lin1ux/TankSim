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

	//glEnable(GL_CULL_FACE);	//Usuwa nie potrzebne rzeczy
	//glCullFace(GL_FRONT);	//Usuwa ty³
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
	this->Textures.push_back(new Texture ("Textures/TrackL.png", GL_TEXTURE_2D));

	this->Textures.push_back(new Texture("Textures/TrackR.png", GL_TEXTURE_2D));

	this->Textures.push_back(new Texture("Textures/HullTank3.png", GL_TEXTURE_2D));

	this->Textures.push_back(new Texture("Textures/Turret.png", GL_TEXTURE_2D));

	this->Textures.push_back(new Texture("Textures/Cannon2.png", GL_TEXTURE_2D));

	this->Textures.push_back(new Texture("Textures/FrontWheel.png", GL_TEXTURE_2D));

	this->Textures.push_back(new Texture("Textures/SingleWheel.png", GL_TEXTURE_2D));

	this->Textures.push_back(new Texture("Textures/DoubleWheel.png", GL_TEXTURE_2D));

	this->Textures.push_back(new Texture("Textures/BackWheel.png", GL_TEXTURE_2D));
	
	this->Textures.push_back(new Texture("Textures/Bullet.png", GL_TEXTURE_2D));

	this->Textures.push_back(new Texture("Textures/Dirt.png", GL_TEXTURE_2D));

	this->Textures.push_back(new Texture("Textures/Particle.png", GL_TEXTURE_2D));

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

	std::vector<Vertex> DirtVertex = OBJModel::loadOBJ("Models/cube.obj");
	std::vector<Mesh*> Dirt;
	std::vector<Vertex> ParticleVertex = OBJModel::loadOBJ("Models/Particle.obj");
	std::vector<Mesh*> Particle;

	Dirt.push_back(new Mesh(DirtVertex.data(), DirtVertex.size(), NULL, 0, glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(1.0f)
	));

	Particle.push_back(new Mesh(ParticleVertex.data(), ParticleVertex.size(), NULL, 0, glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(1.0f)
	));
	//Inicjalizacja modelu

	this->Models.push_back(new Model(
		glm::vec3(3.0f, 0.0f, 0.0f),
		this->Materials[MATERIAL_1],
		this->Textures[TEX_HULLTANK],
		this->Textures[0],
		"Models/Tank3.obj"
	));

	this->Models.push_back(new Model(
		glm::vec3(3.0f, 0.0f, 0.0f),
		this->Materials[MATERIAL_1],
		this->Textures[TEX_TURRET],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Models/Turret.obj"
	));

	this->Models.push_back(new Model(
		glm::vec3(3.0f, 0.0f, 0.0f),
		this->Materials[MATERIAL_1],
		this->Textures[TEX_TRACKL],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Models/LTrack.obj"
	));

	this->Models.push_back(new Model(
		glm::vec3(3.0f, 0.0f, 0.0f),
		this->Materials[MATERIAL_1],
		this->Textures[TEX_TRACKR],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Models/RTrack.obj"
	));
	
	this->Models.push_back(new Model(
		glm::vec3(-1.0f, 0.636f, 0.422f),
		this->Materials[MATERIAL_1],
		this->Textures[TEX_CANNON],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Models/Cannon2.obj"
	));

	//Lewe ko³a
	this->Models.push_back(new Model(
		glm::vec3(-0.41f, 0.0f, 1.374f),
		this->Materials[MATERIAL_1],
		this->Textures[TEX_FRONT_WHEEL],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Models/FrontWheel.obj"
	));
	for (int i = 0; i < 4; i++)
	{
		this->Models.push_back(new Model(
			glm::vec3(0.5 * i, 0.0f, 1.374f),
			this->Materials[MATERIAL_1],
			this->Textures[TEX_SINGLE_WHEEL],
			this->Textures[TEXTURE_BRICKS_SPEC],
			"Models/SingleWheel.obj"
		));
		this->Models.push_back(new Model(
			glm::vec3(-0.5f * i, 0.5f, 1.374f),
			this->Materials[MATERIAL_1],
			this->Textures[TEX_DOUBLE_WHEEL],
			this->Textures[TEXTURE_BRICKS_SPEC],
			"Models/DoubleWheel.obj"
		));
	}

	this->Models.push_back(new Model(
		glm::vec3(0.41f, 0.0f, 1.374f),
		this->Materials[MATERIAL_1],
		this->Textures[TEX_BACK_WHEEL],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Models/BackWheel.obj"
	));
	//Prawe ko³a
	this->Models.push_back(new Model(
		glm::vec3(-0.41f, 0.0f, 1.374f),
		this->Materials[MATERIAL_1],
		this->Textures[TEX_FRONT_WHEEL],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Models/FrontWheel.obj"
	));
	for (int i = 0; i < 4; i++)
	{
		this->Models.push_back(new Model(
			glm::vec3(0.5 * i, 0.0f, 1.374f),
			this->Materials[MATERIAL_1],
			this->Textures[TEX_SINGLE_WHEEL],
			this->Textures[TEXTURE_BRICKS_SPEC],
			"Models/SingleWheel.obj"
		));
		this->Models.push_back(new Model(
			glm::vec3(-0.5f * i, 0.5f, 1.374f),
			this->Materials[MATERIAL_1],
			this->Textures[TEX_DOUBLE_WHEEL],
			this->Textures[TEXTURE_BRICKS_SPEC],
			"Models/DoubleWheel.obj"
		));
	}

	this->Models.push_back(new Model(
		glm::vec3(0.41f, 0.0f, 1.374f),
		this->Materials[MATERIAL_1],
		this->Textures[TEX_BACK_WHEEL],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Models/BackWheel.obj"
	));

	this->Models.push_back(new Model(
		glm::vec3(1.0f, 0.0f, 0.0f),
		this->Materials[MATERIAL_1],
		this->Textures[TEX_BULLET],
		this->Textures[TEXTURE_BRICKS_SPEC],
		"Models/Bullet.obj"
	));
	//Dirt
	for (int i = -15; i < 15; i++)
	{
		for (int j = -15; j < 15; j++)
		{
			this->Models.push_back(new Model(
				glm::vec3(i * 2.0f, -1.4f, j*2.0f),
				this->Materials[MATERIAL_1],
				this->Textures[TEX_DIRT],
				this->Textures[TEXTURE_BRICKS_SPEC],
				Dirt
			));
		}
	}
	//Cz¹steczki
	for (int i = 0; i < 1000; i++)
	{
		this->Particles.push_back(new Model(
			glm::vec3(2.0f, 1.4f, 2.0f),
			this->Materials[MATERIAL_1],
			this->Textures[TEX_PARTICLE],
			this->Textures[TEXTURE_BRICKS_SPEC],
			Particle
		));
	}

	std::cout << "Load\n";

	for (auto*& i : Meshes)
		delete i;


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
	//this->Shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}

void Game::SetParticles(glm::mat4 matrix)
{
	for (int i = 0; i < Particles.size(); i++)
	{
		this->ParticlesMatrices[i] = matrix;
		this->ParticlesMatrices[i] = glm::scale(this->ParticlesMatrices[i], glm::vec3((float)Game::Random(10, 20) / 1000, (float)Game::Random(10, 20) / 1000, (float)Game::Random(10, 20) / 1000));
		this->ParticlesMatrices[i] = glm::translate(this->ParticlesMatrices[i], ParticleOffset[i]);
		this->ParticlesMatrices[i] = glm::rotate(ParticlesMatrices[i], glm::radians(ParticleRotationY[i]), glm::vec3(0.0f, 1.0f, 0.0f));
		this->ParticlesMatrices[i] = glm::rotate(ParticlesMatrices[i], glm::radians(ParticleRotationX[i]), glm::vec3(1.0f, 0.0f, 0.0f));
		this->ParticleRotation[i] = ParticleRotationX[i];
		this->Particles[i]->SetMatrix(this->ParticlesMatrices[i]);
	}
	this->explode = true;
}

void Game::UpdateUniforms()
{
	//wysy³anie shaderów do karty graficznej
	//this->Shaders[SHADER_CORE_PROGRAM]->set1i(0, "texture0");
	//this->Shaders[SHADER_CORE_PROGRAM]->set1i(1, "texture1");
	//this->Materials[MATERIAL_1]->sendToShader(*this->Shaders[SHADER_CORE_PROGRAM]);

	//Aktualizacja macierzy kamery
	this->ViewMatrix = this->camera.GetViewMatrix();
	
	this->Shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->Shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.GetPosition(), "cameraPos");

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

void Game::UpdateParticles()
{
	Particle_speed.clear();
	ParticleOffset.clear();
	ParticleRotationY.clear();
	ParticleRotationX.clear();
	ParticleRotation.clear();
	for (size_t i = 0; i < Particles.size(); i++)
	{
		this->Particle_speed.push_back(Game::Random(10, 30));
		std::cout << Particle_speed[i] << " ";
	}
	for (size_t i = 0; i < Particles.size(); i++)
	{
		this->ParticleOffset.push_back(glm::vec3( (float) Game::Random(10, 30)/10, (float) Game::Random(10, 30) / 10, (float) Game::Random(10, 30) / 10));
	}
	for (size_t i = 0; i < Particles.size(); i++)
	{
		this->ParticleOffset.push_back(glm::vec3((float)Game::Random(10, 30) / 10, (float)Game::Random(10, 30) / 10, (float)Game::Random(10, 30) / 10));
	}
	for (size_t i = 0; i < Particles.size(); i++)
	{
		this->ParticleRotationY.push_back(Game::Random(0, 360));
	}
	for (size_t i = 0; i < Particles.size(); i++)
	{
		this->ParticleRotationX.push_back(Game::Random(0, 75));
	}
	for (size_t i = 0; i < Particles.size(); i++)
	{
		this->ParticleRotation.push_back(0.0f);
	}
	std::cout<<"\n";
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
	this->farPlane = 1000.0f;	//Zasiêg rysowania

	this->dt = 0.0f;
	this->curTime = 0.0f;
	this->lastTime = 0.0f;
	this->gameSpeed = 1.0f;

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
	this->LeftWheels = 0;
	this->RightWheels = 0;
	//Offsety kó³
	this->WheelOffsets = std::vector<glm::vec3>();

	WheelOffsets.push_back(glm::vec3(0.58f, 0.0f, 1.374f));		//Przednie Lewe ko³o
	WheelOffsets.push_back(glm::vec3(0.58f, -0.121f, 1.04f));	//Lewe Ko³o 2
	WheelOffsets.push_back(glm::vec3(0.58f, -0.121f, 0.78f));	//Lewe Ko³o 3
	WheelOffsets.push_back(glm::vec3(0.58f, -0.121f, 0.52f));	//Lewe Ko³o 4
	WheelOffsets.push_back(glm::vec3(0.58f, -0.121f, 0.25f));	//Lewe Ko³o 5
	WheelOffsets.push_back(glm::vec3(0.58f, -0.121f, 0.0f));	//Lewe Ko³o 6
	WheelOffsets.push_back(glm::vec3(0.58f, -0.121f, -0.25f));	//Lewe Ko³o 7
	WheelOffsets.push_back(glm::vec3(0.58f, -0.121f, -0.52f));	//Lewe Ko³o 8
	WheelOffsets.push_back(glm::vec3(0.58f, -0.121f, -0.78f));	//Lewe Ko³o 9
	WheelOffsets.push_back(glm::vec3(0.58f, -0.0f, -1.04f));	//Lewe Ko³o 9

	WheelOffsets.push_back(glm::vec3(-0.52f, 0.0f, 1.374f));	//Przednie Prawe ko³o
	WheelOffsets.push_back(glm::vec3(-0.52f, -0.121f, 1.04f));	//Prawe Ko³o 2
	WheelOffsets.push_back(glm::vec3(-0.52f, -0.121f, 0.78f));	//Prawe Ko³o 3
	WheelOffsets.push_back(glm::vec3(-0.52f, -0.121f, 0.52f));	//Prawe Ko³o 4
	WheelOffsets.push_back(glm::vec3(-0.52f, -0.121f, 0.25f));	//Prawe Ko³o 5
	WheelOffsets.push_back(glm::vec3(-0.52f, -0.121f, 0.0f));	//Prawe Ko³o 6
	WheelOffsets.push_back(glm::vec3(-0.52f, -0.121f, -0.25f));	//Prawe Ko³o 7
	WheelOffsets.push_back(glm::vec3(-0.52f, -0.121f, -0.52f));	//Prawe Ko³o 8
	WheelOffsets.push_back(glm::vec3(-0.52f, -0.121f, -0.78f));	//Prawe Ko³o 9
	WheelOffsets.push_back(glm::vec3(-0.52f, -0.0f, -1.04f));	//Prawe Ko³o 9

	//Macierze
	this->BulletMatrix = glm::mat4(1.0f);
	this->CannonMatrix = glm::mat4(1.0f);

	this->fire = false;
	this->explode = false;
	this->CannonCooldown = 0.0f;

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

	//Cz¹steczki
	this->UpdateParticles();
	for (size_t i = 0; i < this->Particles.size() ;i++)
	{
		this->ParticlesMatrices.push_back(glm::mat4(1.0f));
	}
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
	this->dt*= gameSpeed;
	this->lastTime = this->curTime;
	if (CannonCooldown < 10)
	{
		CannonCooldown += dt;
	}
	
}

void Game::UpdateKeyboardInput()
{
	//Wy³¹czenie programu
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	//Kamera
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camera.Move(this->dt/gameSpeed, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.Move(this->dt / gameSpeed, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.Move(this->dt / gameSpeed, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.Move(this->dt / gameSpeed, RIGHT);
	}
	//Jazda do przodu
	if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		this->TankSpeed = 2.0f;
		this->LeftWheels += TANK_MAX_SPEED * dt;
		this->RightWheels -= TANK_MAX_SPEED * dt;
	}
	//Jazda do ty³u
	else if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		this->TankSpeed = -2.0f;
		this->LeftWheels -= TANK_MAX_SPEED * dt;
		this->RightWheels += TANK_MAX_SPEED * dt;
	}
	//Zatrzymanie
	else
	{
		this->TankSpeed = 0.0f;
	}
	//Obrót w lewo
	if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		this->TankRotate = 1.0f * dt /3.14*180;
		this->Rotation += 1.0f * dt;
		this->LeftWheels -= TANK_MAX_SPEED * dt;
		this->RightWheels -= TANK_MAX_SPEED * dt;
	}
	//Obrót w prawo
	else if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		this->TankRotate = -1.0f * dt / 3.14 * 180;
		this->Rotation -= 1.0f * dt;
		this->LeftWheels += TANK_MAX_SPEED * dt;
		this->RightWheels += TANK_MAX_SPEED * dt;
	}
	else
	{
		this->TankRotate = 0.0f;
	}
	//Obrót wie¿y w lewo
	if (glfwGetKey(this->window, GLFW_KEY_KP_4) == GLFW_PRESS)
	{
		this->TurretRotate = 1.0f * dt / 3.14 * 180;
		TurretRotation += 1.0f * dt;
	}
	//Obrót wie¿y w prawo
	else if (glfwGetKey(this->window, GLFW_KEY_KP_6) == GLFW_PRESS)
	{
		this->TurretRotate = -1.0f * dt / 3.14 * 180;
		TurretRotation -= 1.0f * dt;
	}
	else
	{
		this->TurretRotate = 0.0f;
	}
	//Opuszczenie lufy
	if (glfwGetKey(this->window, GLFW_KEY_KP_5) == GLFW_PRESS)
	{
		this->CannonRotate = 1.0f * dt / 3.14 * 180;
		this->CannonRotation += 1.0f * dt;
		this->CannonRotation = glm::clamp(CannonRotation, glm::radians(-30.0f), glm::radians(5.0f));
	}
	//Podnoszenie lufy
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
	//Strza³ 
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (CannonCooldown > CANNON_RELOAD)	//Dzia³o wymaga czasu do prze³adowania
		{
			this->CannonCooldown = 0;
			this->BulletMatrix = this->CannonMatrix;
			this->BulletMatrix = glm::rotate(this->BulletMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			this->BulletMatrix = glm::scale(this->BulletMatrix, glm::vec3(0.25f, 0.25f, 0.25f));
			this->BulletMatrix = glm::translate(this->BulletMatrix, glm::vec3(-8.0f, 0.0f, 0.0f));
			this->Models[BULLET]->SetMatrix(this->BulletMatrix);
			this->fire = true;
		}
	}
	//Do testowania cz¹steczek (tworzy cz¹steczki na œrodku mapy)
	if (glfwGetKey(this->window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		SetParticles(glm::mat4(1.0f));
	}
	//Prêdkoœæ Gry
	if (glfwGetKey(this->window, GLFW_KEY_1) == GLFW_PRESS)
	{
		this->gameSpeed = 1.0f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_2) == GLFW_PRESS)
	{
		this->gameSpeed = 2.0f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_3) == GLFW_PRESS)
	{
		this->gameSpeed = 0.25f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_4) == GLFW_PRESS)
	{
		this->gameSpeed = 0.1f;
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
	this->camera.UpdateInput(dt/gameSpeed, -1, this->mouseOffsetX, this->mouseOffsetY);
	
}

void Game::Update()
{
	//Aktualizacja wydarzeñ (np wy³¹czanie okna X)
	this->updateDt();
	this->UpdateInput();

	this->x += TankSpeed * dt * -cos(Rotation+PI/2);
	this->z += TankSpeed * dt * sin(Rotation + PI/2);

	//Dzia³o
	this->CannonMatrix = glm::mat4(1.0f);
	this->CannonMatrix = glm::translate(this->CannonMatrix, glm::vec3(x, 0.0f, z));
	this->CannonMatrix = glm::rotate(this->CannonMatrix, Rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	this->CannonMatrix = glm::translate(this->CannonMatrix, glm::vec3(0.0f, 0.636f, 0.0f));
	this->CannonMatrix = glm::rotate(this->CannonMatrix, TurretRotation, glm::vec3(0.0f, 1.0f, 0.0f));
	this->CannonMatrix = glm::translate(this->CannonMatrix, glm::vec3(0.0f, 0.0f, 0.422f));
	this->CannonMatrix = glm::rotate(this->CannonMatrix, CannonRotation, glm::vec3(1.0f, 0.0f, 0.0f));
	this->Models[TANK_CANNON]->SetMatrix(this->CannonMatrix);
	//Pocisk
	if (fire)
	{
		this->BulletMatrix = glm::rotate(this->BulletMatrix, glm::radians(10.0f * dt), glm::vec3(0.0f, 0.0f, 1.0f));
		this->BulletMatrix = glm::translate(this->BulletMatrix, glm::vec3(-BULLET_SPEED * dt, 0.0f, 0.0f));
		if (BulletMatrix[3].y < -0.5)
		{
			fire = false;
			glm::mat4 ScaledBulletMatrix = BulletMatrix;
			ScaledBulletMatrix = glm::scale(ScaledBulletMatrix, glm::vec3(4.0f,4.0f,4.0f));
			SetParticles(ScaledBulletMatrix);
		}
	}
	else
	{
		this->BulletMatrix=this->CannonMatrix;
		this->BulletMatrix = glm::rotate(this->BulletMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		this->BulletMatrix = glm::scale(this->BulletMatrix, glm::vec3(0.25f, 0.25f, 0.25f));
	}
	this->Models[BULLET]->SetMatrix(this->BulletMatrix);
	//Set TankPosition
	
	//Ko³a
	glm::mat4 Wheel = glm::mat4(1.0f);
	for (int i = 0; i < WheelOffsets.size(); i++)
	{
		Wheel = glm::mat4(1.0f);
		Wheel = glm::translate(Wheel, glm::vec3(x, 0.0f, z));
		Wheel = glm::rotate(Wheel, Rotation, glm::vec3(0.0f, 1.0f, 0.0f));
		Wheel = glm::translate(Wheel, WheelOffsets[i]);
		if (i < 10)
		{
			Wheel = glm::rotate(Wheel, LeftWheels, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else
		{
			Wheel = glm::rotate(Wheel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			Wheel = glm::rotate(Wheel, RightWheels, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		this->Models[LFRONT_WHEEL + i]->SetMatrix(Wheel);
	}

	//Inne Czêœci
	this->Models[TANK_HULL]->SetPosition(glm::vec3(x, 0.0f, z));
	this->Models[TANK_TURRET]->SetPosition(glm::vec3(x, 0.0f, z));
	this->Models[TANK_TRACKL]->SetPosition(glm::vec3(x, 0.0f, z));
	this->Models[TANK_TRACKR]->SetPosition(glm::vec3(x, 0.0f, z));
	this->Models[TANK_HULL]->Rotate(glm::vec3(0.0f, TankRotate, 0.0f));
	this->Models[TANK_TURRET]->Rotate(glm::vec3(0.0f, TankRotate, 0.0f));
	this->Models[TANK_TRACKL]->Rotate(glm::vec3(0.0f, TankRotate, 0.0f));
	this->Models[TANK_TRACKR]->Rotate(glm::vec3(0.0f, TankRotate, 0.0f));
	//Rotation of Turret
	this->Models[TANK_TURRET]->Rotate(glm::vec3(0.0f, TurretRotate, 0.0f));

	//Cz¹steczki
	for (size_t i = 0; i < Particles.size(); i++)
	{
		this->ParticlesMatrices[i] = glm::translate(ParticlesMatrices[i], glm::vec3(0.0f, PARTICLE_SPEED *dt,0.0f));
		if (this->ParticleRotation[i] < 140)
		{
			this->ParticlesMatrices[i] = glm::rotate(ParticlesMatrices[i],glm::radians(PARTICLE_ROTATION_SPEED * dt), glm::vec3(1.0f, 0.0f, 0.0f));
			this->ParticleRotation[i] += PARTICLE_ROTATION_SPEED * dt;
			this->ParticleRotation[i] = glm::clamp(ParticleRotation[i], glm::radians(0.0f), glm::radians(140.0f));
		}
		if (ParticlesMatrices[i][3].y < -0.5f)
		{
			this->ParticlesMatrices[i] = glm::scale(ParticlesMatrices[i], glm::vec3(0.0f, 0.0f, 0.0f));
		}
		this->Particles[i]->SetMatrix(ParticlesMatrices[i]);
	}
}

void Game::Render()
{

	//Aktualizowanie (Update)
	//updateInput(window);
	
	//updateInput(window, *this->Meshes[MESH_QUAD]);

	//Czyszczenie ekranu i buforów
	glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Aktualizowanie uniformów (wysy³anie do karty graficznej
	this->UpdateUniforms();

	//Renderowanie modeli
	for (auto& i : this->Models)
	{
		i->Render(this->Shaders[SHADER_CORE_PROGRAM]);
	}
	for (auto& i : this->Particles)
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

int Game::Random(int min, int max)
{
	max += 1;
	return rand() % (max - min) + min;
}