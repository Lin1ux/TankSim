#pragma once

#include "libs.h"

//ENUMS
enum shader_enums {SHADER_CORE_PROGRAM = 0};
enum texture_enums {TEXTURE_BRICKS0 = 0, TEXTURE_BRICKS_SPEC,TEX_TRACKL, TEX_TRACKR,TEX_HULLTANK,
	TEX_FRONT_WHEEL, TEX_SINGLE_WHEEL, TEX_DOUBLE_WHEEL, TEX_BACK_WHEEL,
	TEX_DIRT};
enum material_enums {MATERIAL_1 = 0};
enum mesh_enums {MESH_QUAD = 0};
enum tank_parts {TANK_HULL = 0,TANK_TURRET,TANK_TRACKL, TANK_TRACKR,TANK_CANNON,
	LFRONT_WHEEL,LWHEEL2,LWHEEL3, LWHEEL4, LWHEEL5, LWHEEL6, LWHEEL7, LWHEEL8, LWHEEL9,LBACK_WHEEL,
	RFRONT_WHEEL,RWHEEL2, RWHEEL3, RWHEEL4, RWHEEL5, RWHEEL6, RWHEEL7, RWHEEL8, RWHEEL9, RBACK_WHEEL
};

class Game
{
private:
	//Okno
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int frameBufferWidth;
	int frameBufferHeight;
	//Open GL Kontekst
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Delta time
	float dt;
	float curTime;
	float lastTime;

	//Wejœcie Myszki
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	float TankSpeed;
	float TankRotate;
	float TurretRotate;
	float CannonRotate;

	float x;
	float z;

	float Rotation;
	float TurretRotation;
	float CannonRotation;
	float LeftWheels;
	float RightWheels;

	std::vector<glm::vec3> WheelOffsets;

	//Kamera
	Camera camera;

	//Macierze
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float FOV;
	float nearPlane;
	float farPlane;

	//Shadery
	std::vector<shader*> Shaders;
	//Tekstury
	std::vector<Texture*> Textures;
	//Materia³y
	std::vector<Material*> Materials;
	//Modele
	std::vector<Model*> Models;
	//Œwiat³a
	std::vector<glm::vec3*> Lights;

	void InitGLFW();
	void InitWindow(const char* title, bool resizable);
	void InitGLEW();	//po stworzeniu kontekstu
	void InitOpenGLOptions();
	void InitMatrices();
	void InitShader();
	void InitTextures();
	void InitMaterials();
	void InitOBJModels();
	void InitModels();
	void InitLights();
	void InitUniforms();

	void UpdateUniforms();

	//Funkcje

public:
	Game(const char* title,
		const int width, const int height,
		const int GLVerMaj, const int GLVerMin,
		bool resizable);
	virtual ~Game();

	int getWindowShouldClose();

	void setWindowShouldClose();

	void updateDt();
	void UpdateKeyboardInput();
	void UpdateMouseInput();
	void UpdateInput();
	void Update();
	void Render();


	static void FrameBufferResize(GLFWwindow* window, int fbW, int fbH);
	//static void updateInput(GLFWwindow* window);
	//static void updateInput(GLFWwindow* window, Mesh& mesh);
};

