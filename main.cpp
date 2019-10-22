#define DEBUG

#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "testLog.h"
#include<iostream>
#include<tuple>
#include<fstream>
#include<string>
#include<sstream>

//for getting current path
#include<stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
    #include<direct.h>
    #define GetCurrentDir _getcwd
#else
    #include<unistd.h>
    #define GetCurrentDir getcwd
#endif

// error checking ---------------------------------------------for debug----------------------------------------
#ifdef DEBUG
    #define ASSERT(x) if (!(x)) __builtin_trap()
    #define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
    #define GLCallSetValue(return_type, func) GLClearError();\
        return_type = func;\
        ASSERT(GLLogCall(#func, __FILE__, __LINE__))

#else
    #define GLCall(x) x
    #define GLCallSetValue(return_type, func) return_type = func
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void GLClearError(){
    while(glGetError() != GL_NO_ERROR);
}


static bool GLLogCall(const char* function, const char* file, int line){
    while(GLenum error = glGetError()){
        std::cout << "[OpenGL Error] (" << error <<" (0x" << std::hex << error << ") File: "<< file <<
            " Function: "<< function << " line: " << std::dec << line <<" )\n";
        return false;
    }
    return true;
}
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
static std::string GetCurrentWorkingDir() {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}
/////////////////////////////////////////////////////////////////////////


static std::tuple<std::string, std::string> parseShader(const std::string& filePath){
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


static unsigned int compileShader(unsigned int type, const std::string& source){
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


static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader){
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


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    // glew init
    if(glewInit() != GLEW_OK){
        testLog("glew init failed");
        return -1;
    }
    std::cout << (glGetString(GL_VERSION)) << "\n";



    //triangle buffer
    float positions[] = {
        -0.5f, -0.5f, //0
         0.5f, -0.5f, //1
         0.5f,  0.5f, //2
        -0.5f,  0.5f  //3
    };

    unsigned int indecies[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int buffer;
    GLCall( glGenBuffers(1, &buffer));
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall( glBufferData(GL_ARRAY_BUFFER, (4 * 2 * sizeof(float)), positions, GL_STATIC_DRAW));

    GLCall( glEnableVertexAttribArray(0));
    GLCall( glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, (2 * sizeof(float)), (const void*)0));

    //index buffer
    unsigned int ibo;
    GLCall( glGenBuffers(1, &ibo));
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, (2 * 3 * sizeof(unsigned int)), indecies, GL_STATIC_DRAW));

    /*std::string vertexShader = R"glsi(
        #version 330 core

        layout(location = 0) in vec4 position;

        void main(){
            gl_Position = position;
        }
    )glsi";

    std::string fragmentShader = R"glsi(
        #version 330 core

        layout(location = 0) out vec4 color;

        void main(){
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )glsi";*/

    auto[vertexShader,fragmentShader] = parseShader(GetCurrentWorkingDir() + "/res/shaders/basic.shader");

    unsigned int shader = createShader(vertexShader,fragmentShader);
    GLCall(glUseProgram(shader));

    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //triangle with lagacy opengl
        /*glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();*/

        //triangle
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        GLCall(glDrawElements(GL_TRIANGLES, (2*3)/*num of indecies*/, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    GLCall(glDeleteProgram(shader));

    glfwTerminate();
    return 0;
}