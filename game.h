#pragma once

#include "libs.h"

//ENUMS
enum shader_enums {SHADER_CORE_PROGRAM = 0};
enum texture_enums {TEXTURE_BRICKS0 = 0, TEXTURE_BRICKS_SPEC,TEX_TRACKL, TEX_TRACKR,TEX_HULLTANK,TEX_TURRET,TEX_CANNON,
	TEX_FRONT_WHEEL, TEX_SINGLE_WHEEL, TEX_DOUBLE_WHEEL, TEX_BACK_WHEEL,TEX_BULLET,
	TEX_DIRT,TEX_PARTICLE};
enum material_enums {MATERIAL_1 = 0};
enum mesh_enums {MESH_QUAD = 0};
enum tank_parts {TANK_HULL = 0,TANK_TURRET,TANK_TRACKL, TANK_TRACKR,TANK_CANNON,
	LFRONT_WHEEL,LWHEEL2,LWHEEL3, LWHEEL4, LWHEEL5, LWHEEL6, LWHEEL7, LWHEEL8, LWHEEL9,LBACK_WHEEL,
	RFRONT_WHEEL,RWHEEL2, RWHEEL3, RWHEEL4, RWHEEL5, RWHEEL6, RWHEEL7, RWHEEL8, RWHEEL9, RBACK_WHEEL,
	BULLET
};


class Game
{
private:
	//Okno
	GLFWwindow* window;							//Okno gry
	const int WINDOW_WIDTH;						//Szeroko�� okna
	const int WINDOW_HEIGHT;					//Wysoko�� okna
	int frameBufferWidth;						//Buffor szeroko�ci (pozwala na poprawn� zmian� wymiar�w w trakcie dzia�ania programu
	int frameBufferHeight;						//Buffor Wysoko�ci (pozwala na poprawn� zmian� wymiar�w w trakcie dzia�ania programu
	//Open GL Kontekst
	const int GL_VERSION_MAJOR;					//Wersja OpenGL X.0 - X to g��wna cz��
	const int GL_VERSION_MINOR;					//Wersja OpenGL 0.X - X to mniej wa�na cz��

	//Delta time
	float dt;									//Delta time (naprawia problem r�nych pr�dko��i dzia�ania programu na r�nych urz�dzeniach)
	float curTime;								//Obecny czas
	float lastTime;								//Ostatni zmierzony czas
	float gameSpeed;							//Pr�dko�� gry

	//Wej�cie Myszki
	double lastMouseX;							//Ostatnia wsp�rz�dna myszy X
	double lastMouseY;							//Ostatnia wsp�rz�dna myszy X
	double mouseX;								//Pozycja Myszy X
	double mouseY;								//Pozycja Myszy Y
	double mouseOffsetX;						//Offset myszy X (nwm jak jest offset po Polsku :D)
	double mouseOffsetY;						//Offset myszy X (nwm jak jest offset po Polsku :D)
	bool firstMouse;							//Pierwszy ruch myszy po nie ruszaniu jej

	//Parametry czo�gu
	float TankSpeed;							//Aktualna pr�dko�� czo�gu
	float TankRotate;							//Aktualna pr�dko�c rotacji czo�gu
	float TurretRotate;							//Aktualna pr�dko�c rotacji wie�y
	float CannonRotate;							//Aktualna pr�dko�� podnoszenia/opuszczania lufy
	
	//Macierze
	glm::mat4 BulletMatrix;						//Macierz Pocisku
	glm::mat4 CannonMatrix;						//Macierz Dzia�a

	//Flagi
	bool fire;									//Strza� - s�u�y do ustawiania pozycji startowej pocisku
	bool explode;								//Wybuch - s�u�y do ustawiania pozycji startowej wybuchu

	float CannonCooldown;						//�adowanie dzia�a

	//Pozycja czo�gu
	float x;									//Pozycja X czo�gu
	float z;									//Pozycja Y czo�gu
	//Elementy czo�gu
	float Rotation;								//Obecny obr�t czo�gu
	float TurretRotation;						//Obecny obr�t wie�y
	float CannonRotation;						//Obecny obr�t lufy
	float LeftWheels;							//Obecny obr�t lewych k�
	float RightWheels;							//Obecny obr�t prawych k�
	float BulletRotation;						//Obecny obr�t pocisku (pozwala na lot po paraboli)
	//Offset k�
	std::vector<glm::vec3> WheelOffsets;		//Offset k�

	//Kamera
	Camera camera;								//Obiekt kamery

	//Macierze
	glm::mat4 ViewMatrix;						//Macierz widoku kamery (V)
	glm::vec3 camPosition;						//Pozycja kamery
	glm::vec3 worldUp;							//
	glm::vec3 camFront;							//Prz�d kamery

	glm::mat4 ProjectionMatrix;					//Macierz perspektywy (P)
	float FOV;									
	float nearPlane;	
	float farPlane;

	//Shadery
	std::vector<shader*> Shaders;
	//Tekstury
	std::vector<Texture*> Textures;
	//Materia�y
	std::vector<Material*> Materials;
	//Modele
	std::vector<Model*> Models;
	//Cz�steczki
	std::vector<Model*> Particles;				//Modele cz�steczek
	std::vector<glm::mat4> ParticlesMatrices;	//Macierze cz�steczek
	std::vector<int> Particle_speed;			//Pr�dko�� cz�steczek
	std::vector<glm::vec3> ParticleOffset;		//Offset cz�steczek
	std::vector<float> ParticleRotation;		//Obecny obr�t cz�steczki
	std::vector<float> ParticleRotationY;		//Startowy obr�t cz�steczki Y
	std::vector<float> ParticleRotationX;		//Startowy obr�t cz�steczki X

	//std::vector<int> Particle_speed;
	//�wiat�a
	std::vector<glm::vec3*> Lights;				//�wiat�o

	//Inicjalizacje
	void InitGLFW();
	void InitWindow(const char* title, bool resizable);
	void InitGLEW();				//po stworzeniu kontekstu
	void InitOpenGLOptions();
	void InitMatrices();
	void InitShader();
	void InitTextures();
	void InitMaterials();
	void InitOBJModels();
	void InitModels();
	void InitLights();
	void InitUniforms();

	//Ustawia pozycj� startow� cz�steczek
	void SetParticles(glm::mat4 matrix);
	//Aktualizuje Uniformy do shadera
	void UpdateUniforms();
	//Aktualizuje parametry startowe cz�steczek
	void UpdateParticles();

	//Funkcje

public:
	Game(const char* title,
		const int width, const int height,
		const int GLVerMaj, const int GLVerMin,
		bool resizable);
	virtual ~Game();

	
	int getWindowShouldClose();		//Sprawdza czy okno gry powinno zosta� zamkni�te
	
	void setWindowShouldClose();	//Zamyka program

	void updateDt();				//Aktualizuje rzeczy zwi�zane z delta time
	void UpdateKeyboardInput();		//Uruchamia rzeczy zwi�zane z klawiszami klawiatury
	void UpdateMouseInput();		//Aktualizuje ruch wzgl�dem myszki
	void UpdateInput();				//Aktualizacja urz�dze� wej�ciowych
	void Update();					//Aktualizacja gry - g��wna cz�� gry gdzie obiekty si� ruszaj� itd.
	void Render();					//Wy�wietlanie zmian
 


	static void FrameBufferResize(GLFWwindow* window, int fbW, int fbH);	//Pozwala na poprawn� zmian� wymiar�w okna
	static int Random(int min, int max);									//Losuje losow� liczb� z zakresu [min max]
};

