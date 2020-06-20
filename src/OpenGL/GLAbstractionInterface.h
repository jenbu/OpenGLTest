#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "TextFreetype.h"

#include "ObjectHandler.h"
#include "BaseObject.h"
#include "RectangleObject.h"
#include "CircleObject.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


class GLAbstractionInterface
{

    public:
        GLAbstractionInterface(unsigned int res_width, unsigned int res_height);
        ~GLAbstractionInterface();


        void Test();
        inline void Clear() { m_ObjHandler->Clear(); }

        int AddText(std::string text, unsigned int x, unsigned int y);
        void SetText(unsigned int id, std::string text);
        void Render();

        template<typename T>
        T* AddObject(glm::vec3 pos, unsigned int width, unsigned int height);
        template<typename T>
        T* AddObject(glm::vec3 pos, float radius);
    
    private:
        void UpdateBuffers();

        std::unique_ptr<TextFreetype> m_Text;
        unsigned int m_TextCount;

        glm::mat4 m_Proj;
        VertexData m_VertexData;

        std::unique_ptr<ObjectHandler> m_ObjHandler;
        std::vector<BaseObject*> m_Objects;

        std::unique_ptr<Renderer> m_Renderer;
        std::unique_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;

};

template<>
inline RectangleObject* GLAbstractionInterface::AddObject<RectangleObject>(glm::vec3 pos, unsigned int width, unsigned int height)
{
    RectangleObject* tempRect = m_ObjHandler->AddObject<RectangleObject>(pos, glm::vec3(0, 0, 0), (float)width, (float)height);
    UpdateBuffers();
    return tempRect;
}

template<>
inline CircleObject* GLAbstractionInterface::AddObject<CircleObject>(glm::vec3 pos, float radius)
{
    CircleObject* tempCirc = m_ObjHandler->AddObject<CircleObject>(pos, glm::vec3(0, 0, 0), (float)radius, (unsigned int)30);
    UpdateBuffers();
    return tempCirc;
}
