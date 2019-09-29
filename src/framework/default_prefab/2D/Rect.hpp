#include "Shape.hpp"


class Rect : public Shape
{
    private:
        float width,height;
        
        bool hasTexture = false;
    public:
        float vertices[16];
        float indices[6];
        Rect(float x, float y, float width, float height);
        void setTexture(Texture text);
        ~Rect();
    protected:
        
        void setVertices();
};