#include<GL/glew.h>
#include<tuple>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>

#include "testLog.h"
#include "utilities.h"


std::tuple<std::string, std::string> parseShader(const std::string& filePath){
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream,line))
    {
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        } else if(type != ShaderType::NONE) {
            ss[(int)type] << line << "\n";
        }
    }
    stream.close();
    return { ss[0].str(), ss[1].str() };
}


unsigned int compileShader(unsigned int type, const std::string& source){
    GLCallSetValue( unsigned int id , glCreateShader(type));
    const char* src = source.c_str();
    GLCall( glShaderSource(id, 1, &src, nullptr));
    GLCall( glCompileShader(id));

    int result;
    GLCall( glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE){
        int length;
        GLCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall( glGetShaderInfoLog(id, length, &length, message));
        testLog("Failed to compile shader!, type==>");
        testLog((type == GL_VERTEX_SHADER) ? "vertex" : "fragent");
        testLog(message);
        GLCall( glDeleteShader(id));
        return 0;
    }

    return id;
}


unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader){
    GLCallSetValue( unsigned int program , glCreateProgram());
    GLCallSetValue( unsigned int vs , compileShader(GL_VERTEX_SHADER, vertexShader));
    GLCallSetValue( unsigned int fs , compileShader(GL_FRAGMENT_SHADER, fragmentShader));

    GLCall(glAttachShader(program, vs));
    GLCall( glAttachShader(program, fs));
    GLCall( glLinkProgram(program));
    GLCall( glValidateProgram(program));

    GLCall( glDeleteShader(vs));
    GLCall( glDeleteShader(fs));

    return program;
}