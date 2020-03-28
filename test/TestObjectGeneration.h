#ifndef TESTOBJECTGENERATION_H
#define TESTOBJECTGENERATION_H

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "RectangleObject.h"
#include "ObjectHandler.h"
#include "Physics/NewtonianPhysics.h"
#include "Constants.h"
#include "ImGuiMenu.h"
#include "ImGuiSubMenu.h"
#include "MouseEventHandler.h"
#include "MouseManipulator.h"
#include "SATCollisionDetection.h"



#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>



namespace test
{

    class TestObjectGeneration : public Test 
    {
    public:
        TestObjectGeneration();
        ~TestObjectGeneration();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
        void CursorEventUpdate(double x, double y, bool lclk) override { m_CursPos.x = x; m_CursPos.y = y; m_lBtnClicked = lclk; }


    private:

        void MenuInit();
        void MenuEvents();

        double m_LastTime;
        glm::dvec2 m_CursPos;
        bool m_lBtnClicked;
        MouseEventHandler* m_mouseEvent;
        MouseManipulator* m_Manipulator;

        glm::mat4 m_Proj;
        glm::ivec3 m_NewObjCoords;
        glm::ivec2 m_NewRectProps;
        std::vector<glm::vec3> m_ObjsPos;
        
        
        std::vector<BaseObject*> m_Objects;
        ObjectHandler* m_ObjectHandler;
        VertexData m_VertexData;
        NewtonianPhysics* m_Physics;
        double m_TimeStep;
        bool m_NewObjMenu, m_TogglePhysics, m_TimeStepApply, m_NewObject;
        bool m_tempbool, m_ApplyPosChange;

        int m_NewRectPos[3];
        int m_NewRectSize[2];

        ImGuiMenu* m_Menu;
        ImGuiSubMenu* m_Submenu;
        
        
        Renderer m_Renderer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        
        
    };


}

#endif