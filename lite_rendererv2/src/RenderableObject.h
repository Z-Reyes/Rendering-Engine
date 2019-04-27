#pragma once
#include <iostream>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
class Renderer;
struct material {
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shiny;
};

class RenderableObject {
public:
	RenderableObject() {}
	RenderableObject(bool hp, bool usePR, bool pTransFirst, bool selfTransFirst);
	~RenderableObject() {}
	//RenderableObject(float size);
	virtual void OnUpdate() = 0;
	void DrawCall(Renderer *currRen, glm::mat4 pRotation, glm::mat4 pTranslation);

	unsigned int GetShaderNum();
	
	void AddChild(RenderableObject *child);
	void SetModelTranslation(float x, float y, float z);
	//void SetAbsoluteTranslation(float x, float y, float z);
	void SetScale(float size);
	void SetRotation(float radians, float xAxis, float yAxis, float zAxis);
	void SetShaderNumber(unsigned int shaderNumIn);
	
	glm::mat4 GetModel();
	void SetClassName(std::string na);
	std::string GetObjectClassName();
	void SetTextureName(std::string na);
	std::string GetTextureName();
	void SetPosition(glm::vec3 in);
	void SetHasParent(bool t);
	void SetParentRotation(bool t);
	void SetParentTranslationFirst(bool t);
	void SetSelfTranslationFirst(bool t);
	void SetAmbient(float r, float g, float b, float a);
	void SetDiffuse(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void QuickDraw(Renderer *currRen);
	void SetShiny(float sh);
	void UpdateSelf();
	material GetMaterial();
	void SetDefault();
private:
	material objMaterial;
	glm::mat4 scale, rotation, translation, model;
	glm::vec3 position;
	std::string objectClassName, textureName;
	unsigned int shaderNum;
	bool hasParent, usesParentRotation, parentTranslationFirst, selfTranslationFirst;
	std::vector<RenderableObject*> childList;
};