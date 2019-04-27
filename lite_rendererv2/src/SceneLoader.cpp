//The 'lite renderer' is a program partially developed by Zachary Reyes
// for the purposes of learning OpenGL and building the projects for graphics
// in a short amount of time.
// It utilizes a mixture of code from "The Cherno Project" OpenGL tutorials on Youtube, and
// code Zach has written on his own.
// Zach considered re-writing the code base from scratch, but then realized that was a waste of effort.
// Rather, he decided to keep the components that worked from before, but streamline the entire process
// into a pipeline that he could use to quickly build scenes and that would be expandable for future projects.


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.h"
#include "Renderer.h"
#include "Shader.h"
#include "RenderableObjectLayout.h"
#include "CubeLayout.h"
#include "PentaPrismLayout.h"
#include "RenderableObject.h"
#include "RotatingCube.h"
#include "SphereLayout.h"
#include "VertexBufferLayout.h"
#include "OrbitingBody.h"
#include "texture.h"
#include "AxisTriangle.h"
#include "lightStruct.h"
#include "lightMarker.h"
#include "ShadowBucket.h"
#include "skybox.h"
#include "ObjectFileReader.h"
#include <fstream>
#include <string>

#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

ambient_positional_light globalLight;
ShadowBucket shadowData;
bool isOff = false;
void TurnLightsOff();
void TurnLightsOn();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	float moveRate = 0.05f;
	float turnRate = 0.05f;
	//std::cout << "We'ved received a value!" << std::endl;
	if ((key == GLFW_KEY_W || key == GLFW_KEY_S) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (key == GLFW_KEY_W) {
			Camera::incZ = -moveRate;
		}
		else if (key == GLFW_KEY_S) {
			Camera::incZ = moveRate;
		}

	}
	else {
		Camera::incZ = 0.0f;
	}
	if ((key == GLFW_KEY_D || key == GLFW_KEY_A) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (key == GLFW_KEY_D) {
			Camera::incX = moveRate;
		}
		else if (key == GLFW_KEY_A) {
			Camera::incX = -moveRate;
		}

	}
	else {
		Camera::incX = 0.0f;
	}

	if ((key == GLFW_KEY_Q || key == GLFW_KEY_E) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (key == GLFW_KEY_Q) {
			Camera::incY = moveRate;
		}
		else if (key == GLFW_KEY_E) {
			Camera::incY = -moveRate;
		}

	}
	else {
		Camera::incY = 0.0f;
	}
	if ((key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (key == GLFW_KEY_UP) {
			Camera::rX = -turnRate;
		}
		else if (key == GLFW_KEY_DOWN) {
			Camera::rX = turnRate;
		}

	}
	else {
		Camera::rX = 0.0f;
	}

	if ((key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (key == GLFW_KEY_RIGHT) {
			Camera::rY = -turnRate;
		}
		else if (key == GLFW_KEY_LEFT) {
			Camera::rY = turnRate;
		}

	}
	else {
		Camera::rY = 0.0f;
	}
	if ((key == GLFW_KEY_J || key == GLFW_KEY_L) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (key == GLFW_KEY_J) {
			globalLight.position[0] += -moveRate;
		}
		else if (key == GLFW_KEY_L) {
			globalLight.position[0] += moveRate;
		}

	}
	else {
		globalLight.position[0] = globalLight.position[0];
	}

	if ((key == GLFW_KEY_U || key == GLFW_KEY_O) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (key == GLFW_KEY_O) {
			globalLight.position[1] += moveRate;
		}
		else if (key == GLFW_KEY_U) {
			globalLight.position[1] += -moveRate;
		}

	}
	else {
		globalLight.position[1] = globalLight.position[1];
	}

	if ((key == GLFW_KEY_I || key == GLFW_KEY_K) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (key == GLFW_KEY_I) {
			globalLight.position[2] += -moveRate;
		}
		else if (key == GLFW_KEY_K) {
			globalLight.position[2] += moveRate;
		}

	}
	else {
		globalLight.position[2] = globalLight.position[2];
	}

	if ((key == GLFW_KEY_SPACE) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (isOff) {
			TurnLightsOn();
			isOff = !isOff;
		}
		else {
			TurnLightsOff();
			isOff = !isOff;
		}
	}
	else {
		//globalLight.position[2] = globalLight.position[2];
	}

}


void InitializeGlobalCamera() {
	globalLight.position[0] = 10.0f;
	globalLight.position[1] = 10.0f;
	globalLight.position[2] = 10.0f;

	globalLight.ambientAura[0] = 0.05f;
	globalLight.ambientAura[1] = 0.05f;
	globalLight.ambientAura[2] = 0.05f;
	globalLight.ambientAura[3] = 1.0f;

	globalLight.ambientLight[0] = 0.05f;
	globalLight.ambientLight[1] = 0.05f;
	globalLight.ambientLight[2] = 0.05f;
	globalLight.ambientLight[3] = 1.0f;

	globalLight.diffuseLight[0] = 0.05f;
	globalLight.diffuseLight[1] = 0.05f;
	globalLight.diffuseLight[2] = 0.05f;
	globalLight.diffuseLight[3] = 1.0f;

	globalLight.specularLight[0] = 0.05f;
	globalLight.specularLight[1] = 0.05f;
	globalLight.specularLight[2] = 0.05f;
	globalLight.specularLight[3] = 1.0f;
	
}

void TurnLightsOn() {
	globalLight.ambientAura[0] = 0.05f;
	globalLight.ambientAura[1] = 0.05f;
	globalLight.ambientAura[2] = 0.05f;
	globalLight.ambientAura[3] = 1.0f;

	globalLight.ambientLight[0] = 0.05f;
	globalLight.ambientLight[1] = 0.05f;
	globalLight.ambientLight[2] = 0.05f;
	globalLight.ambientLight[3] = 1.0f;

	globalLight.diffuseLight[0] = 0.05f;
	globalLight.diffuseLight[1] = 0.05f;
	globalLight.diffuseLight[2] = 0.05f;
	globalLight.diffuseLight[3] = 1.0f;

	globalLight.specularLight[0] = 10.05f;
	globalLight.specularLight[1] = 10.05f;
	globalLight.specularLight[2] = 10.05f;
	globalLight.specularLight[3] = 1.0f;

}

void TurnLightsOff() {
	globalLight.ambientAura[0] = 0.0f;
	globalLight.ambientAura[1] = 0.0f;
	globalLight.ambientAura[2] = 0.0f;
	globalLight.ambientAura[3] = 1.0f;

	globalLight.ambientLight[0] = 0.0f;
	globalLight.ambientLight[1] = 0.0f;
	globalLight.ambientLight[2] = 0.0f;
	globalLight.ambientLight[3] = 1.0f;

	globalLight.diffuseLight[0] = 0.0f;
	globalLight.diffuseLight[1] = 0.0f;
	globalLight.diffuseLight[2] = 0.0f;
	globalLight.diffuseLight[3] = 1.0f;

	globalLight.specularLight[0] = 0.0f;
	globalLight.specularLight[1] = 0.0f;
	globalLight.specularLight[2] = 0.0f;
	globalLight.specularLight[3] = 1.0f;

}

void SetJadeMaterial(RenderableObject * mat) {
	mat->SetAmbient(0.135f, 0.2225f, 0.1575f, 0.95f);
	mat->SetDiffuse(10.54f, 10.89f, 10.63f, 10.95f);
	mat->SetSpecular(0.3162f, 0.3162f, 0.3162f, 0.95f);//alpha values should be 0.95f
	mat->SetShiny(12.8f);
}

void InitializeShadowData() {
	shadowData.shadow_buffer = 0;
	shadowData.shadow_texId = 0;
	shadowData.b = glm::mat4(1.0f);
	shadowData.lightV_matrix = glm::mat4(1.0f);
	shadowData.lightP_matrix = glm::mat4(1.0f);
	shadowData.shadowMVP = glm::mat4(1.0f);
	shadowData.shadowMVP2 = glm::mat4(1.0f);

}



int main(void) {
//Create new frame buffer
	std::cout << "Starting program" << std::endl;
	InitializeShadowData();
	shadowData.b = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	
	//set global light values.
	InitializeGlobalCamera();

	std::cout << "Starting program << " << std::endl;
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "Problem with initialization" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Project OpenGL", NULL, NULL);



	if (!window)
	{
		std::cout << "Problem with window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error boi" << std::endl;
	}
	Renderer master;
	master.SetPerspection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f));
	/*
	Initialization process.
	1. Load the shaders
	1.a Build static camera.
	2. Push Desired Object classes to collection of vaos. //one vao per object class.
	3. Create scene's individual objects / virtual cameras.
	*/
	GLCall(glGenFramebuffers(1, &shadowData.shadow_buffer));
	std::cout << "finisehd genFrameBufferscall" << std::endl;
	GLCall(glEnable(GL_DEPTH_TEST));
	//GLCall(glDepthMask(GL_TRUE));
	//GLCall(glDepthFunc(GL_LEQUAL));
	//GLCall(glDepthRange(0.0f, 10.0f));

	//1.
	Shader m_Shader = Shader("res/shaders/Basic5.shader", true);
	std::cout << "mShder id is: " << m_Shader.GetmID() << std::endl;
	Shader m_SShader = Shader("res/shaders/shadow.shader", true);

	std::cout << "mShder id is: " << m_SShader.GetmID() << std::endl;
	Shader sky = Shader("res/shaders/Basic4.shader", true);
	std::cout << "mShder id is: " << sky.GetmID() << std::endl;
	master.AddShader(&m_Shader);
	master.AddShader(&m_SShader);
	master.AddShader(&sky);


	//1.a
	Camera bbCam;
	master.currCam = &bbCam;
	std::cout << "Made past shader constructor" << std::endl;
	//Build basic layout
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	Texture defaul = Texture("res/textures/default.jpg");
	Texture mailler = Texture("res/textures/mail.jpg");
	Texture kuttal = Texture("res/textures/sandy.jpg");
	Texture wainwright = Texture("res/textures/wain.jpg");
	Texture zach = Texture("res/textures/z.jpg");
	Texture hale = Texture("res/textures/h.jpg");
	Texture shenoi = Texture("res/textures/s.jpg");
	Texture zA = Texture("res/textures/blue.jpg");
	Texture yA = Texture("res/textures/green.jpg");
	Texture xA = Texture("res/textures/red.jpg");
	Texture shadows = Texture(shadowData.shadow_texId); ////argument is pass by reference. this could be the problem
	Texture wood = Texture("res/textures/wood.jpg");
	std::cout << "texId is " << shadowData.shadow_texId << std::endl;
	Texture skyT = Texture("res/textures/sky.jpg");

	master.AddTexture("Default", &defaul);
	master.AddTexture("Mailler", &mailler);
	master.AddTexture("Kuttal", &kuttal);
	master.AddTexture("Wainwright", &wainwright);
	master.AddTexture("Zach", &zach);
	master.AddTexture("Hale", &hale);
	master.AddTexture("Shenoi", &shenoi);
	master.AddTexture("z", &zA);
	master.AddTexture("x", &xA);
	master.AddTexture("y", &yA);
	master.AddTexture("Shadow", &shadows);
	master.AddTexture("Sky", &skyT);
	master.AddTexture("Wood", &wood);

	glfwSetKeyCallback(window, key_callback);
	//master.AddNewShape(PentaPrismLayout(), layout);
	//master.AddNewShape(CubeLayout(), layout);
	master.AddNewShape(SphereLayout(), layout);
	master.AddNewShape(ObjectFileReader("res/models/capsule.obj", "Dummy"), layout);
	//master.AddNewShape(AxisTriangle(), layout);
	VertexBufferLayout layout2;
	layout2.Push<float>(3);
	layout2.Push<float>(2);
	master.AddNewShape(CubeLayout(), layout2);

	skybox bob = skybox(&bbCam);
	bob.SetTextureName("Sky");
	master.SetSkybox(&bob);

	//RotatingCube triangleZ = RotatingCube(false, false, false, false);
	//triangleZ.SetClassName("AxisTriangle");
	//triangleZ.SetModelTranslation(5.0f, 5.0f, 0.0f);
	//triangleZ.SetTextureName("z");
	//
	//RotatingCube triangleY = RotatingCube(true, false, false, false);
	//triangleY.SetClassName("AxisTriangle");
	////triangleZ.SetModelTranslation(5.0f, 5.0f, 0.0f);
	//triangleY.SetTextureName("y");
	//triangleY.SetRotation(-1.57f, 1, 0, 0);
	//triangleZ.AddChild(&triangleY);
	//
	//RotatingCube triangleX = RotatingCube(true, false, false, false);
	//triangleX.SetClassName("AxisTriangle");
	////triangleZ.SetModelTranslation(5.0f, 5.0f, 0.0f);
	//triangleX.SetTextureName("x");
	//triangleX.SetRotation(1.57f, 0, 1, 0);
	//triangleX.SetModelTranslation(0, -0.005f, 0);
	//triangleZ.AddChild(&triangleX);
	lightMarker lighter = lightMarker();
	RotatingCube dummy = RotatingCube(false, false, false, false);
	dummy.SetClassName("Dummy");
	dummy.SetTextureName("Wood");
	dummy.SetModelTranslation(10.0f, 5.0f, -5.0f);
	dummy.SetScale(2.0f);
	SetJadeMaterial(&dummy);
	RotatingCube test1 = RotatingCube(false, false, false, false);
	test1.UpdateSelf();
	test1.SetTextureName("Shenoi");
	test1.SetScale(3.0f);
	SetJadeMaterial(&test1);
	OrbitingBody childTest = OrbitingBody(true, false, false, false);
	childTest.SetTextureName("Wainwright");
	childTest.SetScale(0.8f);
	childTest.radiusMulti = 7.5f;

	OrbitingBody satellite = OrbitingBody(true, false, false, false);
	satellite.SetTextureName("Hale");
	satellite.SetScale(0.5);
	satellite.orbitalAdditive = -0.01f;
	satellite.radiusMulti = 2.5f;

	OrbitingBody planet2 = OrbitingBody(true, false, false, false);
	planet2.SetTextureName("Mailler");
	planet2.SetScale(0.75f);
	planet2.radiusMulti = 15.0f;
	planet2.orbitalAdditive = -0.005f;

	OrbitingBody moon2 = OrbitingBody(true, false, false, false);
	moon2.SetTextureName("Kuttal");
	moon2.SetScale(0.65f);
	moon2.radiusMulti = 3.0f;
	moon2.orbitalAdditive = 0.005f;

	OrbitingBody zPlanet = OrbitingBody(true, false, false, false);
	zPlanet.SetTextureName("Zach");
	//zPlanet.SetClassName("PentaPrism");
	zPlanet.radiusMulti = 30.0f;
	zPlanet.orbitalAdditive = 0.01f;
	

	//satellite.SetClassName("PentaPrism");

	//satellite.SetClassName("Sphere");


	//childTest.SetModelTranslation(0, 0, -4);
	test1.SetModelTranslation(0, 0, -2);
	test1.AddChild(&childTest);
	childTest.AddChild(&satellite);
	test1.AddChild(&planet2);
	test1.AddChild(&zPlanet);
	planet2.AddChild(&moon2);
	master.AddRenderQueue(&test1);
	master.AddRenderQueue(&lighter);
	master.AddRenderQueue(&dummy);
	//master.AddRenderQueue(&triangleZ);
	//master.AddUpdateQueue(&bob);
	master.AddUpdateQueue(&test1);
	master.AddUpdateQueue(&childTest);
	master.AddUpdateQueue(&satellite);
	master.AddUpdateQueue(&planet2);
	master.AddUpdateQueue(&moon2);
	master.AddUpdateQueue(&zPlanet);
	master.AddUpdateQueue(&lighter);
	master.AddUpdateQueue(&dummy);



	while (!glfwWindowShouldClose(window))
	{
		//Render here.
		/* Render here */
	//	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	//	std::cout << "Starting loop " << std::endl;
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		master.UpdateObjects();
		bbCam.AssignAllChanges();
		bob.OnUpdate();
		//m_Texture.Bind();
		master.DrawSkybox();
		master.DrawRenderQueue();

		//bbCam.ResetStaticValues(); //don't know if this is necessary It's not.


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}
	glfwTerminate();
	return 0;
}