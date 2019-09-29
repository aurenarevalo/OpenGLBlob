#include "../../dependencies.hpp"
#include "../support/Shader.hpp"
#include <string>

class Camera
{
    private:
        //constants
        glm::vec3 camPos = glm::vec3(0.0f,0.0f,1.0f);

        glm::vec3 camFront = glm::vec3(0.0f,0.0f,-1.0f);
        glm::vec3 camUp = glm::vec3(0.0f,1.0f,0.0f);

        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        glm::vec3 camTarget =glm::vec3(0.0f,0.0f,0.0f);
        glm::vec3 camDirection = glm::normalize(camPos-camTarget);

        GLint viewLoc, modelLoc;
        Shader camShader;
        // float deltaTime=0.0f;
        std::string vertShaderPath;
        bool movementEnabled = true;
    public:
        float speed=0.1f;
        Camera(glm::vec3 initPos, const char* vert, const char* frag);
        Camera(glm::vec3 initPos,Shader shader);
        
        void update();

        void createShader(const char* vert,const char* frag);

        void calcView();

        void updateView();
        void setViewMat(glm::mat4 v);

        void setModel(glm::mat4 mdl);
        void updateModel();

        void setShader(Shader shader);

        void setProjection(glm::mat4 proj);
        void updateProjection();

        Shader getShader();
        glm::mat4 getModel();
        glm::vec3 getCamPos();

        bool isMovementAllowed();
        void setMovementAllowed(bool movementAllowed);
        void translateModel(glm::vec3 pos);
        void handleCameraInput(GLFWwindow *targetWindow,float deltaTime);
        
    protected:

};