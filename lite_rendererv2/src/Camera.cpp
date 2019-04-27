#include "Camera.h"
#include <iostream>
float Camera::incX, Camera::incY, Camera::incZ, Camera::rX, Camera::rY, Camera::rZ = 0.0f;
Camera::Camera()
{
	cameraLocation = glm::vec3(0.0f, 0.0f, 0.0f);
	currRotation = glm::vec3(0.0f, 0.0f * 2.0f, 0.0f);
	rightVector = glm::vec3(1.0f, 0.0f, 0.0f);
	forwardVector = glm::vec3(0.0f, 0.0f, 1.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	//currentWindow = inwin;
	//SetKeyIn();
}
//We need to calculate new right vector
void Camera::ReCalculateRightVector() {
	rightVector.x = -glm::cos(currRotation.y); //gonna assume degrees need to become radians
	rightVector.y = 0.0f;
	rightVector.z = glm::sin(currRotation.y); //gonna assume degrees need to become radians
	//std::cout << currRotation.y << std::endl;
	
}
void Camera::ReCalculateForwardVector() {
	
	if (currRotation.x <= -1.5707) {
		currRotation.x = -1.5707;
	} else if (currRotation.x >= 1.5707) {
		currRotation.x = 1.5707;
	}
	//if (currRotation.y >= 1.5707) {
	//	currRotation.y = 1.5707;
	//}
	//else if (currRotation.y <= -1.5707) {
	//	currRotation.y = -1.5707;
	//}


	forwardVector.x = -glm::sin(currRotation.y) * glm::cos(currRotation.x);
	forwardVector.y = -glm::sin(currRotation.x);
	forwardVector.z = -glm::cos(currRotation.x ) * glm::cos(currRotation.y);
	//std::cout << "( " << forwardVector.x << ", " << forwardVector.y << ", " << forwardVector.z << " )" << std::endl;

}
void Camera::ReCalculateUpVector() {
	upVector = glm::cross(forwardVector, rightVector);
}
void Camera::ReCalculateAllVectors() {
	Camera::ReCalculateRightVector();
	Camera::ReCalculateForwardVector();
	Camera::ReCalculateUpVector();
}

Camera::~Camera()
{
}
//void Camera::SetWindow(GLFWwindow *inwin) {
//	currentWindow = inwin;
//	SetKeyIn();
//}

void Camera::MoveCameraX()
{
	cameraLocation += (rightVector * incX);//(rightVector * (1.0f + incX));
}

void Camera::MoveCameraY()
{
	cameraLocation += (upVector * incY);//(upVector * (1.0f + incY));
}

void Camera::MoveCameraZ()
{
	cameraLocation += (forwardVector * incZ);//(forwardVector * (1.0f + incZ));
}
void Camera::RCameraX()
{
	currRotation.x += rX;
}

void Camera::RCameraY()
{
	currRotation.y += rY;
}

void Camera::RCameraZ()
{
	currRotation.z += rZ;
}
//void Camera::SetKeyIn() {
//	glfwSetKeyCallback(currentWindow, key_callback);
//}
void Camera::AssignAllChanges() {


	RCameraX();
	RCameraY();
	RCameraZ();
	ReCalculateAllVectors();
	MoveCameraX();
	MoveCameraY();
	MoveCameraZ();
	//std::cout << "Up is " << upVector.z << std::endl;
	//std::cout << "Right is: ( " << rightVector.x << ", " << rightVector.y << ", " << rightVector.z << " )" << std::endl;
	//std::cout << "Forward is: ( " << forwardVector.x << ", " << forwardVector.y << ", " << forwardVector.z << " )" << std::endl;
}
glm::mat4 Camera::GetTRMatrix() {
	//std::cout << "x value is: " << cameraLocation.x << std::endl;
	return      glm::rotate(-currRotation.x, rightVector) * glm::rotate(-currRotation.y, upVector) * glm::translate(glm::mat4(1.0f), cameraLocation);
}

glm::vec3 Camera::GetCameraLocation()
{
	return cameraLocation;
}

void Camera::ResetStaticValues() {
	Camera::incX, Camera::incY, Camera::incZ, Camera::rX, Camera::rY, Camera::rZ = 0.0f;
}


