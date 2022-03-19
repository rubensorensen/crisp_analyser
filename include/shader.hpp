
#ifndef SHADER_HPP
#define SHADER_HPP

#include <unordered_map>

#include <stdint.h>
#include <string>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
  public:

    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

  private:

    int GetUniformLocation(const std::string& name);
    ShaderProgramSource ParseShader(const std::string& filepath);
    uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    static uint32_t CompileShader(uint32_t type, const std::string& source);

    uint32_t m_RendererID;
    std::string m_Filepath;
    std::unordered_map<std::string, int> m_UniformLocationCache;
};

#endif  // SHADER_HPP