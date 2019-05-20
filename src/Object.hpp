#include "Shader.hpp"
#include "Texture.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Object
{
    private:
        const char* type;
        // Shader* shaders;
        // Texture texture;
        std::string std_dir = "basic/obj/";
        std::vector<float> obj;
        //Material mtrl;
        void loadObj(std::string path);
        std::vector<GLuint> vInd, uvInd, normInd;


    public:
        Object(std::string objName);
        void Debug();




};