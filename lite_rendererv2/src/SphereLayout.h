#pragma once

#include "RenderableObjectLayout.h"
struct vertexContainer {
	float x;
	float y;
	float z;
	float s;
	float t;
};
class SphereLayout : public RenderableObjectLayout {

public:
	SphereLayout();
	~SphereLayout();
};