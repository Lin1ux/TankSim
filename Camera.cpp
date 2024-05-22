#include "Camera.h"

void Camera::UpdateCameraVectors()
{
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
{
	this->ViewMatrix = glm::mat4(1.0f);

	this->movementSpeed = 3.0f;
	this->sensivity = 20.0f;

	this->worldUp = worldUp;
	this->position = position;
	this->right = glm::vec3(0.0f);
	this->up = worldUp;

	this->pitch = 0.0f;
	this->yaw = -90.0f;
	this->roll = 0.0f;

	this->UpdateCameraVectors();
}

Camera::~Camera()
{

}

const glm::mat4 Camera::GetViewMatrix()
{
	this->UpdateCameraVectors();

	this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

	return this->ViewMatrix;
}

const glm::vec3 Camera::GetPosition() const
{
	return this->position;
}



void Camera::Move(const float& dt, const int direction)
{
	//Aktualizacja pozycji kamery
	switch (direction)
	{
		case FORWARD:
			this->position += this->front * this->movementSpeed * dt;
			break;
		case BACKWARD:
			this->position -= this->front * this->movementSpeed * dt;
			break;
		case LEFT:
			this->position -= this->right * this->movementSpeed * dt;
			break;
		case RIGHT:
			this->position += this->right * this->movementSpeed * dt;
			break;
		default:
			break;
	}
}

void Camera::UpdateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
{
	//Aktualizacja obrotów kamery pitch, yaw, roll
	this->pitch += static_cast<GLfloat>(offsetY) * this->sensivity * dt;
	this->yaw += static_cast<GLfloat>(offsetX) * this->sensivity * dt;

	if (this->pitch > 80.0f)
	{
		this->pitch = 80.0f;
	}
	else if (this->pitch < -80.0f)
	{
		this->pitch = -80.0f;
	}
	if (this->yaw > 360.0f || this->yaw < -360.0f)
	{
		this->yaw = 0.0f;
	}
}

void Camera::UpdateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
{
	this->UpdateMouseInput(dt, offsetX, offsetY);
}
