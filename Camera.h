#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum directions {FORWARD=0,BACKWARD,LEFT,RIGHT};

class Camera
{
private:
	glm::mat4 ViewMatrix;

	GLfloat movementSpeed;
	GLfloat sensivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	void UpdateCameraVectors();

public:
	Camera(glm::vec3 position,glm::vec3 direction,glm::vec3 worldUp);
	~Camera();

	const glm::mat4 GetViewMatrix();
	const glm::vec3 GetPosition() const;

	void Move(const float& dt, const int direction);
	//void UpdateKeyboardInput(const float& dt, const int direction);
	void UpdateMouseInput(const float& dt,const double& offsetX, const double& offsetY);
	void UpdateInput(const float& dt, const int direction, const double& offsetX,const double& offsetY);


};

