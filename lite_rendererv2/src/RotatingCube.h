#pragma once
#include "RenderableObject.h"

class RotatingCube : public RenderableObject {
public:
	RotatingCube(bool hp, bool usePR, bool pTransFirst, bool selfTransFirst);
	RotatingCube();
	~RotatingCube();
	void OnUpdate();

private:
	float rotationCarry;
};