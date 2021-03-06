//dependencies
    //GLAD, glm, and FreeType




#include<windows.h>
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

//user
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "framework/default_prefab/Camera.hpp"
#include "framework/prefab2D.hpp"
#include "framework/gui/UIElement.hpp"
#include "framework/Math.hpp"
#include "framework/Supports.h"

// #include "glglobal.hpp"



using namespace std;

//time for constant speed
float deltaTime=0.0f;
float lastFrame = 0.0f;

//cam
glm::vec3 camPos = glm::vec3(0.0f,0.0f,3.0f);
glm::vec3 camFront = glm::vec3(0.0f,0.0f,-1.0f);
glm::vec3 camUp = glm::vec3(0.0f,1.0f,0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;

//functions in glfn.cpp




void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


const char* vertShaderPaths[1] = {
    "framework/shaders/vert/basic.vert"
    };
const char* fragShaderPaths[2] {
    "framework/shaders/frag/color.frag",
    "framework/shaders/frag/color2.frag"
};

//Use GLuint instead of "unsigned int"

int main()
{
    int width=800,height=600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    



     GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
     //disable cursor, mouse input. FPS cam
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
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


    Shader guiShader("framework/shaders/vert/gui.vert",fragShaderPaths[1]);
    // Shader worldShader(vertShaderPaths[0],fragShaderPaths[0]);


    Rect rect(0.0,0.0,0.5,0.5);
    // Shape myshape = rect;
    

    // UIElement bar(-1.0f,-1.0f,2.0f,0.4f);
    // UIElement bar2(-0.5f,-1.0f,0.5f,0.4f);
    // bar.setShader(&GUIShader);
    // bar2.setShader(&shader);
    // Camera cam(camPos,vertShaderPaths[0],fragShaderPaths[0]);


    /*Uncomment for wireframe*/
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    

    float xx = -0.4;
    float yy = 0.4;

    std::cout << xx << " "  << yy << std::endl;
    Coordinates::originBotLeft(&xx,&yy);
    std::cout << xx << " "  << yy << std::endl;
    //trying to perspective
  

    // cam.getShader().use();

    //RENDER LOOP
    Color color;
    // glEnable(GL_DEPTH_TEST);
    float r=0.0f,g=0.0f,b=0.0f;
    float t=0.0f;
    while(!glfwWindowShouldClose(window))
    {   
        //to print fps
        
 
        glClearColor(1.0f,1.0f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        rect.setColor(glm::vec4(r,g,b,1.0f));
        rect.draw(&guiShader);




        float currentFrame = glfwGetTime();
        deltaTime = currentFrame-lastFrame;
        lastFrame=currentFrame;
        //print out fps
        t= (t >  2*glm::pi<float>() ) ? 0 : t+ deltaTime;
        //end
        glfwSwapBuffers(window);
        glfwPollEvents();
        g=(glm::sin(t) < 0 ) ? -glm::sin(t) : glm::sin(t);
        // r=glm::cos(t);
        // b=glm::sin(t+0.5);
        std::cout << t << std::endl;
    }

    // glDeleteBuffers(1,&EBO);

   
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

void drawUIElements()
{
    //TODO write this
}

