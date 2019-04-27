#include "lightMarker.h"

lightMarker::lightMarker()
{
	SetClassName("Sphere");
	SetTextureName("Default");
	SetDefault();
	SetShaderNumber(0);
	SetScale(0.1f);
	SetRotation(0, 0, 1, 0);
	SetModelTranslation(0, 0, 0);
	SetHasParent(false);
	SetParentRotation(false);
	SetParentTranslationFirst(false);
	SetSelfTranslationFirst(false);
}

lightMarker::~lightMarker()
{

}

void lightMarker::OnUpdate()
{
	SetModelTranslation(globalLight.position[0],globalLight.position[1],globalLight.position[2]);
}
