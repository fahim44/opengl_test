#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

#include "testLog.h"
#include "utilities.h"
#include "shaderLib.h"


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