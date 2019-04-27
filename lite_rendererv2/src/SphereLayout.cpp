#include "SphereLayout.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

SphereLayout::SphereLayout() {
	int precision = 15;
	//Set meta data
	verticesSize = (precision + 1) * (precision + 1) * 8;
	indicesSize = precision * precision * 6;

	float *vertices = (float *) alloca(verticesSize * sizeof(float)) ; //may need changes
	vertexContainer *vc = (vertexContainer*)alloca((verticesSize/8) * sizeof(vertexContainer));
	//calculate triangle vertices
	for (int i = 0; i <= precision; i++) {
		for (int j = 0; j <= precision; j++) {
			float y = (float)cos((180.0f - i * 180.0f / precision) * (M_PI / 180.0f));
			float x = -(float)cos((j*360.0f / precision) * (M_PI / 180.0f)) * (float)abs(cos(asin(y)));
			float z = (float)sin((j * 360.0f / precision) * (M_PI / 180.0f)) * (float)abs(cos(asin(y)));
			//Eh we'll see what happens.
			float s = (float)j / (float) precision;
			float t = (float)i / (float) precision;
			vc[i * (precision + 1) + j] = { x, y, z, s, t };
		}
	}
	for (int i = 0; i < (verticesSize / 8); i++) {
		std::cout << vc[i].s << " " << vc[i].t << std::endl;
	}
	//for (int i = 0; i < verticesSize; i++) {
	//	std::cout << "( " << vc[i].x << ", " << vc[i].y << ", " << vc[i].z << ")" << std::endl;
	//}
	int acc = 0;
	for (int i = 0; i < (verticesSize / 8); i++) {
		vertices[acc] = vc[i].x;
		acc++;
		vertices[acc] = vc[i].y;
		acc++;
		vertices[acc] = vc[i].z;
		acc++;
		vertices[acc] = vc[i].s;
		acc++;
		vertices[acc] = vc[i].t;
		acc++;
		vertices[acc] = vc[i].x;
		acc++;
		vertices[acc] = vc[i].y;
		acc++;
		vertices[acc] = vc[i].z;
		acc++;
	}
	SetVertices(vertices);
	unsigned int * indices = (unsigned int *)alloca(indicesSize * sizeof(unsigned int));
	//Now for the triangle calculations.
	int iterator = 0;
	for (int i = 0; i < precision; i++) {
		for (int j = 0; j < precision; j++) {
			indices[6 * (i*precision + j) + 0] = i * (precision + 1) + j;
			indices[6 * (i*precision + j) + 1] = i * (precision + 1) + j + 1;
			indices[6 * (i*precision + j) + 2] = (i + 1) * (precision + 1) + j;
			indices[6 * (i*precision + j) + 3] = i * (precision + 1) + j + 1;
			indices[6 * (i*precision + j) + 4] = (i + 1) * (precision + 1) + j + 1;
			indices[6 * (i*precision + j) + 5] = (i + 1) * (precision + 1) + j;
			iterator += 6;
		}
	}
	std::cout << "Indices" << std::endl;
	for (int i = 0; i < iterator; i++) {
		if (i % 3 == 0) {
			std::cout << std::endl;
		}
		std::cout << indices[i];
		if ((i + 1) % 3 != 0) {
			std::cout << " ";
		}

	}
	std::cout << std::endl;
	SetIndices(indices);
	SetClassName("Sphere");
}

SphereLayout::~SphereLayout() {
	//Do nothing right now.
}