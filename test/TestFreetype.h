#pragma once

#include <memory>
#include <vector>
#include <map>

#include "Test.h"
#include "Utility.h"
#include "imgui/imgui.h"
#include "Constants.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ObjectHandler.h"
#include "Texture.h"

#include "BaseObject.h"
#include "RectangleObject.h"
#include "CircleObject.h"
#include "TextFreetype.h"

#include "GLAbstractionInterface.h"

#include "ft2build.h"
#include FT_FREETYPE_H

namespace test {

    struct Character {
        unsigned int TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
    };

    class TestFreetype : public Test
    {
    public:
        TestFreetype();
        ~TestFreetype();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        int InitializeFT();
        void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

        void Reset();

    private:
        //std::map<char, Character> m_Characters;
        GLAbstractionInterface* m_GLApi;
        

        glm::mat4 m_ProjMatrix;

        VertexData m_VertexData;
        Texture* m_TestTexture;
        std::unique_ptr<ObjectHandler> m_ObjHandler;

        std::shared_ptr<Renderer> m_Renderer;
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VAO;
        std::shared_ptr<IndexBuffer> m_IndexBufferTest;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;

        std::unique_ptr<TextFreetype> m_Text;

        FT_Face m_Face;
        FT_Library m_Library;


    };
}