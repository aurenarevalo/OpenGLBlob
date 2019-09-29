#include "Rect.hpp"

Rect::Rect(float x, float y, float width, float height)
{
    Shape::type = "rectangle";
    Shape::x = x;
    Shape::y = y;
    Rect::width = width;
    Rect::height = height;
    Shape::numVerts = 12;
    Shape::numIndices = 6;
    setVertices();
}

void Rect::setVertices()
{
    //go BL, BR, TL, TR
    Shape::vertices = new float[numVerts]{
        x,y,0.0f,
        x+width,y,0.0f,
        x,y+height,0.0f,
        x+width,y+height,0.0f
    };
    Shape::indices = new int[numIndices]{
        0,1,3,
        0,3,2
    };
    setBuffers();
}

void Rect::setTexture(Texture texture)
{

}

void Shape::setBuffers()
{
    glGenVertexArrays(1,&(Shape::VAO));
    glGenBuffers(1,&(Shape::VBO));
    glGenBuffers(1,&(Shape::EBO));

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Shape::vertices)*Shape::numVerts,Shape::vertices,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Shape::indices)*Shape::numIndices,Shape::indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}


void Shape::draw(Shader* shader)
{
    shader->use();
    if(Shape::colorSet)
        shader->setVec4("color",Shape::color);
    else
        shader->setVec4("color",glm::vec4(0.0f,0.0f,0.0f,1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}


void Shape::convertToLocal(float x, float y)
{
    
}


Rect::~Rect(){
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}