#pragma once
#include "RenderableObject.h"
#include "Camera.h"
class skybox : public RenderableObject {
public:
	skybox(Camera *tracker);
	~skybox();
	void OnUpdate();

private :
	Camera * tracer;
};