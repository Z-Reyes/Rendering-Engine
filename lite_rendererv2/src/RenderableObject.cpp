#include "RenderableObject.h"
#include "Renderer.h"

RenderableObject::RenderableObject(bool hp, bool usePR, bool pTransFirst, bool selfTransFirst) {
	hasParent = hp;
	usesParentRotation = usePR;
	parentTranslationFirst = pTransFirst;
	selfTranslationFirst = selfTransFirst;
}

void RenderableObject::DrawCall(Renderer *currRen, glm::mat4 pRotation, glm::mat4 pTranslation)
{
	glm::mat4 passTranslation = translation;
	glm::mat4 passRotation = rotation;
	if (selfTranslationFirst) {
		model = rotation * translation * scale;
	}
	else {
		model = translation * rotation * scale; //scale may need to be changed.
	}

	if (hasParent) {
		if (usesParentRotation) {
			if (parentTranslationFirst) {
				//model = model * pRotation * pTranslation;
				model = pRotation * pTranslation * model;
				passTranslation = pTranslation * passTranslation;
				passRotation = pRotation * passRotation;
			}
			else {
				//model = model * pTranslation * pRotation;
				model = pTranslation * pRotation * model;
				passTranslation = pTranslation * passTranslation;
				passRotation = pRotation * passRotation;
			}
		}
		else {
			//model = model * pTranslation;
			model = pTranslation * model;
			passTranslation = pTranslation * passTranslation;
		}
	}
	else {
		//do nothing.
	}

	currRen->PassOne(this);
	for (int j = 0; j < childList.size(); j++) {
		childList.at(j)->DrawCall(currRen, passRotation, passTranslation);
	}

}

std::string RenderableObject::GetObjectClassName()
{
	return objectClassName;
}

void RenderableObject::SetTextureName(std::string na)
{
	textureName = na;
}

std::string RenderableObject::GetTextureName()
{
	return textureName;
}

void RenderableObject::SetPosition(glm::vec3 in)
{
	position = glm::vec3(in.x, in.y, in.z);
}

unsigned int RenderableObject::GetShaderNum()
{
	return shaderNum;
}

void RenderableObject::AddChild(RenderableObject * child)
{
	childList.push_back(child);
}

void RenderableObject::SetModelTranslation(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
	translation = glm::translate(glm::mat4(1.0f), position);
}


void RenderableObject::SetScale(float size)
{
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(size));
	//scale = glm::mat4(size);
}
void RenderableObject::SetRotation(float radians, float xAxis, float yAxis, float zAxis)
{
	glm::vec3 rotationAxis = glm::vec3(xAxis, yAxis, zAxis);
	rotation = glm::rotate(radians,rotationAxis);
}
void RenderableObject::SetShaderNumber(unsigned int shaderNumIn) {
	shaderNum = shaderNumIn;
}
glm::mat4 RenderableObject::GetModel()
{
	return model;
}
void RenderableObject::SetClassName(std::string na)
{
	objectClassName = na;
}
void RenderableObject::SetHasParent(bool t)
{
	hasParent = t;
}
void RenderableObject::SetParentRotation(bool t)
{
	usesParentRotation = t;
}
void RenderableObject::SetParentTranslationFirst(bool t)
{
	parentTranslationFirst = t;
}
void RenderableObject::SetSelfTranslationFirst(bool t)
{
	selfTranslationFirst = t;
}
void RenderableObject::SetAmbient(float r, float g, float b, float a)
{
	objMaterial.ambient[0] = r;
	objMaterial.ambient[1] = g;
	objMaterial.ambient[2] = b;
	objMaterial.ambient[3] = a;
}
void RenderableObject::SetDiffuse(float r, float g, float b, float a)
{
	objMaterial.diffuse[0] = r;
	objMaterial.diffuse[1] = g;
	objMaterial.diffuse[2] = b;
	objMaterial.diffuse[3] = a;
}
void RenderableObject::SetSpecular(float r, float g, float b, float a)
{
	objMaterial.specular[0] = r;
	objMaterial.specular[1] = g;
	objMaterial.specular[2] = b;
	objMaterial.specular[3] = a;
}
void RenderableObject::QuickDraw(Renderer * currRen)
{
	currRen->DrawNow(this);
	for (int j = 0; j < childList.size(); j++) {
		childList.at(j)->QuickDraw(currRen);
	}
}
void RenderableObject::SetShiny(float sh)
{
	objMaterial.shiny = sh;
}

void RenderableObject::UpdateSelf()
{
	if (selfTranslationFirst) {
		model = rotation * translation * scale;
	}
	else {
		model = translation * rotation * scale; //scale may need to be changed.
	}
}

material RenderableObject::GetMaterial()
{
	return objMaterial;
}
void RenderableObject::SetDefault()
{
	float dv = 0.5f;
	SetAmbient(dv,dv,dv,1.0f);
	SetDiffuse(dv,dv,dv,1.0f);
	SetSpecular(dv,dv,dv,1.0f);
	SetShiny(dv);
}
//void RenderableObject::SetRotation(float radians, float xAxis, float yAxis, float zAxis)
//{

//}
