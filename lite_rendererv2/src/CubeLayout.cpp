#include "CubeLayout.h"

CubeLayout::CubeLayout() {
	verticesSize = 180;
	float positions[] = {
		
		-0.5f,0.5f,0.5f,  0.25f, 0.66f,//front top left //2
		-0.5f,-0.5f,0.5f, 0.25f,0.33f, //front bottom left //3
		0.5f,-0.5f,0.5f,  0.5f, 0.33f,//front bottomright //0

		0.5f,-0.5f,0.5f,  0.5f, 0.33f,//front bottomright //0
		0.5f,0.5f,0.5f,   0.5f, 0.66f,//front top right //1
		-0.5f,0.5f,0.5f,  0.25f, 0.66f,//front top left //2

		//Front triangles
		0.5f,-0.5f,0.5f,  0.5f, 0.33f,//front bottomright //0
		0.5f,-0.5f,-0.5f, 0.75f, 0.33f,//back bottomright //4
		0.5f,0.5f,0.5f,   0.5f, 0.66f,//front top right //1

		0.5f,-0.5f,-0.5f, 0.75f, 0.33f,//back bottomright //4
		0.5f,0.5f,-0.5f,  0.75f, 0.66f,//back top right //5
		0.5f,0.5f,0.5f,   0.5f, 0.66f,//front top right //1
		//Right triangles

		0.5f,-0.5f,-0.5f, 0.75f, 0.33f,//back bottomright //4
		-0.5f,-0.5f,-0.5f,1.0f, 0.33f,//back bottom left //7
		0.5f,0.5f,-0.5f,  0.75f, 0.66f,//back top right //5

		-0.5f,-0.5f,-0.5f,1.0f, 0.33f,//back bottom left //7
		- 0.5f,0.5f,-0.5f,1.0f, 0.66f,//back top left //6
		0.5f,0.5f,-0.5f,  0.75f, 0.66f,//back top right //5
		//Back triangles

		-0.5f,-0.5f,-0.5f,0.0f, 0.33f,//back bottom left //7
		-0.5f,-0.5f,0.5f, 0.25f,0.33f, //front bottom left //3
		-0.5f,0.5f,-0.5f, 0.0f, 0.66f,//back top left //6

		-0.5f,-0.5f,0.5f, 0.25f,0.33f, //front bottom left //3
		-0.5f,0.5f,0.5f,  0.25f, 0.66f,//front top left //2
		-0.5f,0.5f,-0.5f, 0.0f, 0.66f,//back top left //6
		//Left triangles

		-0.5f,-0.5f,-0.5f,0.25f, 0.0f,//back bottom left //7
		0.5f,-0.5f,-0.5f, 0.50f, 0.0f,//back bottomright //4
		0.5f,-0.5f,0.5f,  0.5f, 0.33f,//front bottomright //0

		0.5f,-0.5f,0.5f,  0.5f, 0.33f,//front bottomright //0
		-0.5f,-0.5f,0.5f, 0.25f,0.33f, //front bottom left //3
		-0.5f,-0.5f,-0.5f,0.25f, 0.0f,//back bottom left //7
		//Bottom triangles

		-0.5f,0.5f,0.5f,  0.25f, 0.66f,//front top left //2
		0.5f,0.5f,0.5f,   0.5f, 0.66f,//front top right //1
		0.5f,0.5f,-0.5f,  0.50f, 1.0f,//back top right //5

		0.5f,0.5f,-0.5f,  0.50f, 1.0f,//back top right //5
		-0.5f,0.5f,-0.5f, 0.25f, 1.0f,//back top left //6
		-0.5f,0.5f,0.5f,  0.25f, 0.66f,//front top left //2


	};

	SetVertices(positions);
	indicesSize = 36;
	unsigned int indices[] = {
		0,1,2,
		3,4,5, //front face

		6,7,8,
		9,10,11, //left face

		12,13,14,
		15,16,17, //bottom face.

		18,19,20,
		21,22,23, //right face.

		24,25,26,
		27,28,29, //top face.

		30,31,32,
		33,34,35, //back face.

	};

	SetIndices(indices);
	SetClassName("Cube");
}
CubeLayout::~CubeLayout() {

}