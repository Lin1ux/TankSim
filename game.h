#pragma once

#include "libs.h"

//ENUMS
enum shader_enums {SHADER_CORE_PROGRAM = 0};
enum texture_enums {TEXTURE_BRICKS0 = 0, TEXTURE_STONE1};
enum material_enums {MATERIAL_1 = 0};
enum mesh_enums {MESH_QUAD = 0};

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
	//Materials
	std::vector<Material*> Materials;
	//Meshes
	std::vector<Mesh*> Meshes;
	//Œwiat³¹
	std::vector<glm::vec3*> Lights;

	void InitGLFW();
	void InitWindow(const char* title, bool resizable);
	void InitGLEW();	//po stworzeniu kontekstu
	void InitOpenGLOptions();
	void InitMatrices();
	void InitShader();
	void InitTextures();
	void InitMaterials();
	void InitMeshes();
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

	void Update();
	void Render();


	static void FrameBufferResize(GLFWwindow* window, int fbW, int fbH);
	static void updateInput(GLFWwindow* window);
	static void updateInput(GLFWwindow* window, Mesh& mesh);
};

