#pragma once

#include "BaseObject.h"
#include "RectangleObject.h"
#include "CircleObject.h"
#include "EBMath.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <vector>

struct VertexData
{
    std::vector<float> VertexPosition;
    std::vector<unsigned int> VertexIndices;
};

class ObjectHandler
{
    public:
        ObjectHandler();
        ~ObjectHandler();

        inline VertexData GetVertexData() { return { m_VertexCoords, m_Indices }; }
        inline std::vector<BaseObject*> GetObjectsData() { return m_Objects; }
        inline unsigned int GetObjectCount() { return m_ObjectCount; }

        void Clear();

        template<typename T>
        RectangleObject* AddObject(glm::vec3 pos, glm::vec3 vel, float width, float height)
        {
            
        }

        template<typename T>
        CircleObject* AddObject(glm::vec3 pos, glm::vec3 vel, float radius, unsigned int resolution)
        {
            
        }

    private:

        void Update();

        static ObjectHandler* instance;

        std::vector<BaseObject*> m_Objects;
        unsigned int m_ObjectCount;
        unsigned int m_VertexCount;

        std::vector<float> m_VertexCoords;
        std::vector<unsigned int> m_Indices;        

};