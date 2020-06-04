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

    private:
        std::map<char, Character> m_Characters;


        glm::mat4 m_ProjMatrix;

        VertexData m_VertexData;
        Texture* m_TestTexture;

        Renderer m_Renderer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;

        FT_Face m_Face;
        FT_Library m_Library;


    };
}