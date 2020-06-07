#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Utility.h"
#include "Texture.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct Character {
    Texture* texture;//unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Position;
    unsigned int Advance;
};

struct TextBox
{
    std::string text;
    unsigned int x;
    unsigned int y;
    glm::vec3 color;
};

class TextFreetype
{
public:
    TextFreetype(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<IndexBuffer> ib,
                 std::shared_ptr<Renderer> renderer, std::shared_ptr<Shader> shader,
                 std::shared_ptr<VertexArray> vao, glm::mat4 mvp);
    ~TextFreetype();

    void SetText(std::string text, unsigned int textID, unsigned int x, 
                 unsigned int y, glm::vec3 color);
    void RenderText(std::string text, unsigned int x, unsigned int y, glm::vec3 color);
    void Render();

private:
    void Initialize();

    std::shared_ptr<Renderer> m_Renderer;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    std::shared_ptr<VertexArray> m_VAO;
    
    std::unique_ptr<Texture> m_TestTexture;
    std::vector<std::unique_ptr<Texture>> m_Textures;

    glm::mat4 m_MVP;

    std::map<char, Character> m_Characters;
    std::map<unsigned int, TextBox> m_TextBoxes;

};