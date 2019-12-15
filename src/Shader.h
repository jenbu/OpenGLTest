#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "Utility.h"

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;

    //caching for uniforms, instead of retrieving ucolor location with getuniformlocation everytime 
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void UnBind() const;

    //Set uniforms
    void SetUniform1i(const std::string& name, int value);//used to tell shader what texture slot we want to sample from.
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    ShaderProgramSource readShader(const std::string& path);
    int GetUniformLocation(const std::string& name);
};

#endif