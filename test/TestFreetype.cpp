#include "TestFreetype.h"

namespace test
{
    TestFreetype::TestFreetype()
    : m_ProjMatrix(glm::ortho(0.0f, 800.0f, 0.0f, 600.0f))
    {
        

        //m_TestTexture = new Texture("res/Textures/cherno.png");
        //m_TestTexture->Bind(0);


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        
        if(InitializeFT())
            std::cout << "Error initializing Freetype!" << std::endl;
        
    }

    TestFreetype::~TestFreetype()
    {
        
    }

    int TestFreetype::InitializeFT()
    {
        int error = FT_Init_FreeType(&m_Library);
        if(error)
            std::cout << "Some error freetype lib" << std::endl;
        
 
        error = FT_New_Face(m_Library,
                            "/usr/share/fonts/truetype/freefont/FreeSans.ttf",
                            0,
                            &m_Face);
        if(error == FT_Err_Unknown_File_Format)
            std::cout << "loading font error freetype lib" << std::endl;
        else if(error)
            std::cout << "Some other error related to FT_New_Face" << std::endl;

        error = FT_Set_Pixel_Sizes(m_Face, 0, 80);
        if(error)
            std::cout << "Some error related to FT_Set_Char_Size()" << std::endl;


        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        if(FT_Load_Char(m_Face, 200, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
        }

        float xpos = 100 + m_Face->glyph->bitmap_left * 1.0;
        float ypos = 100 - m_Face->glyph->bitmap_top * 1.0;

        float w = m_Face->glyph->bitmap.width * 1.0;
        float h = m_Face->glyph->bitmap.rows * 1.0;

        float vertices[] = {
             xpos,     ypos + h,   0.0f, 0.0f,            
             xpos,     ypos,       0.0f, 1.0f,
             xpos + w, ypos,       1.0f, 1.0f,
             xpos + w, ypos + h,   1.0f, 0.0f    
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(2); //Vertex coordinates
        layout.Push<float>(2); //Texture coordinates

        m_VAO = std::make_unique<VertexArray>();
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        //m_IndexBuffer = std::make_unique<IndexBuffer>(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());
        m_Shader = std::make_unique<Shader>("res/freetype_shader.shader"); 
        m_Shader->Bind();

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices)/sizeof(unsigned int));
        
        //render glyph texture over quad
        //GLCall(glBindTexture(GL_TEXTURE_2D, ch.TextureID));



        //m_TestTexture = new Texture(face->glyph->bitmap.width, face->glyph->bitmap.rows,
        //                   face->glyph->bitmap.buffer);
        //m_TestTexture->Bind(0);
        //m_TestTexture = new Texture("res/Textures/cherno.png");
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


        //FT_Done_Face(face);
        //FT_Done_FreeType(m_Library);

        return error;
    }

    void TestFreetype::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
    {
        static int letterInc = 0;

        letterInc++;
        Texture* tempTexture;
        if(letterInc >= 10)
        {
            letterInc = 0;
            static int charInc = 65; // 0 starter på 49 
            std::cout << charInc << std::endl;
            if(FT_Load_Char(m_Face, charInc, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            }

            float xpos = 100 + m_Face->glyph->bitmap_left * 1.0;
            float ypos = 100 - m_Face->glyph->bitmap_top * 1.0;

            float w = m_Face->glyph->bitmap.width * 1.0;
            float h = m_Face->glyph->bitmap.rows * 1.0;

            float vertices[] = {
                xpos,     ypos + h,   0.0f, 0.0f,            
                xpos,     ypos,       0.0f, 1.0f,
                xpos + w, ypos,       1.0f, 1.0f,
                xpos + w, ypos + h,   1.0f, 0.0f    
            };
            charInc++;

            m_VertexBuffer->SetBufferData(vertices, sizeof(vertices));
            tempTexture = new Texture(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows,
                        m_Face->glyph->bitmap.buffer);
            tempTexture->Bind(0);
        }


        //m_TestTexture->Bind(0);


        glm::mat4 mvp = glm::mat4(1.0f)* m_ProjMatrix;
        m_Shader->Bind();
        m_Shader->SetUniform3f("textColor", color.x, color.y, color.z);
        m_Shader->SetUniformMat4f("projection", mvp);

        //m_VAO->Bind();
        m_Renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

    }

    void TestFreetype::OnUpdate(float deltaTime)
    {

    }

    void TestFreetype::OnRender()
    {
    }

    void TestFreetype::OnImGuiRender()
    {
        RenderText("C", 100.0f, 100.0f, 5.0f, glm::vec3(1.0f, 0.1f, 0.1f));

    }

}