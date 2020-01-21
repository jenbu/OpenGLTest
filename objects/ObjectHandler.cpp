#include "ObjectHandler.h"

ObjectHandler* ObjectHandler::instance = 0;

ObjectHandler::ObjectHandler()
{
    m_ObjectCount = 0;
}

ObjectHandler* ObjectHandler::GetInstance()
{
    if(!instance)
    {
        instance = new ObjectHandler;
    }
    return instance;
}

template<>
void ObjectHandler::AddObject<RectangleObject>(glm::vec3 pos, float width, float height)
{
    ++m_ObjectCount;
    std::cout << "AddObject: m_ObjectCount: " << m_ObjectCount << "Pos: ("<< pos.x << "," << pos.y << "," << pos.z << ")" << std::endl;
    RectangleObject tempRect(pos.x, pos.y, pos.z, width, height, 100);
    m_Objects.push_back(&tempRect);
    
    std::vector<float> customPos{ -width/2,  height/2, 
                                   width/2,  height/2,
                                  -width/2, -height/2,
                                   width/2, -height/2};
    m_VertexCoords.insert(m_VertexCoords.end(), customPos.begin(), customPos.end());

    std::vector<unsigned int> addIndicesVec{(0+(m_ObjectCount-1)*4), (2+(m_ObjectCount-1)*4), (3+(m_ObjectCount-1)*4),
                                            (3+(m_ObjectCount-1)*4), (1+(m_ObjectCount-1)*4), (0+(m_ObjectCount-1)*4)};
    m_Indices.insert(m_Indices.end(), addIndicesVec.begin(), addIndicesVec.end());

    m_IndexOffsets.push_back(tempRect.GetNumIndices()*(m_ObjectCount-1));
}