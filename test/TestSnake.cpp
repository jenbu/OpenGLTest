#include "TestSnake.h"

namespace test
{
    void TestFunc()
    {
        std::cout << "TestFunc msg: "  << std::endl;
    }


    TestSnake::TestSnake()
    : m_Proj(glm::ortho(0.0f, (float)ResolutionWidth, 0.0f, (float)ResolutionHeight, -1.0f, 1.0f)), 
      m_GridNum(10), m_Gridx(m_GridNum/2), m_Gridy(m_GridNum/2), m_xPixelOffset(0), m_yPixelOffset(0),
      m_SnakeDirection(Direction::Up), m_UDPComm(new Communication::UDPClass), m_GamePaused(true)
    {
        FT_Library library;
        FT_Face face;
        int error = FT_Init_FreeType(&library);
        if(error)
            std::cout << "Some error freetype lib" << std::endl;
        
        error = FT_New_Face(library,
                            "/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf",
                            0,
                            &face);
        if(error == FT_Err_Unknown_File_Format)
            std::cout << "loading font error freetype lib" << std::endl;
        else if(error)
            std::cout << "Some other error related to FT_New_Face" << std::endl;

        error = FT_Set_Char_Size(face, 0, 16*64, 300, 300);
        if(error)
            std::cout << "Some error related to FT_Set_Char_Size()" << std::endl;
            

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
        m_ObjSnakeBody.push_back(m_objectHandler->AddObject<RectangleObject>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), (float)m_gridPixelSize, (float)m_gridPixelSize));
        m_SnakePos.push_back({m_Gridx, m_Gridy});
        m_Food = m_objectHandler->AddObject<CircleObject>(glm::vec3(100, 100, 0), glm::vec3(0, 0, 0), (float)(m_gridPixelSize/3), (unsigned int) 43);
        m_FoodPos = { 3, 4 };
        SetGridPos(m_Food, m_FoodPos.x, m_FoodPos.y);


        //Boundary objects
        m_ObjBackground.push_back(m_objectHandler->AddObject<RectangleObject>(glm::vec3(m_xPixelOffset/2, (float)ResolutionHeight/2, 0), glm::vec3(0, 0, 0), (float)m_xPixelOffset, (float)ResolutionHeight));
        m_ObjBackground.push_back(m_objectHandler->AddObject<RectangleObject>(
            glm::vec3(3*m_xPixelOffset/2 + m_gridPixelSize*m_GridNum, (float)ResolutionHeight/2, 0), glm::vec3(0, 0, 0), (float)m_xPixelOffset, (float)ResolutionHeight));
        

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

        m_UDPComm->UDPInit(std::bind(&TestSnake::SnakeMsgHandler, this, std::placeholders::_1));
        char abc[40] = "hei";
        //m_UDP.MessageHandler(abc);
        m_lastTime = clock();
        m_TickPeriod = CLOCKS_PER_SEC/4;
        //ResetGame();
        
        
    }

    TestSnake::~TestSnake()
    {
        delete m_UDPComm;
    }

    void TestSnake::SnakeMsgHandler(char* msg)
    {
        std::cout << "SnakeMsgHandler msg: "  << msg << std::endl;
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
        if(!m_GamePaused)
        {
            if(clock() - m_lastTime >  m_TickPeriod)
            {
                GameTick();
                //std::cout << "tick" << std::endl; 
                m_lastTime = clock();
            }
        }


        for(int i = 0; i < m_objectHandler->GetObjectCount(); i++)
        {
            glm::mat4 mvp = glm::mat4(1.0f)* m_Proj* glm::translate(glm::mat4(1.0f), m_Objects[i]->GetPosition());
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer.DrawInRange(*m_VAO, *m_IndexBuffer, *m_Shader, m_Objects[i]->GetIndicesOffset(), m_Objects[i]->GetIndicesSize());

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

        glm::vec3 newSqrPos = glm::vec3(((m_xPixelOffset - m_gridPixelSize/2) + m_SnakePos[m_SnakePos.size()-1].x*m_gridPixelSize),
                                         (m_yPixelOffset+m_SnakePos[m_SnakePos.size()-1].y*m_gridPixelSize - m_gridPixelSize/2),
                                         0);

        m_ObjSnakeBody.push_back(m_objectHandler->AddObject<RectangleObject>(newSqrPos, glm::vec3(0, 0, 0), (float)m_gridPixelSize, (float)m_gridPixelSize));
        m_Objects = m_objectHandler->GetObjectsData();
        m_VertexData = m_objectHandler->GetVertexData();
        m_VertexBuffer->SetBufferData(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
        m_IndexBuffer->SetIndexBuffer(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());

        std::cout << "m_Objects size: " << m_Objects.size() << std::endl;
    }

    void TestSnake::SetSnakePos(int& x, int& y)
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
                SetGridPos(m_ObjSnakeBody[k], m_SnakePos[k].x, m_SnakePos[k].y);
            }

        }
        //Set head pos
        m_SnakePos[0].x = x;
        m_SnakePos[0].y = y;
        SetGridPos(m_ObjSnakeBody[0], m_SnakePos[0].x, m_SnakePos[0].y);

        if(IsEating())
        {
            EatingConsequence();
        }

    }

    void TestSnake::SetGridPos(BaseObject* obj, int x, int y)
    {
            glm::vec3 posvec = glm::vec3( ((m_xPixelOffset-m_gridPixelSize/2) + x*m_gridPixelSize),
                                          ((m_yPixelOffset - m_gridPixelSize/2) + y*m_gridPixelSize),
                                            0 );    
            obj->SetObjectPos(posvec);
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

    bool TestSnake::IsEating()
    {
        if(m_FoodPos.x == m_SnakePos[0].x && m_FoodPos.y == m_SnakePos[0].y)
            return true;

        return false;
    }

    void TestSnake::EatingConsequence()
    {
        AddBodySquare();
        unsigned int randX, randY;
        //Check to prevent food to spawn in snake
        bool inSnake;
        do
        {
            inSnake = false;
            randX = rand() % m_GridNum + 1;   
            randY = rand() % m_GridNum + 1;

            for(int i = 0; i < m_SnakePos.size(); i++)
            {
                if(randX == m_SnakePos[i].x && randY == m_SnakePos[i].y)
                    inSnake = true;
            }
        } while (inSnake);
        


        m_FoodPos.x = randX; m_FoodPos.y = randY;
        SetGridPos(m_Food, randX, randY);   
        std::cout << "Eating!" << std::endl;
    }

    void TestSnake::KeyEvents()
    {
        switch(m_InputInstance->GetKeyState())
        {
            case KeyboardEvent::ArrowUp:
            {
                m_GamePaused = false;
                m_SnakeDirection = Direction::Up;
                //++m_Gridy;
                //SetSnakePos(m_Gridx, m_Gridy);              
                break;
            }
            case KeyboardEvent::ArrowDown:
            {   
                m_SnakeDirection = Direction::Down;
                //--m_Gridy;
                //SetSnakePos(m_Gridx, m_Gridy);
                break;
            }
            case KeyboardEvent::ArrowLeft:
            {
                m_SnakeDirection = Direction::Left;
                //--m_Gridx;
                //SetSnakePos(m_Gridx, m_Gridy);
                break;
            }
            case KeyboardEvent::ArrowRight:
            {
                m_SnakeDirection = Direction::Right;
                //++m_Gridx;
                //SetSnakePos(m_Gridx, m_Gridy);
                break;
            }
            case KeyboardEvent::KeyE:
            {
                AddBodySquare();
                break;
            }
            case KeyboardEvent::KeySpacebar:
            {
                std::cout << "Pausing game" << std::endl;
                m_GamePaused = !m_GamePaused;
            }
            default:
                break;
        }
    }

    void TestSnake::GameTick()
    {
        switch(m_SnakeDirection)
        {
            case Direction::Up:
            {
                ++m_Gridy;
                SetSnakePos(m_Gridx, m_Gridy);              
                break;
            }
            case Direction::Down:
            {   
                --m_Gridy;
                SetSnakePos(m_Gridx, m_Gridy);
                break;
            }
            case Direction::Left:
            {
                --m_Gridx;
                SetSnakePos(m_Gridx, m_Gridy);
                break;
            }
            case Direction::Right:
            {
                ++m_Gridx;
                SetSnakePos(m_Gridx, m_Gridy);
                break;
            }
            default:
            {
                std::cout << "Invalid direction, error!" << std::endl;
                break;
            }
        }
    }

    void TestSnake::ResetGame()
    {
        std::cout << "***Game Over***" << std::endl;
        m_GamePaused = true;
        m_Gridx = m_GridNum/2;
        m_Gridy = m_GridNum/2;
        
        m_SnakePos.clear();
        delete m_Food;
        m_ObjSnakeBody.clear();
        m_SnakePos.push_back({m_Gridx, m_Gridy});



        m_objectHandler->Clear();
        m_ObjSnakeBody.push_back(m_objectHandler->AddObject<RectangleObject>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), (float)m_gridPixelSize, (float)m_gridPixelSize));
        m_Food = m_objectHandler->AddObject<CircleObject>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), (float)(m_gridPixelSize/3), (unsigned int) 8);

        //Boundary objects
        m_objectHandler->AddObject<RectangleObject>(glm::vec3(m_xPixelOffset/2, (float)ResolutionHeight/2, 0), glm::vec3(0, 0, 0), (float)m_xPixelOffset, (float)ResolutionHeight);
        m_objectHandler->AddObject<RectangleObject>(glm::vec3(3*m_xPixelOffset/2 + m_gridPixelSize*m_GridNum, (float)ResolutionHeight/2, 0), glm::vec3(0, 0, 0), (float)m_xPixelOffset, (float)ResolutionHeight);

        m_Objects = m_objectHandler->GetObjectsData();
        m_VertexData = m_objectHandler->GetVertexData();
        m_VertexBuffer->SetBufferData(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
        m_IndexBuffer->SetIndexBuffer(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());

        glm::vec3 posvec = glm::vec3((m_xPixelOffset + m_Gridx*m_gridPixelSize/2),
                                    ((m_yPixelOffset - m_gridPixelSize/2) + m_Gridy*m_gridPixelSize),
                                      0);
        m_Objects[0]->SetObjectPosVelAcc(posvec,
                                         glm::vec3(0,0,0),
                                         glm::vec3(0,0,0));

        m_FoodPos = { 3, 3 };
        SetGridPos(m_Food, m_FoodPos.x, m_FoodPos.y);
      

    }

}