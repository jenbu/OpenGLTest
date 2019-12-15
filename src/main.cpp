#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

using namespace std;



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
    window = glfwCreateWindow(1024, 768, "Test", NULL, NULL);
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

    static const GLfloat g_vertex_buffer_data[] = {
    -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, 1.0f, 1.0f,
     -0.5f, 0.5f, 0.0f, 1.0f 
     //1.0f, 1.0f
    };

    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0//,
       // 4, 1, 2
    };

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    VertexArray va;
    VertexBuffer vbo(g_vertex_buffer_data, 4*4*sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vbo, layout);

    IndexBuffer ibo(indices, sizeof(indices)/sizeof(unsigned int));


    Shader shader("res/basic.shader");
    shader.Bind();
    //shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

    Texture texture("res/Textures/cherno.png");
    texture.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    va.UnBind();
    shader.UnBind();
    vbo.UnBind();
    ibo.UnBind();

    Renderer renderer;

    float red = 1.0f;
    bool decrement = true;
    
    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        renderer.Clear();
        
        shader.Bind();
        //shader.SetUniform4f("u_Color", red, 0.0f, 0.0f, 1.0f);


        renderer.Draw(va, ibo, shader);


        glfwSwapBuffers(window);
        glfwPollEvents();

        if(red > 0.0f && decrement)
        {
            red -= 0.01f;
        }
        else if(red <= 1.0f && !decrement)
        {
            red += 0.01f;
        }
        else
        {
            decrement = !decrement;
        }
        

    } //while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    
    glfwTerminate();

    return 0;
}
