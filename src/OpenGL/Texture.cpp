#include "Texture.h"



Texture::Texture(const std::string& path)
: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1); //Flip texture around the horizontal, OpenGL expect pixel coords from bottom left
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    if(m_LocalBuffer == NULL)
    {
        std::cout << "invalid texture image" << std::endl;
    }
    else
    {
        GLCall(glGenTextures(1, &m_RendererID));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

        //Disse 4 må spesiferes. 
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));//min filer, hvordan man skalerer ned bildet når bildet er mindre enn original
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));// samme bare opp
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer))//GL_RGBA8 hvordan opengl skal håndere dataen(internal format)
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
        
        if(m_LocalBuffer)
            stbi_image_free(m_LocalBuffer);
    }
}

Texture::Texture(unsigned int width, unsigned int height, unsigned char* data)
: m_RendererID(0), m_FilePath("empty"), m_LocalBuffer(data), m_Width(width), m_Height(height), m_BPP(0)
{
        GLCall(glGenTextures(1, &m_RendererID));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

        //Disse 4 må spesiferes. 
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));//min filer, hvordan man skalerer ned bildet når bildet er mindre enn original
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));// samme bare opp
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Width, m_Height, 0, GL_RED, GL_UNSIGNED_BYTE, m_LocalBuffer))//GL_RGBA8 hvordan opengl skal håndere dataen(internal format)
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
        
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::UnBind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}