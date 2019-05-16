#include<windows.h>
#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/* Note difference between vertex and fragment Shaders!!!*/

const char* vertexShaderSource =
{
    "basic.frag"
};

const char* fragmentShaderSource = 
{
    "color.frag"
};

int main()
{
    glfwInit();

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
    };
    unsigned int VBO; // Vertex buffer objects
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    // Vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    //Compile check declarations
    int success;
    char infoLog[512];
    //check successful compile
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512,NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // Frag shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    //check compile
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader,512,NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    //Shader Object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    //check link
    if(!success)
    {
         glGetShaderInfoLog(fragmentShader,512,NULL, infoLog);
        cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << endl;
    }
    //delete objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //init
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        cout << "Failed to create GLFW win" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {   
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }    
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    //RENDER LOOP
    while(!glfwWindowShouldClose(window))
    {   
        processInput(window);
        //Rendering commands
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
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

