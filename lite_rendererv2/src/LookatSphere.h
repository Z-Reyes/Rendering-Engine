#pragma once
#include "RenderableObject.h"
#include "lightStruct.h"
class LookAtSphere : RenderableObject {
public: LookAtSphere();
	~LookAtSphere();
	void OnUpdate();
};