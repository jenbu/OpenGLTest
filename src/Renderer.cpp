#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    std::string error_msg;
    while(GLenum error = glGetError())
    {
        switch (error)
        {
        case 1281:
            error_msg = "GL_INVALID_VALUE"; break;
        case 1282:
            error_msg = "GL_INVALID_OPERATION"; break;
        case 1280:
            error_msg = "GL_INVALID_ENUM"; break;
        default:
            error_msg = error;
            break;
        }
        std::cout << "[OpenGL Error]: (" << error_msg << ")" << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}