#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include "RenderableObject.h"
#include "IndexBuffer.h"
#include "RenderableObjectLayout.h"
#include "VertexArray.h"
#include "Camera.h"

#include <vector>
#include <iostream>
#include <unordered_map>
#include "texture.h"
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

class VertexBufferLayout;


bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
	void Clear() const;

	//void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void SetPerspection(glm::mat4 per);
	void PassOne(RenderableObject * toBeDrawn);
	void DrawNow(RenderableObject* toBeDrawn);

	void AddShader(Shader *newShader);
	void AddTexture(std::string name, Texture *t);
	void AddNewShape(RenderableObjectLayout newLayout, VertexBufferLayout layout);
	void AddRenderQueue(RenderableObject *addition);
	void AddUpdateQueue(RenderableObject *uAddition);
	void DrawRenderQueue();
	void UpdateObjects();
	void SetSkybox(RenderableObject *sky);
	void DrawSkybox();
	Camera* currCam;

private:
	glm::mat4 m_Proj, vTemp;
	std::vector<Shader*> shaderList;
	std::unordered_map<std::string, VertexArray*> shapeList;
	std::unordered_map<std::string, IndexBuffer*> indexList;
	std::unordered_map<std::string, VertexBuffer*> vbList;
	std::unordered_map<std::string, Texture*> tList;
	std::vector<RenderableObject *> renderList;
	std::vector<RenderableObject *> updateList;
	RenderableObject * currSkybox;

};