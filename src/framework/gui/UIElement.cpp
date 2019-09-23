#include "UIElement.hpp"



UIElement::UIElement()
{
    uiShader  =   Shader(vertShaderPath,fragShaderPath);
    
}


UIElement::UIElement(float xpos, float ypos)
{
    uiShader  =   Shader(vertShaderPath,fragShaderPath);
    if(xpos<0.0f || xpos>1.0f)
        std::cout << "WARNING::UIELEMENT, passed in value  (x<0.0f) or (x>1.0f)" << std::endl;
    if(ypos<0.0f || ypos>1.0f)
        std::cout << "WARNING::UIELEMENT, passed in value  (y<0.0f) or (y>1.0f)" << std::endl;  
    x=xpos-0.5f;
    y=ypos-0.5f;
    
}

UIElement::UIElement(float xpos, float ypos, float w, float h)
{
    uiShader  =   Shader(vertShaderPath,fragShaderPath);
    if(xpos<0.0f || xpos>1.0f)
        std::cout << "WARNING::UIELEMENT, passed in value  (x<0.0f) or (x>1.0f)" << std::endl;
    if(ypos<0.0f || ypos>1.0f)
        std::cout << "WARNING::UIELEMENT, passed in value  (y<0.0f) or (y>1.0f)" << std::endl;  
    if(width<0.0f || width>1.0f)
            std::cout << "WARNING::UIELEMENT, passed in value  (width<0.0f) or (width>1.0f)" << std::endl;
    if(height<0.0f || height>1.0f)
        std::cout << "WARNING::UIELEMENT, passed in value  (height<0.0f) or (height>1.0f)" << std::endl;  
    
    x=xpos;
    y=ypos;

    width = w;
    height = h;
    generateVertices();
}


void UIElement::setShader(Shader *shader)
{
    uiShader=*shader;
}

Shader UIElement::getShader(){return uiShader;}
//protected

void UIElement::generateVertices()
{
    int size=12;
    vertices = new float[size];
    indices = new unsigned int[6];
    for(int i=0; i<size;i+=3)
    {
        float xadd = (i==0 || i==3) ? width : 0.0f;
        float yadd = (i==3 || i==6) ? height : 0.0f;
        vertices[i] = x+xadd;
        vertices[i+1] = y+yadd;
        vertices[i+2] = 0.0f;
        std::cout <<"x: "<< vertices[i] << ", y: " << vertices[i+1] << ",z: " << vertices[i+2] << std::endl;
    }

    // for(int i = 0; i < size; i ++)
    // {
    //     std::cout << vertices[i] << std::endl;
    // }
    indices[0] =0;
    indices[1]=1;
    indices[2]=3;

    indices[3] =1;
    indices[4]=2;
    indices[5]=3;
    initializeGraphics();

}


void UIElement::initializeGraphics()
{

    for(int i = 0; i < 12; i ++)
    {
        std::cout << vertices[i] << std::endl;
    }
    // uiShader->use();
    float localvert[] =
    {
        *vertices,*(vertices+1),*(vertices+2),
        *(vertices+3),*(vertices+4),*(vertices+5),
        *(vertices+6),*(vertices+7),*(vertices+8),
        *(vertices+9),*(vertices+10),*(vertices+11)
    };
    unsigned int localind[] = {
        0,1,3,
        1,2,3
    };

    // float localvert[] = 
    // {
    //     0.5f,  0.5f, 0.0f,  // top right
    //      0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f
    // };

    // unsigned int localind[] = {  // note that we start from 0!
    //     0, 1, 3,  // first Triangle
    //     1, 2, 3   // second Triangle
    // };
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    // glBind
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(localvert),localvert,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(localind),localind,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}


void UIElement::draw()
{
    // uiShader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void UIElement::deleteBuffers()
{
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}