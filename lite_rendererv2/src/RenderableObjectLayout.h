#pragma once
#include <iostream>
class RenderableObjectLayout
{
public:
	RenderableObjectLayout() {}
	virtual ~RenderableObjectLayout() {}
	float * GetVertices();
	void SetVertices(float *list);
	unsigned int * GetIndexLayout();
	void SetIndices(unsigned int * list);
	std::string GetClassName();
	void SetClassName(std::string name);
	unsigned int verticesSize, indicesSize;
private:

	float * vertices;
	unsigned int *indexLayout;
	std::string className;
};