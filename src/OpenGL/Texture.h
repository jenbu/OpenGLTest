#ifndef TEXTURE_H
#define TEXTURE_H


#include "Utility.h"
#include "stb_image.h"



class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    Texture(const std::string& path);
    Texture(unsigned int width, unsigned int height, unsigned char* data);
    ~Texture();

    inline unsigned int GetTextureID() { return m_RendererID; }

    void Bind(unsigned int slot) const;//different texture slots depending on system.
    void UnBind() const;

    inline int GetWidth() const     { return m_Width; }
    inline int GetHeight() const    { return m_Height; }
};

#endif