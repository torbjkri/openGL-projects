#pragma once

#include <string>
#include <unordered_map>


struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;

	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(const unsigned int type, const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader );

	int GetUniformLocation(const std::string &name) const;

public:
	Shader(const std::string& filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform4f(const std::string& name, const float v1, const float v2, const float v3, const float v4);
};
