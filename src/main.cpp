#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
    while(GLenum error = glGetError())
    {
        cout << "[OpenGL Error]: (" << error << ")" << endl;
    }
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(GL_VERTEX_SHADER);;
}

static int CreateShader(const std::string vertexShader, const std::string fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
}

int main(int, char**) {


    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize glfw!");
        return -1;
    }


    /*glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
    */
    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "Test", NULL, NULL);
    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
     0.0f,  1.0f
    };    

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), g_vertex_buffer_data, GL_STATIC_DRAW);

    //layout of the actual buffer
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            2*sizeof(float),    // stride
            0            // array buffer offset
            );
            

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        glClear( GL_COLOR_BUFFER_BIT );
        
        // 1st attribute buffer : vertices
        //glEnableVertexAttribArray(0);

        // Draw the triangle !
        GLClearError();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        GLCheckError();



        glfwSwapBuffers(window);
        glfwPollEvents();

    } //while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    
    glfwTerminate();

    return 0;
}
