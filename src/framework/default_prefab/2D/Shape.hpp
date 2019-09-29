#ifndef SHAPE_H
#define SHAPE_H
#include "../../../dependencies.hpp"
#include "../../support/Shader.hpp"
#include "../../support/Texture.hpp"
#include "../../support/Color.hpp"
class Shape
{
    private:
        

    public:
        void draw(Shader *shader);
        void setColor(glm::vec4 color)
        {
            Shape::color=color;
            Shape::colorSet=true;
        }
    protected:
        glm::vec4 color;
        bool colorSet=false;
        float x,y;
        const char* type;
        GLuint VAO, VBO, EBO;
        int numVerts;
        int numIndices;
        float *vertices;
        int *indices;
        
        void setBuffers();
        void convertToLocal(float x, float y);
        void covertToWorld(float x, float y);


};

#endif // !SHAPE_H