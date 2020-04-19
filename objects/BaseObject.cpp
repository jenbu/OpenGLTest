#include "BaseObject.h"

unsigned int BaseObject::m_ObjectCount = 0;

BaseObject::BaseObject(glm::vec3 pos, glm::vec3 vel, VertexIndexData vertexindexdata, 
                       float rot = 0.0f, float mass = 100)
 : m_Name("Base"), m_Mass(mass), m_PosVelAcc({glm::vec3(0,0,0), 
   glm::vec3(0,0,0), glm::vec3(0,0,0), 0}), m_Spring(100000), m_ObjPhysEnabled(true)
{
    ++m_ObjectCount;

    m_PosVec = pos;
    m_VelVec = vel;
    m_AccVec = glm::vec3(0, 0, 0);

    m_PosVelAcc.PosVec = pos;
    m_PosVelAcc.VelVec = vel;
    m_PosVelAcc.AccVec = glm::vec3(0, 0, 0);
    m_PosVelAcc.rot = 1231;

    m_VertexPosition = vertexindexdata.vertex2DVec;
    m_BaseVertices   = EBMath::ConvertVertex2DVecToFloatVec(vertexindexdata.vertex2DVec);
    m_IndexOffset    = vertexindexdata.IndexOffset;
    m_Indices        = vertexindexdata.indices;

    m_Color = {1.0f, 0.0f, 0.5f, 1.0f};
}

BaseObject::~BaseObject()
{

}

void BaseObject::TransformVertices(glm::mat4 mvp)
{
    //Unfinished
    glm::vec4 tempVec, tempResultVec;
    for(int i = 0; i < m_VertexPosition.size(); i++)
    {
        tempVec = glm::vec4(m_VertexPosition[i].x, m_VertexPosition[i].y, 1, 0);
        tempResultVec = mvp*tempVec;
        //m_VertexData[i] = mvp*m_VertexData;
    }
}

