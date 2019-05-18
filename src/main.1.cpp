#include<windows.h>
#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.hpp"
#include <iostream>

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


const char* vertShaderPaths[1] = {
    "shaders/basic.vert"
    };
const char* fragShaderPaths[2] {
    "shaders/color.frag",
    "shaders/color2.frag"
};

//Use GLuint instead of "unsigned int"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);



     GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
     if(window == NULL)
    {
        cout << "Failed to create GLFW win" << endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {   
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    } 
    Shader program1(vertShaderPaths[0],fragShaderPaths[0]);
    // Shader program2(vertShaderPaths[0], fragShaderPaths[1]);

  float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };
    // unsigned int indices[] = 
    // {
    //     1,2,3,
    //     0,2,3
    // };

    unsigned int VBO[2], EBO, VAO[2]; // Vertex buffer objects
    glGenVertexArrays(2,VAO);
    glGenBuffers(2,VBO);
    glGenBuffers(1,&EBO);
    //First Vert Array Obj (for frag Shader 1)
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(firstTriangle),firstTriangle,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //Second Vert Array Obj (for frag Shader 2) and triangle 2
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(secondTriangle),secondTriangle,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

   

    /*Uncomment for wireframe*/
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    
    //RENDER LOOP
    while(!glfwWindowShouldClose(window))
    {   
        processInput(window);
        //Rendering commands
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw triangle
        program1.use();
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0,3);
        
        program2.use();
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES,0,3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(2,VAO);
    glDeleteBuffers(2,VBO);
    glDeleteBuffers(1,&EBO);


    glfwTerminate();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

