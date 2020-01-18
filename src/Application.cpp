#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "TestClearColor.h"
#include "TestTexture2D.h"
#include "TestRectangle2D.h"
#include "TestLines.h"
#include "TestObjectGeneration.h"
#include "Utility.h"

using namespace std;

std::vector<double> mousePos = { 0.0, 0.0 };


int main(int, char**) {


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
    test::TestClearColor test;

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTexture2D>("Texture2D");
    testMenu->RegisterTest<test::TestRectangle2D>("RectangleColor2D");
    testMenu->RegisterTest<test::TestLines>("Lines");
    testMenu->RegisterTest<test::TestObjectGeneration>("ObjectGeneration");


    int counterFPS = 0;
    double lastTime;
    int displayFPSCounter = 0;
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        renderer.Clear();
        lastTime = glfwGetTime();

        ImGui_ImplGlfwGL3_NewFrame();

        if(currentTest)
        {
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
        
        if(displayFPSCounter >= 40)
        {
            counterFPS = (int)1.0/((double)(glfwGetTime()-lastTime));
            std::cout << counterFPS << std::endl;
            displayFPSCounter = 0;

        }
        ++displayFPSCounter;
        
    }
    
    delete currentTest;
    if(currentTest != testMenu)
        delete testMenu;

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}
