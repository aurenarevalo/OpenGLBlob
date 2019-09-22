#include "../dependencies.hpp"
#include "../support/Texture.hpp"
#include "../support/Shader.hpp"

class SimpleGui 
{
    private:
        Texture texture;
        Shader shader;
        const float HEIGHT;
        const float WIDTH;
    public:
        SimpleGui::SimpleGui();       
        void draw();
        float getHeight();
        float getWidth();




};