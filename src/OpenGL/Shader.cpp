#include "Shader.h"

Shader::Shader(const std::string& filepath) 
: m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = readShader(filepath);
    m_RendererID = CreateShader(source.vertexSource, source.fragmentSource);

}

Shader::~Shader()
{
    //GLCall(glDeleteShader(m_RendererID));
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char message[length]; 
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "Vertex shader": "Fragment shader") << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));

        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader); 
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);    
    
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

ShaderProgramSource Shader::readShader(const std::string& path)
{
    std::ifstream file(path);
    //file.open(path, std::ifstream::in);


    std::string line;

    if(!file.is_open())
    {
        std::cout << "couldnt open that file!" << std::endl;
        return {"0", "0"};
    }

    enum ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    ShaderType shaderType = ShaderType::NONE;
    std::stringstream ss[2];

    while(getline(file, line))
    {   

        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                shaderType = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                shaderType = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)shaderType] << line << "\n";
        }        
    }

    return { ss[0].str(), ss[1].str() };
}


void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}

//Set uniforms
void Shader::SetUniform1i(const std::string& name, int value)
{   
    int location = GetUniformLocation(name);
    GLCall(glUniform1i(location, value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{   
    int location = GetUniformLocation(name); 
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    int location = GetUniformLocation(name); 
    GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0])); 
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform3f(location, v0, v1, v2));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if(location == -1)
        std::cout << "Warning: uniform '" << name << "' doesnt exist!" << std::endl;
    else
        m_UniformLocationCache[name] = location;
    
    return location;
}