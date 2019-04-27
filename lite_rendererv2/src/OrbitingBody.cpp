#include "OrbitingBody.h"
#include <math.h>
OrbitingBody::OrbitingBody(bool hp, bool usePR, bool pTransFirst, bool selfTransFirst)
{
	SetClassName("Sphere");
	SetTextureName("Default");
	SetDefault();
	SetShaderNumber(0);
	SetScale(1.0f);
	SetRotation(0, 0, 1, 0);
	SetModelTranslation(0, 0, 0);
	orbitalValue = 0;
	SetHasParent(hp);
	SetParentRotation(usePR);
	SetParentTranslationFirst(pTransFirst);
	SetSelfTranslationFirst(selfTransFirst);
	orbitalAdditive = 0.005f;
	radiusMulti = 5.0f;
}

OrbitingBody::OrbitingBody()
{
	SetClassName("Sphere");
	SetTextureName("Default");
	SetDefault();
	SetShaderNumber(0);
	SetScale(1.0f);
	SetRotation(0, 0, 1, 0);
	SetModelTranslation(0, 0, 0);
	orbitalValue = 0;
	SetHasParent(false);
	SetParentRotation(false);
	SetParentTranslationFirst(false);
	SetSelfTranslationFirst(false);
	orbitalAdditive = 0.005f;
	radiusMulti = 5.0f;
}

OrbitingBody::~OrbitingBody()
{

}

void OrbitingBody::OnUpdate()
{
	//SetRotation(0.0f, 0, 1, 0);
	orbitalValue += orbitalAdditive;
	float xPos = radiusMulti * cos(orbitalValue);
		float zPos = radiusMulti * sin(orbitalValue);
	SetModelTranslation(xPos, 0, zPos);
	SetRotation(5.0f * -orbitalValue, 0, 1, 0);
}
