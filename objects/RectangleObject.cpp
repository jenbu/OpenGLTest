#include "RectangleObject.h"

unsigned int RectangleObject::m_RectCount = 0;

RectangleObject::RectangleObject(float x = 0, float y = 0, float rot = 0, unsigned int width = 100, unsigned int height = 100, float mass = 100)
: m_Width(width), m_Height(height), BaseObject(x, y, rot, mass)
{
    ++m_RectCount;
    std::string rectName("Rectangle ");
    rectName.append(std::to_string(m_RectCount));
    this->SetName(rectName);

    m_IndexOffsets.push_back((m_ObjectCount-1)*6);

    //To do: hindre duplikater
    addRectData((float)width, (float)height);


}

RectangleObject::~RectangleObject()
{

}

void RectangleObject::DrawObject()
{

}

void RectangleObject::addRectData(float width, float height)
{
    std::vector<float> customPos{ -width/2,  height/2, 
                                   width/2,  height/2,
                                  -width/2, -height/2,
                                   width/2, -height/2};
    m_VertexCoords.insert(m_VertexCoords.end(), customPos.begin(), customPos.end());

    std::vector<unsigned int> addIndicesVec{(0+(m_RectCount-1)*4), (2+(m_RectCount-1)*4), (3+(m_RectCount-1)*4),
                                            (3+(m_RectCount-1)*4), (1+(m_RectCount-1)*4), (0+(m_RectCount-1)*4)};
    m_Indices.insert(m_Indices.end(), addIndicesVec.begin(), addIndicesVec.end());
}
