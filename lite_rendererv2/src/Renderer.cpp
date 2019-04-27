#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "lightStruct.h"
#include "ShadowBucket.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
void GLClearError()
{
	//declare all the errors
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError()) {
		std::cout << "[OPENGL Error] (" << error << ")" << " " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::SetPerspection(glm::mat4 per)
{
	m_Proj = per;
}



void Renderer::PassOne(RenderableObject * toBeDrawn) {
	std::string classN = toBeDrawn->GetObjectClassName();
	Shader *shadowShader = shaderList.at(1);
	shadowShader->Bind();

	glm::vec3 origin = glm::vec3(0.0);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 currLoc = glm::vec3(globalLight.position[0], globalLight.position[1],globalLight.position[2]);
	//shadowData.lightV_matrix = glm::mat4(1.0f); //removal could cause a breaking point
	//shadowData.lightP_matrix = glm::mat4(1.0f);
	shadowData.lightV_matrix = glm::lookAt(currLoc, origin, up);
	//std::cout << glm::to_string(shadowData.lightV_matrix) << std::endl;
	shadowData.lightP_matrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); //maybe change later.
	shadowData.shadowMVP = shadowData.lightP_matrix * shadowData.lightV_matrix * toBeDrawn->GetModel();
	//std::cout << glm::to_string(shadowData.shadowMVP) << std::endl;
	shadowShader->SetUniformMat4f("shadowMVP",shadowData.shadowMVP);

	shapeList.at(classN)->Bind();
	vbList.at(classN)->Bind();
	
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDrawElements(GL_TRIANGLES, indexList.at(classN)->GetCount(), GL_UNSIGNED_INT, nullptr));
	shapeList.at(classN)->Unbind(); //Some issues may be caused in passone.

}

void Renderer::DrawNow(RenderableObject * toBeDrawn)
{
	//std::cout << "Calling draw " << std::endl;

	//PassOne(toBeDrawn);

	Texture *s = tList.at("Shadow");
	s->Bind();

	///////////////
	std::string classN = toBeDrawn->GetObjectClassName();
	//std::cout << "Getting shader at location: " << toBeDrawn->GetShaderNum() << std::endl;
	Shader *m_Shader = shaderList.at(toBeDrawn->GetShaderNum());
	//std::cout << m_Shader->GetmID() << std::endl;
	//need to bind texture.
	Texture * t = tList.at(toBeDrawn->GetTextureName());
	t->Bind(1);
	m_Shader->Bind();
	//std::cout << "Made it past binding call" << std::endl;
	glm::mat4 mv = vTemp * toBeDrawn->GetModel();
	//glm::mat4 mv = toBeDrawn->GetModel();
	//Let's make a full one shall we?
	//glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(globalLight.position[0], globalLight.position[1], globalLight.position[2]));
	//glm::mat4 mv = shadowData.lightV_matrix * toBeDrawn->GetModel();
	//std::cout << glm::to_string(mv) << std::endl;
	
	glm::mat4 nm = glm::inverse(glm::transpose(mv));

	////
	shadowData.shadowMVP2 = shadowData.b * shadowData.lightP_matrix * shadowData.lightV_matrix * toBeDrawn->GetModel();
	//std::cout << glm::to_string(shadowData.b) << std::endl;
	m_Shader->SetUniformMat4f("shadowMVP2", shadowData.shadowMVP2);
	////
	
	//Insert matrices:
	m_Shader->SetUniformMat4f("m_matrix", toBeDrawn->GetModel());
	m_Shader->SetUniformMat4f("mv_matrix", mv);
	m_Shader->SetUniformMat4f("proj_matrix", m_Proj);
	m_Shader->SetUniformMat4f("norm_matrix", nm);

	//m_Shader->SetUniform1i("shTex", 0);

	//m_Shader->SetUniformMat4f("u_MVP", mvp );
	m_Shader->SetUniform1i("u_Texture", 1);

	//First the gloabl ambient
	m_Shader->SetUniform4fv("globalAmbient", globalLight.ambientAura);

	//next, positional light
	m_Shader->SetUniform4fv("light.ambient", globalLight.ambientLight);
	m_Shader->SetUniform4fv("light.diffuse", globalLight.diffuseLight);
	m_Shader->SetUniform4fv("light.specular", globalLight.specularLight);
	m_Shader->SetUniform3fv("light.position", globalLight.position);

	m_Shader->SetUniform4fv("material.ambient", toBeDrawn->GetMaterial().ambient);
	m_Shader->SetUniform4fv("material.diffuse", toBeDrawn->GetMaterial().diffuse);
	m_Shader->SetUniform4fv("material.specular", toBeDrawn->GetMaterial().specular);
	m_Shader->SetUniform1f("material.shininess", toBeDrawn->GetMaterial().shiny);

	

	shapeList.at(classN)->Bind();
	vbList.at(classN)->Bind();

	//GLCall(glDrawArrays(GL_TRIANGLES, 0, 7000));
	GLCall(glDrawElements(GL_TRIANGLES, indexList.at(classN)->GetCount(), GL_UNSIGNED_INT, nullptr));
	shapeList.at(classN)->Unbind();
}



void Renderer::AddShader(Shader *newShader)
{
	shaderList.push_back(newShader);
}

void Renderer::AddTexture(std::string name, Texture * t)
{
	tList.insert({ name, t });
}

void Renderer::AddNewShape(RenderableObjectLayout newLayout, VertexBufferLayout layout)
{
	//Gonna involve the most work.
	VertexArray *m_VAO = new VertexArray(); //may also need work done. (std::make unique).
	std::cout << "mVAO id value is: " << m_VAO->GetRenderID() << std::endl;
	//may cause issues.
	VertexBuffer * m_VBO = new VertexBuffer(newLayout.GetVertices(), newLayout.verticesSize * sizeof(float));
	m_VAO->AddBuffer(*m_VBO, layout);
	IndexBuffer *m_IndexBuffer = new IndexBuffer(newLayout.GetIndexLayout(), newLayout.indicesSize);
	shapeList.insert({ newLayout.GetClassName(), m_VAO });
	vbList.insert({ newLayout.GetClassName(), m_VBO });
	indexList.insert({newLayout.GetClassName(), m_IndexBuffer});
	m_VAO->Unbind();
}

void Renderer::AddRenderQueue(RenderableObject * addition)
{
	renderList.push_back(addition);
}

void Renderer::AddUpdateQueue(RenderableObject * uAddition)
{
	updateList.push_back(uAddition);
}

void Renderer::DrawSkybox() {
	vTemp = currCam->GetTRMatrix();
	std::string classN = currSkybox->GetObjectClassName();
	currSkybox->SetModelTranslation(0,0,0);
	//std::cout << "Getting shader at location: " << currSkybox->GetShaderNum() << std::endl;
	Shader *m_Shader = shaderList.at(currSkybox->GetShaderNum());
	//std::cout << m_Shader->GetmID() << std::endl;
	//need to bind texture.
	Texture * t = tList.at(currSkybox->GetTextureName());
	t->Bind();
	m_Shader->Bind();
	//std::cout << "Made it past binding call" << std::endl;

	glm::mat4 mvp = m_Proj * vTemp * currSkybox->GetModel();
	m_Shader->SetUniformMat4f("u_MVP", mvp);
	//std::cout << glm::to_string(m_Proj) << std::endl;
	//std::cout << glm::to_string(vTemp) << std::endl;
	//std::cout << glm::to_string(currSkybox->GetModel()) << std::endl;
	//std::cout << glm::to_string(mvp) << std::endl;
	m_Shader->SetUniform1i("u_Texture", 0);
	shapeList.at(classN)->Bind();
	vbList.at(classN)->Bind();
	GLCall(glDisable(GL_DEPTH_TEST));
	GLCall(glDrawElements(GL_TRIANGLES, indexList.at(classN)->GetCount(), GL_UNSIGNED_INT, nullptr));
	shapeList.at(classN)->Unbind();
	GLCall(glEnable(GL_DEPTH_TEST));
	//std::cout << "Drawing " << indexList.at(classN)->GetCount() << " edges" << std::endl;
	//std::cout << "just drew sky box " << std::endl;
}

void Renderer::DrawRenderQueue()
{
	//glClearDepth(GLfloat)
	//GLCall(gl_Clear(GL_DEPTH_BUFFER_BIT));

	vTemp = currCam->GetTRMatrix();
	///Draw the skybox.
	//DrawSkybox();


	///
	///we update the objects in the scene and then draw the shadows.
	////

	//////////////
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, shadowData.shadow_buffer));

	GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowData.shadow_texId, 0)); //Possible breaking point.

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "uh oh" << std::endl;
	}
	GLCall(glClear(GL_DEPTH_BUFFER_BIT)); //May cause problems
	GLCall(glDrawBuffer(GL_NONE));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_POLYGON_OFFSET_FILL));
	GLCall(glPolygonOffset(2.0f, 4.0f));
	//GLCall(glClear(GL_DEPTH_BUFFER_BIT)); //May cause problems

	for (RenderableObject *r : renderList) {
		r->DrawCall(this, glm::mat4(1.0f), glm::mat4(1.0f));
	}
	//GLCall(glClear(GL_DEPTH_BUFFER_BIT)); //May cause problems
	GLCall(glDisable(GL_POLYGON_OFFSET_FILL));
	///////////////
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	GLCall(glClear(GL_DEPTH_BUFFER_BIT)); //May cause problems
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDrawBuffer(GL_FRONT));
	for (RenderableObject *r : renderList) {
		r->QuickDraw(this);
	}

	//Let's try clearing the frame buffer now.
	//GLCall(glBindFramebuffer(GL_FRAMEBUFFER, shadowData.shadow_buffer));

	//GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowData.shadow_texId, 0)); //Possible breaking point.
	//GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	//GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void Renderer::UpdateObjects()
{
	for (RenderableObject *r : updateList) {
		r->OnUpdate();
	}
}

void Renderer::SetSkybox(RenderableObject * sky)
{
	currSkybox = sky;
}

//void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
//	shader.Bind();
//	va.Bind();
//	//ib.Bind() is not technically necessary apparently because
	//va is already bound to ib (by other code).
//	ib.Bind();

//	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
//}