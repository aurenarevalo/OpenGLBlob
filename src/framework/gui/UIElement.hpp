#include "../../dependencies.hpp"
#include "../support/Texture.hpp"
#include "../support/Shader.hpp"

//default rectangle for testing
class UIElement
{
    private:
        // Texture uiTexture;
        Shader uiShader;
        const char* vertShaderPath = "framework/shaders/vert/basic.vert";
        const char* fragShaderPath = "framework/shaders/frag/color2.frag";
        glm::vec3 position = glm::vec3(1.0f);
        //for now, from 0.0f-1.0f
        float x, y;
        float width, height;
        
        float *vertices;
        // float vertices[] = {

        // };

        unsigned int *indices;

        unsigned int VAO,VBO,EBO;
        //private functions
        
    public:
        UIElement();
        UIElement(float x, float y);
        UIElement(float x, float y, float width, float height);
        void setShader(Shader *shader);
        Shader getShader();

        void draw();
        void deleteBuffers();

        

        // UIElement(const char* fragShader);
        // UIElement(const char* vertShader,const char* fragShader);

    protected:
        void initializeGraphics();
        //protected funs
        void generateVertices();

};