#include "ObjectHandler.h"

ObjectHandler::ObjectHandler()
: m_VertexCount(0), m_ObjectCount(0)
{
}

ObjectHandler::~ObjectHandler()
{
    for(std::vector<BaseObject *>::iterator it = m_Objects.begin(); it != m_Objects.end(); it++)
    {
        delete *it;
    }
}

void ObjectHandler::Update()
{
    //Add latest object to vertices vec and index vecs
    int latestObj = m_Objects.size()-1;
    BaseObject* obj = m_Objects[latestObj];
    std::vector<float> vertices = obj->GetBaseVertices();
    std::vector<unsigned int> indices = obj->GetBaseIndices();

    m_VertexCoords.insert(m_VertexCoords.end(), vertices.begin(), vertices.end());
    m_Indices.insert(m_Indices.end(), indices.begin(), indices.end());
}

void ObjectHandler::Clear()
{
    m_ObjectCount = 0;
    m_VertexCount = 0;

    m_Indices.clear();
    m_VertexCoords.clear();
    m_Objects.clear();
}


template<>
RectangleObject* ObjectHandler::AddObject<RectangleObject>(glm::vec3 pos, glm::vec3 vel, float width, float height)
{
    ++m_ObjectCount;
    std::vector<EBMath::Vertex2D> vertices{  {-width/2,  height/2}, 
                                             { width/2,  height/2},
                                             {-width/2, -height/2},
                                             { width/2, -height/2} };
    
    std::vector<unsigned int> indices{ (0+ m_VertexCount), (2+m_VertexCount), (3+m_VertexCount),
                                       (3+ m_VertexCount), (1+m_VertexCount), (0+m_VertexCount) };


    
    RectangleObject* tempRect = new RectangleObject(pos, vel, {vertices, indices, m_Indices.size()},
                                                    0, width, height, 100);
    m_Objects.push_back(tempRect);
    m_VertexCount += vertices.size();
    
    Update();

    return tempRect;
}

template<>
BaseObject* ObjectHandler::AddObject<CircleObject>(glm::vec3 pos, glm::vec3 vel, float radius, unsigned int resolution)
{
    ++m_ObjectCount;
    
    std::vector<EBMath::Vertex2D> vertices;
    std::vector<unsigned int> indices;
    
    float theta = 0.0f, x = 0.0f, y = 0.0f;
    float angleStep = 2*M_PI/(float)resolution;

    
    std::vector<EBMath::Vertex2D> circlePos;
    unsigned int currentVecSize;
    vertices.push_back( {pos.x, pos.y} );

    for(theta = 0.0f; theta <= 2*M_PI; theta += angleStep)
    {
        x = radius*cos(theta);
        y = radius*sin(theta);
        vertices.push_back( {(pos.x + x), (pos.y + y)} );
    }

    for(int i = 2; i < vertices.size(); i++)
    {
        indices.push_back(0+ m_VertexCount); //Center pos
        indices.push_back(i - 1 + m_VertexCount);
        indices.push_back(i + m_VertexCount);

    }
    
    CircleObject* tempCircle = new CircleObject(10, pos, vel, {vertices, indices, m_Indices.size()}, 0.0f, 10.0f);
    m_Objects.push_back(tempCircle);
    m_VertexCount += vertices.size();


    Update();

    return tempCircle;
}