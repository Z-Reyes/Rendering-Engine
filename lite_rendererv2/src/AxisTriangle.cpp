#include "AxisTriangle.h"

AxisTriangle::AxisTriangle()
{
	verticesSize = 15;
	float positions[]{
		0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
		0.25f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.25f, 0.0f, 0.0f, 1.0f, 0.0f
	};
	SetVertices(positions);
	indicesSize = 3;

	unsigned int indices[]{
		0,1,2
	};
	SetIndices(indices);
	SetClassName("AxisTriangle");
}

AxisTriangle::~AxisTriangle()
{
}
