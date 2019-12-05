#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define ASSERT(x) if(!(x)) __builtin_trap();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

ShaderProgramSource readShader(const std::string& path)
{
    std::ifstream file(path);
    //file.open(path, std::ifstream::in);


    std::string line;

    if(!file.is_open())
    {
        cout << "couldnt open that file!" << endl;
        return {"0", "0"};
    }

    enum ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    ShaderType shaderType = ShaderType::NONE;
    std::stringstream ss[2];
    
    while(getline(file, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                shaderType = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                shaderType = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)shaderType] << line << "\n";
        }        
    }

    return { ss[0].str(), ss[1].str() };
}

static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        cout << "[OpenGL Error]: (" << error << ")" << function << " " << file << ":" << line << endl;
        return false;
    }
    return true;
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char message[length]; 
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "Vertex shader": "Fragment shader") << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));

        return 0;
    }
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);    
    
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

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

    GLuint VertexArrayID;
    GLCall(glGenVertexArrays(1, &VertexArrayID));
    GLCall(glBindVertexArray(VertexArrayID));

    static const GLfloat g_vertex_buffer_data[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,
     -0.5f, 0.5f,
     1.0f, 1.0f
    };

    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0,
        4, 1, 2
    };

    GLuint vertexbuffer;
    GLCall(glGenBuffers(1, &vertexbuffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW));

    //layout of the actual buffer
    GLCall(glEnableVertexAttribArray(0));

    GLCall(glVertexAttribPointer(
            0,                  // bind the current buffer with vertex array object 0
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            2*sizeof(float),    // stride
            0            // array buffer offset
            ));
            
    GLuint ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));



    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));

    ShaderProgramSource shaderSources = readShader("res/basic.shader");

    //cout << "Vertex Shader:\n" << shaderSources.vertexSource << endl;
    //cout << "Fragment Shader:\n" << shaderSources.fragmentSource << endl;

    unsigned int program = CreateShader(shaderSources.vertexSource, shaderSources.fragmentSource);
    cout << "program: " << program << endl;
    GLCall(glUseProgram(program));

    float red = 1.0f;
    bool decrement = true;
    //Get uniform color variable
    GLCall(int location = glGetUniformLocation(program, "u_Color"));
    ASSERT(location != -1);
    GLCall(glUniform4f(location, red, 0.0f, 0.0f, 1.0f));

    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        glClear( GL_COLOR_BUFFER_BIT );
        
        // 1st attribute buffer : vertices
        //glEnableVertexAttribArray(0);

        GLCall(glUniform4f(location, red, 0.0f, 0.0f, 1.0f));

        // Draw the triangle !
        //GLClearError();
        GLCall(glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr)); //second arg is the number of INDICESE
        //GLCheckError();



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
