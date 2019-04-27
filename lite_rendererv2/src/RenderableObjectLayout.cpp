#include "RenderableObjectLayout.h"

float * RenderableObjectLayout::GetVertices() {
	return vertices;
}
//Simple retrieval.
void RenderableObjectLayout::SetVertices(float *list) {
	//int sizeOfArray = sizeof(list) / sizeof(list[0]);
	
	vertices = new float[verticesSize];
	for (int i = 0; i < verticesSize; i++) {
		vertices[i] = list[i];
	}
}

unsigned int * RenderableObjectLayout::GetIndexLayout() {
	return indexLayout;
}

void RenderableObjectLayout::SetIndices(unsigned int *list) {
	int sizeOfArray = indicesSize;
	indexLayout = new unsigned int[sizeOfArray];
	for (int i = 0; i < sizeOfArray; i++) {
		indexLayout[i] = list[i];
	}
}

std::string RenderableObjectLayout::GetClassName() {
	return className;
}

void RenderableObjectLayout::SetClassName(std::string name) {
	className = name; //possible breaking point
}
