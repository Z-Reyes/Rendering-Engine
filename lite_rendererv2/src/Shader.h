#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};
class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	//caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath, bool vf);
	~Shader();

	void Bind() const;
	void Unbind() const;
	unsigned int GetmID();

	//Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniform4fv(const std::string& name, const float*  in);
	void SetUniform3fv(const std::string& name, const float*  in);
	void SetUniform1f(const std::string& name, const float in);
	unsigned int GetUniformLocation(const std::string& name);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader, bool vf);

};