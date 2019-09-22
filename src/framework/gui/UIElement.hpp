#include "../dependencies.hpp"
#include "../support/Texture.hpp"
#include "../support/Shader.hpp"

class UIElement
{
    private:
        Texture uiTexture;
        const char* vertShaderPath = "../framework/shaders/gui.vert";
        const char* fragShaderPath = "../framework/shaders/frag";
    public:
        UIElement();
        UIElement(const char* vertShader);
        UIElement(const char* vertShader,const char* fragShader);

};