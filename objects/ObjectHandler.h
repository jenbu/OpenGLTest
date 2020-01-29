#pragma once

#include "BaseObject.h"
#include "RectangleObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <vector>

struct VertexData
{
    std::vector<float> VertexPosition;
    std::vector<unsigned int> VertexIndices;
    std::vector<unsigned int> ObjectIndexOffset;
};

class ObjectHandler
{
    public:

        static ObjectHandler* GetInstance();
        inline VertexData GetVertexData() { return { m_VertexCoords, m_Indices, m_IndexOffsets }; }
        inline std::vector<BaseObject*> GetObjectsData() { return m_Objects; }
        void PrintObjectsName();

        template<typename T>
        void AddObject(glm::vec3 pos, float width, float height)
        {
            
        }

    private:
        static ObjectHandler* instance;
        ObjectHandler();
        ~ObjectHandler();

        std::vector<BaseObject*> m_Objects;
        unsigned int m_ObjectCount;

        std::vector<float> m_VertexCoords;
        std::vector<unsigned int> m_Indices;
        std::vector<unsigned int> m_IndexOffsets;

};