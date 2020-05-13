#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <time.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "TestClearColor.h"
#include "TestTexture2D.h"
#include "TestRectangle2D.h"
#include "TestLines.h"
#include "TestObjectGeneration.h"
#include "TestSnake.h"
#include "Utility.h"
#include "Constants.h"
#include "InputEventHandler.h"




//UDPClientServer::UDPClient testUDP("localnet", 20001);

using namespace std;

std::vector<double> mousePos = { 0.0, 0.0 };

void mouseButtonCb(GLFWwindow* window, int button, int action, int mods)
{
    std::cout << "MouseButtonCallback" << std::endl;
}




int main(int, char**) {

    //Communication::UDPClass test;
    //test.UDPInit();

    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize glfw!");
        return -1;
    }


    //glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // When running core, we have to create our own vertex array, COMPAt has one set up by default
    
    GLFWwindow* window;
    window = glfwCreateWindow(1280, 720, "Test", NULL, NULL);
    if(window == NULL)
    {

        fprintf(stderr, "Failed to open GLFW window.");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    
    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Circle");
    testMenu->RegisterTest<test::TestTexture2D>("Texture2D");
    testMenu->RegisterTest<test::TestRectangle2D>("RectangleColor2D");
    testMenu->RegisterTest<test::TestLines>("Lines");
    testMenu->RegisterTest<test::TestObjectGeneration>("ObjectGeneration");
    testMenu->RegisterTest<test::TestSnake>("Snake");


    int counterFPS = 0;
    double lastTime;
    int displayFPSCounter = 0;
    clock_t time = clock();
    double const TicksPerFrame = CLOCKS_PER_SEC/FPS;
    double xCurs, yCurs;
    InputEventHandler* MouseInstance = InputEventHandler::GetInstance();
    glfwSetMouseButtonCallback(window, InputEventHandler::MouseButtonCallback);
    glfwSetKeyCallback(window, InputEventHandler::KeyboardCallback);
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        //Manual lock FPS due to vsync not working on every computer with glfwSwapInterval()
        //lastTime = glfwGetTime();
        

        if(clock()-time > TicksPerFrame)
        {
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();
            glfwGetCursorPos(window, &xCurs, &yCurs);
            MouseInstance->SetCursorPos(xCurs, yCurs);

            if(currentTest)
            {
                currentTest->CursorEventUpdate(xCurs, yCurs, (bool) glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT));
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if(currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();

                ImGui::Text(std::to_string(counterFPS).c_str());
                ImGui::End();
            }


            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            glfwGetCursorPos(window, &mousePos[0], &mousePos[1]);
            glfwSwapBuffers(window);
            glfwPollEvents();
            //glfwSetCursorPosCallback()
            
            counterFPS = CLOCKS_PER_SEC/(clock()-time);
            time = clock();
        }
        else
        {
            
        }
        
        /*
        if(displayFPSCounter >= 40)
        {
            counterFPS = (int)1.0/((double)(glfwGetTime()-lastTime));
            displayFPSCounter = 0;

        }
        ++displayFPSCounter;
        */
        
    }
    
    delete currentTest;
    if(currentTest != testMenu)
        delete testMenu;

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}
