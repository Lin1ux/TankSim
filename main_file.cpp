/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/


#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "Tank.h"
#include "HullTank.h"


static float Width = 1920;
static float Height = 1080;
static float ScreenProportion = 1920 / 1080;
static float pi = 3.14;

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



//Modele
Tank tonk = Tank::Tank();
static Models::HullTank HullTank();

static Models::Sphere sun(0.5, 36, 36);
static Models::Sphere planet1(0.2, 36, 36);
static Models::Sphere moon1(0.1, 36, 36);
static Models::Cube cube();
static Models::Torus kolo(0.3, 0.1, 36, 36);





//Do wywalenia
float speed = 0; //3.14;
float earthSpeed = 100;
float moonSpeed = 500;
float wheelSpeed = 50;
float wheelAngle = 0;
float wheelRotate = 0;



//Wykrywanie przycisków
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if (action == GLFW_PRESS) 
	{
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
		/*if (key == GLFW_KEY_RIGHT) speed = -100; //printf("Prawa \n");
		if (key == GLFW_KEY_LEFT) speed = 100; //printf("Lewa \n");
		if (key == GLFW_KEY_W && (mods & GLFW_MOD_ALT) != 0)
			printf("ALT+W\n");
		if (key == GLFW_KEY_A) wheelRotate = 30.f;
		if (key == GLFW_KEY_D) wheelRotate = -30.f;*/
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
		/*if (key == GLFW_KEY_W) printf("puszczone W\n");
		if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT)
		{
			speed = 0;
		}
		if (key == GLFW_KEY_A || key == GLFW_KEY_D)
		{
			wheelRotate = 0;
		}*/
	}
}

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	glClearColor(0.3, 0.3, 0.6, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************	
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
	//************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************	
}



//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Czyszczenie bufora
	
	//Kamera
	//Dokończyć
	if (camHorizontal != 0 || camVertical != 0)
	{
		Yaw = Yaw + rotateSpeed * camHorizontal * glfwGetTime();
		Pitch = Pitch + rotateSpeed * camVertical * glfwGetTime();
		
	}
	//CamPosition += glm::vec3(camSpeed * directon * glfwGetTime(), 0.0f, camSpeed * forward * glfwGetTime());
	CamPosition += glm::vec3((cos(Yaw) * directon + cos(Yaw+pi/2) * forward) * camSpeed * glfwGetTime(), 0.0f, (sin(Yaw) * directon + sin(Yaw + pi / 2) * forward) * camSpeed * glfwGetTime());
	CamTargetPosition = glm::vec3(CamPosition.x + sin(-Yaw) * cos(-Pitch), CamPosition.y + sin(-Pitch), CamPosition.z + cos(-Yaw) * cos(-Pitch));
	//CamTargetPosition += glm::vec3(camSpeed * directon * glfwGetTime(), 0.0f, camSpeed * forward * glfwGetTime());

	//tonk.LoadHull();
	printf("%f %f %f\n", CamTargetPosition.x, CamTargetPosition.y, CamTargetPosition.z);

	glm::mat4 M = glm::mat4(1.0f);
	glm::mat4 V = glm::lookAt(
		CamPosition,							//Pozycja
		CamTargetPosition,						//Gdzie patrzy
		glm::vec3(0.0f, 1.0f, 0.0f));			//Nie ruszać
	glm::mat4 P = glm::perspective(
		glm::radians(50.0f), ScreenProportion, 1.0f, 50.0f);	

	//Program cieniujący
	spConstant->use();//Aktywacja programu cieniującego
	
	glUniformMatrix4fv(spConstant->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spConstant->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));
	
	//Ziemia
	glUniform4f(spConstant->u("color"), 0.05, 0.2, 0.05, 1);
	glm::mat4 Ground = glm::mat4(1.0f);
	Ground = glm::translate(Ground, glm::vec3(0.0f, -2.0f, 0.00f));
	Ground = glm::scale(Ground, glm::vec3(5.0f, 1.0f, 5.0f));
	glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(Ground));
	Models::cube.drawSolid();
	
	//spLambert->use();


	//glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
	//glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));
	//glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M));

	//PODWOZIE SAMOCHODU
	glUniform4f(spConstant->u("color"), 1, 0.0, 0.0, 1);
	glm::mat4 Tank = glm::mat4(1.0f);
	Tank = glm::translate(Tank, glm::vec3(1.0f, 0.0f, 0.66f));
	glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(Tank));
	Models::hullTank.drawSolid();

	/*spConstant->use();
	glUniformMatrix4fv(spConstant->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spConstant->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

	glm::mat4 MC = glm::mat4(1.0f);
	MC = glm::rotate(MC, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	//podwozie
	glUniform4f(spConstant->u("color"), 0.6, 0.6, 0.1, 1);
	glm::mat4 MS = glm::mat4(1.0f);
	MS = glm::scale(MC, glm::vec3(0.66f, 0.125f, 1.0f));
	glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(MS));
	Models::cube.drawSolid();

	//kolo 1
	glUniform4f(spConstant->u("color"), 0.2, 0.2, 0.2, 1);
	glm::mat4 MW1 = glm::mat4(1.0f);
	MW1 = glm::rotate(MC, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	MW1 = glm::translate(MW1, glm::vec3(1.0f, 0.0f, 0.66f));
	MW1 = glm::rotate(MW1, glm::radians(wheelRotate), glm::vec3(0.0f, 1.0f, 0.0f));
	MW1 = glm::rotate(MW1, glm::radians(wheelAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(MW1));
	kolo.drawSolid();
	
	//kolo 2
	glUniform4f(spConstant->u("color"), 0.2, 0.2, 0.2, 1);
	glm::mat4 MW2 = glm::mat4(1.0f);
	MW2 = glm::rotate(MC, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	MW2 = glm::translate(MW2, glm::vec3(1.0f, 0.0f, -0.66f));
	MW2 = glm::rotate(MW2, glm::radians(wheelRotate), glm::vec3(0.0f, 1.0f, 0.0f));
	MW2 = glm::rotate(MW2, glm::radians(wheelAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(MW2));
	kolo.drawSolid();

	//kolo 3
	glUniform4f(spConstant->u("color"), 0.2, 0.2, 0.2, 1);
	glm::mat4 MW3 = glm::mat4(1.0f);
	MW3 = glm::rotate(MC, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	MW3 = glm::translate(MW3, glm::vec3(-1.0f, 0.0f, 0.66f));
	MW3 = glm::rotate(MW3, glm::radians(wheelAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(MW3));
	kolo.drawSolid();
	
	//kolo 4
	glUniform4f(spConstant->u("color"), 0.2, 0.2, 0.2, 1);
	glm::mat4 MW4 = glm::mat4(1.0f);
	MW4 = glm::rotate(MC, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	MW4 = glm::translate(MW4, glm::vec3(-1.0f, 0.0f, -0.66f));
	MW4 = glm::rotate(MW4, glm::radians(wheelAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(MW4));
	kolo.drawSolid();

	*/


	//ZEBATKI

	/*for (int j = 0; j < 3; j++)
	{
		//Torus 1
		glUniform4f(spLambert->u("color"), 0.6, 0.6, 0.1, 1);
		glm::mat4 MT1 = glm::mat4(1.0f);
		MT1 = glm::translate(MT1, glm::vec3(0.0f, 0.0f, 0.0f));
		MT1 = glm::rotate(MT1, glm::radians(120.0f*j), glm::vec3(0.0f, 0.0f, 1.0f));
		MT1 = glm::translate(MT1, glm::vec3(2.0f, 0.0f, 0.0f));
		MT1 = glm::rotate(MT1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		MT1 = glm::rotate(MT1, angle * PI / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(MT1));
		Models::torus.drawSolid();

		//Torus 2
		glUniform4f(spLambert->u("color"), 0.1, 0.6, 0.1, 1);
		glm::mat4 MT2 = glm::mat4(1.0f);
		MT2 = glm::translate(MT2, glm::vec3(0.0f, 0.0f, 0.0f));
		MT2 = glm::rotate(MT2, glm::radians(120.0f * j) + glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		MT2 = glm::translate(MT2, glm::vec3(2.0f, 0.0f, 0.0f));
		MT2 = glm::rotate(MT2, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		MT2 = glm::rotate(MT2, -angle * PI / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(MT2));
		Models::torus.drawSolid();

		//Cubes
		for (int i = 0; i < 12; i++)
		{
			glUniform4f(spLambert->u("color"), 0.1, 0.6, 0.1, 1);
			glm::mat4 MC = glm::mat4(1.0f);
			MC = glm::rotate(MT2, glm::radians(30.0f*i), glm::vec3(0.0f, 0.0f, 1.0f));
			MC = glm::translate(MC, glm::vec3(1.0f, 0.0f, 0.0f));
			MC = glm::scale(MC, glm::vec3(0.1f, 0.1f, 0.1f));
			glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(MC));
			Models::cube.drawSolid();

			glUniform4f(spLambert->u("color"), 0.6, 0.6, 0.1, 1);
			MC = glm::mat4(1.0f);
			MC = glm::rotate(MT1, glm::radians(30.0f * i) + glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			MC = glm::translate(MC, glm::vec3(1.0f, 0.0f, 0.0f));
			MC = glm::scale(MC, glm::vec3(0.1f, 0.1f, 0.1f));
			glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(MC));
			Models::cube.drawSolid();
		}
	}
	*/
	//Torus 3
	/*
	glUniform4f(spLambert->u("color"), 0.1, 0.6, 0.6, 1);
	glm::mat4 MT3 = glm::mat4(1.0f);
	MT3 = glm::translate(MT3, glm::vec3(0.0f, 0.0f, 0.0f));
	MT3 = glm::rotate(MT3, 90.0f * PI / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	MT3 = glm::rotate(MT3, angle * PI / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(MT3));
	Models::torus.drawWire();
	*/

	
	
	
	/*Planety
	
	//Rysowanie modeli
	M = glm::rotate(glm::mat4(1.0f), angle * PI / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//Models::teapot.drawSolid();
	
	glm::mat4 Ms = glm::mat4(1.0f);
	//Ms = glm::rotate(glm::mat4(1.0f), angle * PI / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Ms));

	sun.drawSolid();
	
	//Planeta
	glm::mat4 Mp = Ms;
	Mp = glm::rotate(Ms, angle * PI / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	Mp = glm::translate(Mp, glm::vec3(1.5f, 0.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mp));

	glUniform4f(spLambert->u("color"), 0.1, 0.6, 0.1, 1);
	planet1.drawSolid();

	//Księżyc
	glm::mat4 Mm = Mp;
	Mm = glm::rotate(Mp, angle * PI / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	Mm = glm::translate(Mm, glm::vec3(0.5f, 0.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mm));

	glUniform4f(spLambert->u("color"), 0.1, 0.1, 0.1, 1);
	moon1.drawSolid();

	//Planeta 2
	glm::mat4 Mp2 = Ms;
	Mp2 = glm::rotate(Ms, angle * PI / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	Mp2 = glm::translate(Mp2, glm::vec3(2.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mp2));

	glUniform4f(spLambert->u("color"), 0.1, 0.6, 0.1, 1);
	planet1.drawSolid();

	*/
	glfwSwapBuffers(window);

}


int main(void)
{

	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	float angle = 0;
	glfwSetTime(0);

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1600, 900, "Tank Simulator", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Models::hullTank.loadModel(); //Wczytywanie danych .obj

	//Główna pętla	
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle += speed * glfwGetTime();
		wheelAngle += wheelSpeed * glfwGetTime();
		glfwSetTime(0);
		drawScene(window, angle); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
