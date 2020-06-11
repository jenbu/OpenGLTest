#include "TextFreetype.h"

//TextFreetype::TextFreetype(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<IndexBuffer> ib,
//                           std::shared_ptr<Renderer> renderer, std::shared_ptr<Shader> shader,
//                           std::shared_ptr<VertexArray> vao, glm::mat4 mvp)
TextFreetype::TextFreetype(unsigned int font_size, glm::mat4 mvp)
: m_MVP(mvp), m_FontSize(font_size)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Initialize();
    m_VertexBuffer = std::make_shared<VertexBuffer>(nullptr, 0);
    VertexBufferLayout layout;
    layout.Push<float>(2); //Vertex coordinates
    layout.Push<float>(2); //Texture coordinates

    m_VAO = std::make_shared<VertexArray>();
    m_VAO->AddBuffer(*m_VertexBuffer, layout);
    m_Shader = std::make_shared<Shader>("res/freetype_shader.shader"); 
    //m_Shader->Bind();

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    m_IndexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices)/sizeof(unsigned int));



    
    m_Renderer = std::make_shared<Renderer>();
}

TextFreetype::~TextFreetype()
{
    //delete texture pointer in m_Characters
    std::cout << m_Characters.size() << std::endl;
    for(std::map<char, Character>::iterator it = m_Characters.begin(); it != m_Characters.end(); it++)
    {
        delete (*it).second.texture;
    }

}

void TextFreetype::Initialize()
{
    FT_Face face;
    FT_Library library;
    int error = FT_Init_FreeType(&library);
    if(error)
        std::cout << "Some error freetype lib" << std::endl;
    

    error = FT_New_Face(library,
                        "/usr/share/fonts/truetype/freefont/FreeSans.ttf",
                        0,
                        &face);
    if(error == FT_Err_Unknown_File_Format)
        std::cout << "loading font error freetype lib" << std::endl;
    else if(error)
        std::cout << "Some other error related to FT_New_Face" << std::endl;

    error = FT_Set_Pixel_Sizes(face, 0, m_FontSize);
    if(error)
        std::cout << "Some error related to FT_Set_Char_Size()" << std::endl;


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if(FT_Load_Char(face, 200, FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
    }

    for(int c = 32; c < 128; c++)
    {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
        }
        
        Texture* tempTexture = new Texture(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);

        std::cout << "textureid " << tempTexture->GetTextureID() << std::endl;

        Character character = {
            tempTexture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        m_Characters.insert(std::pair<char, Character>(c, character));
    }
    
    FT_Done_Face(face);
    FT_Done_FreeType(library);
}


void TextFreetype::AddText(std::string text, unsigned int textID, unsigned int x, unsigned int y, glm::vec3 color)
{
    //If not found, create. If found change TextBox.
    if(m_TextBoxes.find(textID) == m_TextBoxes.end())
        m_TextBoxes.insert(std::pair<unsigned int, TextBox>(textID, {text, x, y, color}));
    else
        m_TextBoxes[textID] = {text, x, y, color};
}

void TextFreetype::SetText(std::string text, unsigned int textID)
{
    //If not found, create. If found change TextBox.
    if(m_TextBoxes.find(textID) == m_TextBoxes.end())
    {
        std::cout << "No existing ID for the textbox" << std::endl;
        return;
    }
    else
        m_TextBoxes[textID].text = text;
}

void TextFreetype::RenderText(std::string text, unsigned int x, unsigned int y, glm::vec3 color)
{

    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++)
    {
        //std::cout << "charType: " << *c << std::endl;
        Character character = m_Characters[*c];

        float xpos = x + character.Position.x * 1.0;
        float ypos = y - (character.Size.y - character.Position.y) * 1.0;

        float w = character.Size.x * 1.0;
        float h = character.Size.y * 1.0;

        /*std::cout << "xpos: "       << xpos << " ypos: " << ypos
                    << " w: "         << w    << " h: "    << h     
                    << " TextureID: " << character.texture->GetTextureID() << std::endl;*/

        //TODO make it so that vertices and indeces are appended to the list containing object vertices and indeces

        float vertices[] = {
            xpos,     ypos + h,   0.0f, 0.0f,            
            xpos,     ypos,       0.0f, 1.0f,
            xpos + w, ypos,       1.0f, 1.0f,
            xpos + w, ypos + h,   1.0f, 0.0f    
        };
        x += (character.Advance >> 6);


        glm::mat4 matr = glm::mat4(1.0f) * glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

        m_VertexBuffer->SetBufferData(vertices, sizeof(vertices));
        character.texture->Bind(0);
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", color.x, color.y, color.z, 1.0f);
        m_Shader->SetUniformMat4f("u_MVP", matr);
        m_Renderer->Draw(*m_VAO, *m_IndexBuffer, *m_Shader);        
    }

}

void TextFreetype::Render()
{
    for(std::map<unsigned int, TextBox>::iterator it = m_TextBoxes.begin(); it != m_TextBoxes.end(); it++)
    {
        RenderText(it->second.text, it->second.x, it->second.y, it->second.color);
    }
}
