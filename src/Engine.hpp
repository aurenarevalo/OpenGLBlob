#include "Texture.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Engine
{
    private:
       Shader shaders[];
        Texture textures[];

    public:
        Engine();
        void Instatiate(const char* obj_type);
};