#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

//struct vCamera {
//	float incX, incY, incZ, rX, rY, rZ;
//	glm::vec3 cameraLocation, currRotation, forwardVector, rightVector, upVector;
//} BasicCam = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0,0,20), glm::vec3(0,0,0), glm::vec3(0,0,-1), glm::vec3(1,0,0), glm::vec3(0,1,0) };

class Camera {

public:
	static float incX, incY, incZ, rX, rY, rZ;
	Camera();
	~Camera();
	//void SetKeyIn();
	//void SetWindow(GLFWwindow *inwin);

	void MoveCameraX();
	void MoveCameraY();
	void MoveCameraZ();
	void ReCalculateRightVector();
	void ReCalculateForwardVector();
	void ReCalculateUpVector();
	void ReCalculateAllVectors();
	void RCameraX();
	void RCameraY();
	void RCameraZ();
	void AssignAllChanges();
	void ResetStaticValues();
	glm::mat4 GetTRMatrix();
	glm::vec3 GetCameraLocation();
private:
	glm::vec3 cameraLocation, currRotation, forwardVector, rightVector, upVector; //currRotation is in angles 0 degrees = 0.0f, 90 degrees = 90.0f.
																				  //GLFWwindow *currentWindow;
};

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);