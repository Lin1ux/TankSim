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
	const int WINDOW_WIDTH;						//Szerokoœæ okna
	const int WINDOW_HEIGHT;					//Wysokoœæ okna
	int frameBufferWidth;						//Buffor szerokoœci (pozwala na poprawn¹ zmianê wymiarów w trakcie dzia³ania programu
	int frameBufferHeight;						//Buffor Wysokoœci (pozwala na poprawn¹ zmianê wymiarów w trakcie dzia³ania programu
	//Open GL Kontekst
	const int GL_VERSION_MAJOR;					//Wersja OpenGL X.0 - X to g³ówna czêœæ
	const int GL_VERSION_MINOR;					//Wersja OpenGL 0.X - X to mniej wa¿na czêœæ

	//Delta time
	float dt;									//Delta time (naprawia problem ró¿nych prêdkoœæi dzia³ania programu na ró¿nych urz¹dzeniach)
	float curTime;								//Obecny czas
	float lastTime;								//Ostatni zmierzony czas
	float gameSpeed;							//Prêdkoœæ gry

	//Wejœcie Myszki
	double lastMouseX;							//Ostatnia wspó³rzêdna myszy X
	double lastMouseY;							//Ostatnia wspó³rzêdna myszy X
	double mouseX;								//Pozycja Myszy X
	double mouseY;								//Pozycja Myszy Y
	double mouseOffsetX;						//Offset myszy X (nwm jak jest offset po Polsku :D)
	double mouseOffsetY;						//Offset myszy X (nwm jak jest offset po Polsku :D)
	bool firstMouse;							//Pierwszy ruch myszy po nie ruszaniu jej

	//Parametry czo³gu
	float TankSpeed;							//Aktualna prêdkoœæ czo³gu
	float TankRotate;							//Aktualna prêdkoœc rotacji czo³gu
	float TurretRotate;							//Aktualna prêdkoœc rotacji wie¿y
	float CannonRotate;							//Aktualna prêdkoœæ podnoszenia/opuszczania lufy
	
	//Macierze
	glm::mat4 BulletMatrix;						//Macierz Pocisku
	glm::mat4 CannonMatrix;						//Macierz Dzia³a

	//Flagi
	bool fire;									//Strza³ - s³u¿y do ustawiania pozycji startowej pocisku
	bool explode;								//Wybuch - s³u¿y do ustawiania pozycji startowej wybuchu

	float CannonCooldown;						//£adowanie dzia³a

	//Pozycja czo³gu
	float x;									//Pozycja X czo³gu
	float z;									//Pozycja Y czo³gu
	//Elementy czo³gu
	float Rotation;								//Obecny obrót czo³gu
	float TurretRotation;						//Obecny obrót wie¿y
	float CannonRotation;						//Obecny obrót lufy
	float LeftWheels;							//Obecny obrót lewych kó³
	float RightWheels;							//Obecny obrót prawych kó³
	float BulletRotation;						//Obecny obrót pocisku (pozwala na lot po paraboli)
	//Offset kó³
	std::vector<glm::vec3> WheelOffsets;		//Offset kó³

	//Kamera
	Camera camera;								//Obiekt kamery

	//Macierze
	glm::mat4 ViewMatrix;						//Macierz widoku kamery (V)
	glm::vec3 camPosition;						//Pozycja kamery
	glm::vec3 worldUp;							//
	glm::vec3 camFront;							//Przód kamery

	glm::mat4 ProjectionMatrix;					//Macierz perspektywy (P)
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
	//Cz¹steczki
	std::vector<Model*> Particles;				//Modele cz¹steczek
	std::vector<glm::mat4> ParticlesMatrices;	//Macierze cz¹steczek
	std::vector<int> Particle_speed;			//Prêdkoœæ cz¹steczek
	std::vector<glm::vec3> ParticleOffset;		//Offset cz¹steczek
	std::vector<float> ParticleRotation;		//Obecny obrót cz¹steczki
	std::vector<float> ParticleRotationY;		//Startowy obrót cz¹steczki Y
	std::vector<float> ParticleRotationX;		//Startowy obrót cz¹steczki X

	//std::vector<int> Particle_speed;
	//Œwiat³a
	std::vector<glm::vec3*> Lights;				//Œwiat³o

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

	//Ustawia pozycjê startow¹ cz¹steczek
	void SetParticles(glm::mat4 matrix);
	//Aktualizuje Uniformy do shadera
	void UpdateUniforms();
	//Aktualizuje parametry startowe cz¹steczek
	void UpdateParticles();

	//Funkcje

public:
	Game(const char* title,
		const int width, const int height,
		const int GLVerMaj, const int GLVerMin,
		bool resizable);
	virtual ~Game();

	
	int getWindowShouldClose();		//Sprawdza czy okno gry powinno zostaæ zamkniête
	
	void setWindowShouldClose();	//Zamyka program

	void updateDt();				//Aktualizuje rzeczy zwi¹zane z delta time
	void UpdateKeyboardInput();		//Uruchamia rzeczy zwi¹zane z klawiszami klawiatury
	void UpdateMouseInput();		//Aktualizuje ruch wzglêdem myszki
	void UpdateInput();				//Aktualizacja urz¹dzeñ wejœciowych
	void Update();					//Aktualizacja gry - g³ówna czêœæ gry gdzie obiekty siê ruszaj¹ itd.
	void Render();					//Wyœwietlanie zmian
 


	static void FrameBufferResize(GLFWwindow* window, int fbW, int fbH);	//Pozwala na poprawn¹ zmianê wymiarów okna
	static int Random(int min, int max);									//Losuje losow¹ liczbê z zakresu [min max]
};

