#include "RotatingCube.h"

RotatingCube::RotatingCube(bool hp, bool usePR, bool pTransFirst, bool selfTransFirst)
{
	//RotatingCube::RotatingCube();
	SetClassName("Sphere");
	SetTextureName("Default");
	SetDefault();
	SetShaderNumber(0);
	SetScale(1.0f);
	SetRotation(0, 0, 1, 0);
	SetModelTranslation(-10, -10,-10);
	rotationCarry = 0; 
	SetHasParent(hp);
	SetParentRotation(usePR);
	SetParentTranslationFirst(pTransFirst);
	SetSelfTranslationFirst(selfTransFirst);
	//SetClassName("Cube");
}

RotatingCube::RotatingCube() {
	SetClassName("Sphere");
	SetTextureName("Default");
	SetDefault();
	SetShaderNumber(0);
	SetScale(1.0f);
	SetRotation(0, 0, 1, 0);
	SetModelTranslation(0,-10, -10);
	rotationCarry = 0;
	SetHasParent(false);
	SetParentRotation(false);
	SetParentTranslationFirst(false);
	SetSelfTranslationFirst(false);
}

RotatingCube::~RotatingCube() {

}

void RotatingCube::OnUpdate() {
	rotationCarry += 0.02f;
	if (rotationCarry >= 6.28) {
		rotationCarry = rotationCarry - 6.28f;
	}
	SetRotation(rotationCarry, 0, 1, 0);
	//SetModelTranslation(rotationCarry, 0, 0);
	
}