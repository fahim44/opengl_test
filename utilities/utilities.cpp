

#include<GL/glew.h>
#include<iostream>
#include<string>
#include<stdio.h>  /* defines FILENAME_MAX */

#ifdef WINDOWS
    #include<direct.h>
    #define GetCurrentDir _getcwd
#else
    #include<unistd.h>
    #define GetCurrentDir getcwd
#endif




void GLClearError(){
    while(glGetError() != GL_NO_ERROR);
}


bool GLLogCall(const char* function, const char* file, int line){
    while(GLenum error = glGetError()){
        std::cout << "[OpenGL Error] (" << error <<" (0x" << std::hex << error << ") File: "<< file <<
            " Function: "<< function << " line: " << std::dec << line <<" )\n";
        return false;
    }
    return true;
}


std::string GetCurrentWorkingDir() {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}