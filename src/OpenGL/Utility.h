#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <GL/glew.h>
#include "glm/glm.hpp"

#define ASSERT(x) if(!(x)) __builtin_trap();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

glm::mat3 Transformation2D(float rot, float x, float y);


#endif