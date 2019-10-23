#pragma once

#define DEBUG
//#define WINDOWS  /* uncomment this line to use it for windows.*/ 

#include <iostream>

#ifdef DEBUG
    #define ASSERT(x) if (!(x)) __builtin_trap()
    #define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
    /*#define GLCallSetValue(type_and_variable, func) GLClearError();\
        type_and_variable = func;\
        ASSERT(GLLogCall(#func, __FILE__, __LINE__))*/

#else
    #define ASSERT(x) 
    #define GLCall(x) x
    //#define GLCallSetValue(type_and_variable, func) type_and_variable = func
#endif



void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
std::string GetCurrentWorkingDir();