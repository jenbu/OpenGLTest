#include "TestSnake.h"

namespace test
{
    TestSnake::TestSnake()
    : m_Proj(glm::ortho(0.0f, (float)ResolutionWidth, 0.0f, (float)ResolutionHeight, -1.0f, 1.0f)), 
      m_GridNum(26), m_Gridx(m_GridNum/2), m_Gridy(m_GridNum/2), m_xPixelOffset(0), m_yPixelOffset(0)
        {
        
        int startX;  
        if(ResolutionWidth >= ResolutionHeight)
        {
            m_gridPixelSize = ResolutionHeight/m_GridNum;
            m_xPixelOffset = (ResolutionWidth - ResolutionHeight)/2;
        }
        else
            m_gridPixelSize = ResolutionWidth/m_GridNum;
    
        std::cout << "Grid size: " << m_GridNum << " Grid pixel size: " << m_gridPixelSize << std::endl;


        m_InputInstance = InputEventHandler::GetInstance();
        
        m_objectHandler = new ObjectHandler();
        m_objectHandler->AddObject<RectangleObject>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), (float)m_gridPixelSize, (float)m_gridPixelSize);
        m_SnakePos.push_back({m_Gridx, m_Gridy});

        m_Objects = m_objectHandler->GetObjectsData();
        m_VertexData = m_objectHandler->GetVertexData();


        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());
        m_Shader = std::make_unique<Shader>("res/basic_color.shader"); 
        m_Shader->Bind();

        m_Toggle = false;


    }

    TestSnake::~TestSnake()
    {
    }

    void TestSnake::OnUpdate(float deltaTime)
    {

    }

    void TestSnake::OnRender()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    }

    void TestSnake::OnImGuiRender()
    {
        KeyEvents();

        for(int i = 0; i < m_VertexData.ObjectIndexOffset.size(); i++)
        {
            glm::mat4 mvp = glm::mat4(1.0f)* m_Proj* glm::translate(glm::mat4(1.0f), m_Objects[i]->GetPosition());
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer.DrawInRange(*m_VAO, *m_IndexBuffer, *m_Shader, m_VertexData.ObjectIndexOffset[i]);

        }
    }

    void TestSnake::AddBodySquare()
    {
        
        if(m_SnakePos.size() > 0)
            m_SnakePos.push_back(m_SnakePos[m_SnakePos.size()-1]);
        std::cout << "New square with pos: (" << m_SnakePos[m_SnakePos.size()-1].x << ", " << m_SnakePos[m_SnakePos.size()-1].y << ")"
                  << std::endl << "Square count: " << m_SnakePos.size() << std::endl;

        for(int d = 0; d < m_SnakePos.size(); d++)
        {
            std::cout << "m_SnakePos[" << d << "] (x, y): (" << m_SnakePos[d].x << ", " << m_SnakePos[d].y << ")" << std::endl; 
        }

        glm::vec3 newSqrPos = glm::vec3((m_xPixelOffset+m_SnakePos[m_SnakePos.size()-1].x*m_gridPixelSize),
                                         (m_yPixelOffset+m_SnakePos[m_SnakePos.size()-1].y*m_gridPixelSize - m_gridPixelSize/2),
                                         0);

        m_objectHandler->AddObject<RectangleObject>(newSqrPos, glm::vec3(0, 0, 0), (float)m_gridPixelSize, (float)m_gridPixelSize);
        m_Objects = m_objectHandler->GetObjectsData();
        m_VertexData = m_objectHandler->GetVertexData();
        m_VertexBuffer->SetBufferData(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
        m_IndexBuffer->SetIndexBuffer(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());

        std::cout << "m_Objects size: " << m_Objects.size() << std::endl;
    }

    void TestSnake::SetGridPos(int& x, int& y)
    {
        CollisionType boundaryCollision = CollisionType::NoCollision;

        boundaryCollision = Collision(x, y);
        
        if(boundaryCollision != CollisionType::NoCollision)
        {
            ResetGame();
            return;
        }

        if(x > m_GridNum || x < 1)
        {
            if(x >= m_GridNum)
                x = m_GridNum;
            else
                x = 1;            
        }
        if(y >= m_GridNum || y <= 1)
        {
            if(y >= m_GridNum)
                y = m_GridNum;
            else
                y = 1;            
        }
        


        //Set pos rest of body 
        if(boundaryCollision == CollisionType::NoCollision)
        {
            for(int k = (m_SnakePos.size()-1); k >= 1; k--)
            {
                m_SnakePos[k] = m_SnakePos[k-1];
                std::cout << "m_SnakePos[" << k << "] (x, y): (" << m_SnakePos[k].x << ", " << m_SnakePos[k].y << ")" << std::endl; 

                glm::vec3 posvec = glm::vec3((m_xPixelOffset + m_SnakePos[k].x*m_gridPixelSize),
                                            ((m_yPixelOffset - m_gridPixelSize/2) + m_SnakePos[k].y*m_gridPixelSize),
                                            0);
                m_Objects[k]->SetObjectPosVelAcc(posvec,
                                                glm::vec3(0,0,0),
                                                glm::vec3(0,0,0));
            }
            std::cout << "m_SnakePos[" << 0 << "] (x, y): (" << x << ", " << y << ")" << std::endl; 

        }
        //Set head pos
        m_SnakePos[0].x = x;
        m_SnakePos[0].y = y;
        glm::vec3 posvec = glm::vec3((m_xPixelOffset + x*m_gridPixelSize),
                                    ((m_yPixelOffset - m_gridPixelSize/2) + y*m_gridPixelSize),
                                      0);
        m_Objects[0]->SetObjectPosVelAcc(posvec,
                                         glm::vec3(0,0,0),
                                         glm::vec3(0,0,0));
    }

    CollisionType TestSnake::Collision(int x, int y)
    {
        if((x > m_GridNum || x < 1) || (y > m_GridNum || y < 1))
        {
            return CollisionType::Boundary;
        }

        for(int i = 1; i < m_SnakePos.size(); i++)
        {
            if(x == m_SnakePos[i].x && y == m_SnakePos[i].y)
                return CollisionType::Snake;
        }

        return CollisionType::NoCollision;
    }

    void TestSnake::KeyEvents()
    {
        switch(m_InputInstance->GetKeyState())
        {
            case KeyboardEvent::ArrowUp:
            {
                ++m_Gridy;
                SetGridPos(m_Gridx, m_Gridy);              
                break;
            }
            case KeyboardEvent::ArrowDown:
            {   
                --m_Gridy;
                SetGridPos(m_Gridx, m_Gridy);
                break;
            }
            case KeyboardEvent::ArrowLeft:
            {
                --m_Gridx;
                SetGridPos(m_Gridx, m_Gridy);
                break;
            }
            case KeyboardEvent::ArrowRight:
            {
                ++m_Gridx;
                SetGridPos(m_Gridx, m_Gridy);
                break;
            }
            case KeyboardEvent::KeyE:
            {
                AddBodySquare();
                break;
            }
            default:
                break;
        }
    }

    void TestSnake::ResetGame()
    {
        m_Gridx = m_GridNum/2;
        m_Gridy = m_GridNum/2;
        
        m_SnakePos.clear();
        m_SnakePos.push_back({m_Gridx, m_Gridy});


        m_objectHandler->Clear();
        m_objectHandler->AddObject<RectangleObject>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), (float)m_gridPixelSize, (float)m_gridPixelSize);

        m_Objects = m_objectHandler->GetObjectsData();
        m_VertexData = m_objectHandler->GetVertexData();
        m_VertexBuffer->SetBufferData(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
        m_IndexBuffer->SetIndexBuffer(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());

        glm::vec3 posvec = glm::vec3((m_xPixelOffset + m_Gridx*m_gridPixelSize),
                                    ((m_yPixelOffset - m_gridPixelSize/2) + m_Gridy*m_gridPixelSize),
                                      0);
        m_Objects[0]->SetObjectPosVelAcc(posvec,
                                         glm::vec3(0,0,0),
                                         glm::vec3(0,0,0));
        

    }
}