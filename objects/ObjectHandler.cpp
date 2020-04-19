#include "ObjectHandler.h"

//ObjectHandler* ObjectHandler::instance = 0;

ObjectHandler::ObjectHandler()
{
    m_ObjectCount = 0;
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
    std::cout << latestObj << " m_Objects size: " << m_Objects.size() << std::endl; 
    BaseObject* obj = m_Objects[latestObj];
    std::vector<float> vertices = obj->GetBaseVertices(); std::cout << obj->GetBaseVertices()[0] << std::endl;
    std::vector<unsigned int> indices = obj->GetBaseIndices();

    m_VertexCoords.insert(m_VertexCoords.end(), vertices.begin(), vertices.end());
    m_Indices.insert(m_Indices.end(), indices.begin(), indices.end());
    m_IndexOffsets.push_back(obj->GetIndexOffset());
}

void ObjectHandler::Clear()
{
    m_ObjectCount = 0;

    m_Indices.clear();
    m_IndexOffsets.clear();
    m_VertexCoords.clear();
    m_Objects.clear();
}


template<>
void ObjectHandler::AddObject<RectangleObject>(glm::vec3 pos, glm::vec3 vel, float width, float height)
{
    ++m_ObjectCount;
    std::cout << "AddObject: m_ObjectCount: " << m_ObjectCount << "Pos: ("<< pos.x << "," << pos.y << "," << pos.z << ")" << std::endl;
    std::vector<EBMath::Vertex2D> vertices{  {-width/2,  height/2}, 
                                             { width/2,  height/2},
                                             {-width/2, -height/2},
                                             { width/2, -height/2} };
    
    std::vector<unsigned int> indices{ (0+(m_ObjectCount-1)*4), (2+(m_ObjectCount-1)*4), (3+(m_ObjectCount-1)*4),
                                       (3+(m_ObjectCount-1)*4), (1+(m_ObjectCount-1)*4), (0+(m_ObjectCount-1)*4) };
    

    RectangleObject* tempRect = new RectangleObject(pos, vel, {vertices, indices, 6*(m_ObjectCount-1)},
                                                    0, width, height, 100);
    m_Objects.push_back(tempRect);
    
    Update();
}

template<>
void ObjectHandler::AddObject<CircleObject>(glm::vec3 pos, glm::vec3 vel, float radius, unsigned int resolution)
{
    ++m_ObjectCount;
    //std::cout << "AddObject: m_ObjectCount: " << m_ObjectCount << "Pos: ("<< pos.x << "," << pos.y << "," << pos.z << ")" << std::endl;
    std::vector<EBMath::Vertex2D> vertices;
    std::vector<unsigned int> indices{ (0+(m_ObjectCount-1)*4), (2+(m_ObjectCount-1)*4), (3+(m_ObjectCount-1)*4),
                                       (3+(m_ObjectCount-1)*4), (1+(m_ObjectCount-1)*4), (0+(m_ObjectCount-1)*4) };
    
    float theta = 0.0f, x = 0.0f, y = 0.0f;
    float angleStep = 2*M_PI/(float)resolution;

    vertices.push_back({pos.x, pos.y});
    vertices.push_back({(pos.x + radius*cos(theta))});
    
    for(theta = 0.0f; theta < M_PI; theta += angleStep)
    {
        x = radius*cos(theta);
        y = radius*sin(theta);
        vertices.push_back({(pos.x + x), (pos.y + y)});

    }

    CircleObject* tempCircle = new CircleObject(10, pos, vel, {vertices, indices, 6*(m_ObjectCount-1)}, 0.0f, 10.0f);
    m_Objects.push_back(tempCircle);
}