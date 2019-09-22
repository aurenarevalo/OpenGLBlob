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
#include "framework/support/Shader.hpp"
#include "framework/support/Texture.hpp"

#include "framework/defprefab/Camera.hpp"

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
    // Shader program1(vertShaderPaths[0],fragShaderPaths[0]);
    // Shader program2(vertShaderPaths[0],fragShaderPaths[0])
    // Shader program2(vertShaderPaths[0], fragShaderPaths[1]);

    glm::vec3 cameraTarget=glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 cameraDirection = glm::normalize(camPos-cameraTarget);
    glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);
    glm::vec3 camRight = glm::normalize(glm::cross(up,cameraDirection));
    glm::vec3 camUp = glm::cross(cameraDirection,camRight);
    glm::mat4 view;
    view = glm::lookAt( glm::vec3(0.0f,0.0f,3.0f),
                        glm::vec3(0.0f,0.0f,0.0f),
                        glm::vec3(0.0f,1.0f,0.0f));


    Camera cam(camPos,vertShaderPaths[0],fragShaderPaths[0]);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
    float squareUI[] = 
    {
        -0.75f, -0.75f, -0.75f,  0.0f, 0.0f,
        0.25f, -0.75f, -0.75f,  1.0f, 0.0f,
        0.25f,  0.25f, -0.75f,  1.0f, 1.0f,
        0.25f,  0.25f, -0.75f,  1.0f, 1.0f,
        -0.75f,  0.25f, -0.75f,  0.0f, 1.0f,
        -0.75f, -0.75f, -0.75f,  0.0f, 0.0f
    };
    glm::vec3 cubePos[]=
    {   
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int uiIndices[]
    {
        0,1,3,
        2,3,1
    };
    Texture textr("textures/rip.png");
    Texture textr2("textures/220.jpg");
    // Object obj("cube.obj");
    textr2.generate(1);
    textr.generate(0);
    unsigned int VBO, VAO,EBO; // Vertex buffer objects
    unsigned int UI_VBO, UI_VAO,UI_EBO;
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1,&UI_VAO);
    glGenBuffers(1,&UI_VBO);
    glGenBuffers(1,&UI_EBO);

    glBindVertexArray(UI_VAO);
    glBindBuffer(GL_ARRAY_BUFFER,UI_VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(squareUI),squareUI,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,UI_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(uiIndices),uiIndices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    

   

    /*Uncomment for wireframe*/
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    

    
    float radius = 10.0f;
  
    // Camera cam(camPos,program1);



    //trying to perspective
  

    cam.getShader().use();
    cam.getShader().SetInt("texture2",1);
    cam.getShader().SetInt("texture1",0);
    //RENDER LOOP
    
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {   
        //to print fps
        FILE* f = fopen("Debug.txt","w");

        cam.handleCameraInput(window,deltaTime);
        processInput(window);
        //Rendering commands
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //draw triangle
        textr.bind(0);
        textr2.bind(1);
        cam.getShader().use();

    float camX = sin(glfwGetTime())*radius;
    float camZ = cos(glfwGetTime())*radius;
    glm::mat4 projection = glm::mat4(1.0f);

    //translating scene in reverse direction of where we want to move
  
    projection = glm::perspective(glm::radians(80.0f), (float)(width / height), 0.1f, 100.0f);
    
    cam.setView();
    cam.setProjection(projection);
    cam.getShader().setMat4("projection",projection);
    
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 1; i++)
        {
            // glm::mat4 model = glm::mat4(1.0f);
            cam.setModelVal(glm::mat4(1.0f));
            cam.translateModel(cubePos[2]);
            glm::mat4 model = cam.getModel();
            float ang = 20.0f;

            if(i%3==0)  cam.setModelVal(glm::rotate(model,(float)glfwGetTime()*glm::radians(ang),glm::vec3(1.0f,0.3f,0.5f)));
            else  cam.setModelVal(glm::rotate(model,glm::radians(ang),glm::vec3(0.0,1.0f,0.5f)));
            cam.setModelVal(model);
            cam.getShader().setMat4("model",cam.getModel());
            glDrawArrays(GL_TRIANGLES,0,36);
        }
        // glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);
        // glDrawArrays(GL_TRIANGLES,0,36);
        
        glBindVertexArray(UI_VAO);
        cam.setProjection(glm::mat4(1.0f));
        cam.setModelVal(glm::mat4(1.0f));
        glm::vec3 cpos = cam.getCamPos();
        // cpos.z +=0.24;
        cam.translateModel(cpos);

        cam.getShader().setMat4("model",cam.getModel());
        glDrawArrays(GL_TRIANGLES,0,6);

        // cam.getShader().use();
        // cam.setModelVal(glm::mat4(1.0f));
        // cam.translateModel(cam.getCamPos());
        // cam.setModel();
        // cam.getShader().setMat4("model",cam.getModel());
        // glBindVertexArray(UI_VAO);
        // glDrawArrays(GL_TRIANGLES,0,4);
        // glBindVertexArray(1);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame-lastFrame;
        lastFrame=currentFrame;
        //print out fps
        fprintf(f,"FPS at %f time : %f",lastFrame,1.0f/deltaTime);
        fclose(f);
        //end
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&UI_VBO);
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

