
#include<windows.h>
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

//user
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Object.hpp"

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
    // Shader program2(vertShaderPaths[0],fragShaderPaths[0])
    // Shader program2(vertShaderPaths[0], fragShaderPaths[1]);

//   float firstTriangle[] = {
//         -0.9f, -0.5f, 0.0f,  // left 
//         -0.0f, -0.5f, 0.0f,  // right
//         -0.45f, 0.5f, 0.0f,  // top 
//     };
  float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.1f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    Texture textr("textures/rip.png");
    Texture textr2("textures/220.jpg");
    // Object obj("cube.obj");
    textr2.generate(1);
    textr.generate(0);
    unsigned int VBO, VAO,EBO; // Vertex buffer objects
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    //First Vert Array Obj (for frag Shader 1)
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    // obj.display();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    

   

    /*Uncomment for wireframe*/
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    program1.use();
    program1.SetInt("texture1",0);
    program1.SetInt("texture2",1);
    glm::ortho(0.0f,800.0f,0.0f,600.0f,0.1f,100.0f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model,glm::radians(-55.0f),glm::vec3(1.0f,0.0f,0.0f));
    //RENDER LOOP
    while(!glfwWindowShouldClose(window))
    {   
        processInput(window);
        //Rendering commands
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //draw triangle
        textr2.bind(1);
        textr.bind(0);
       
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);
        glm::mat4 trans = glm::mat4(1.0f);
        // trans = glm::rotate(trans,4*(float)glfwGetTime(),glm::vec3(0.0f,1.0f,1.0f));
        trans = glm::translate(trans,glm::vec3(0.5,-0.5f,0.0f));

        // glm::mat4 model = glm::mat4(1.0f);
        // glm::mat4 view  = glm::mat4(1.0f);
        // glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model,glm::radians(-55.0f),glm::vec3(1.0f,0.0f,0.0f));
        // view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
        // projection = glm::perspective(glm::radians(45.0f),800.0f/600.0f,0.0f,100.0f);

        unsigned int modelLoc =glGetUniformLocation(program1.getID(),"model");
        unsigned int viewLoc = glGetUniformLocation(program1.getID(),"view");
        program1.setMat4("projection",projection);

        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
        // glUniformMatrix4fv(viewLoc,1,GL_FALSE,&view[0][0]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
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

