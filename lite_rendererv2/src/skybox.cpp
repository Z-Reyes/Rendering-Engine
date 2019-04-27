#include "skybox.h"

skybox::skybox(Camera *tracker)
{
	tracer = tracker;
	SetClassName("Cube");
	SetTextureName("Default");
	SetDefault();
	SetShaderNumber(2);
	SetScale(1.0f);
	SetRotation(0, 0, 1, 0);
	SetModelTranslation(0, 0, 0);
	//rotationCarry = 0;
	SetHasParent(false);
	SetParentRotation(false);
	SetParentTranslationFirst(false);
	SetSelfTranslationFirst(false);
}

skybox::~skybox()
{
}

void skybox::OnUpdate()
{
	glm::vec3 transfer = tracer->GetCameraLocation();
	//std::cout << -transfer.x << ", " << -transfer.y << ", " << -transfer.z << std::endl;
	
	SetModelTranslation(-transfer.x, -transfer.y, -transfer.z);
	UpdateSelf();
}
