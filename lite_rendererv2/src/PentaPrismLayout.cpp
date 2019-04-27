#include "PentaPrismLayout.h"

PentaPrismLayout::PentaPrismLayout() {
	verticesSize = 50;
	float positions[] = {
		-0.5878f, 0.5f, .8090f, 0.25f, 0.0f,//0
		-0.9511f, 0.5f, -0.3090f, 0.0f, 0.5f, //1
		0.0f, 0.5f, -1.0f, 0.5f, 1.0f,//2
		0.9511f, 0.5f, -0.3090f, 1.0f, 0.5f,//3
		0.5878f, 0.5f, .8090f, 0.75f, 0.0f,//4
		//0.0f, 0.5f, 0.0f //5 center top.

		- 0.5878f, -0.5f, .8090f, 0.25f, 0.0f,//5
		-0.9511f, -0.5f, -0.3090f, 0.0f, 0.5f,//6
		0.0f, -0.5f, -1.0f,  0.5f, 1.0f,//7
		0.9511f, -0.5f, -0.3090f,  1.0f, 0.5f,//8
		0.5878f, -0.5f, .8090f,  0.75f, 0.0f//9
		//0.0f, -0.5f, 0.0f //11 center bot.

	};
	SetVertices(positions);
	indicesSize = 48;
	unsigned int indices[]{
		//top 'cover' we start from center with all.
		//5, 0, 4, 
		//5, 1, 0,
		//5, 2, 1,
		//5, 3, 2,
		//5, 4, 3,
		2, 0, 4,
		0,2,1,
		4,3,2,

		//front face
		0, 5, 4,
		4, 5, 9,
		//front left face
		1, 6, 0,
		0, 6, 5,
		//back left face
		2, 7, 1,
		1, 7, 6,
		//back right face
		3, 8, 2,
		2, 8, 7,
		//front right face
		4, 9, 3,
		3, 9, 8,

		//bottom 'cover' we start from the center with call
		//11, 6, 10,
		//11, 7, 6,
		//11, 8, 7,
		//11,9,8,
		//11,10,9
		7, 5, 9,
		5, 7, 6,
		9, 8, 7


	};
	SetIndices(indices);
	SetClassName("PentaPrism");
}
PentaPrismLayout::~PentaPrismLayout() {

}