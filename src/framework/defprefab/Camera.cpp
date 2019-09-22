#include "Camera.hpp"


Camera::Camera(glm::vec3 initPos, const char* vert, const char* frag)
{
    camPos=initPos;
    
    createShader(vert,frag);
    setView();
}


Camera::Camera(glm::vec3 initPos,Shader shader)
{
    camPos=initPos;
    camShader = shader;
}

void Camera::createShader(const char* vert,const char* frag)
{
    camShader = *new Shader(vert,frag);

}


void Camera::calcView()
{
    view = glm::lookAt(camPos,
                        camPos+camFront,
                        camUp);
}



void Camera::setView()
{
    calcView();
    viewLoc = glGetUniformLocation(camShader.getID(),"view");
    glUniformMatrix4fv(viewLoc,1,GL_FALSE,&view[0][0]);
}
void Camera::setViewMat(glm::mat4 v)
{
    view=v;
}
void Camera::setModel()
{
    modelLoc = glGetUniformLocation(camShader.getID(),"model");
    glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
}

void Camera::setModelVal(glm::mat4 mdl)
{
    model=mdl;
}

void Camera::setShader(Shader shader)
{
    camShader=shader;
}

void Camera::setProjection(glm::mat4 proj)
{
    projection=proj;
    camShader.setMat4("projection",projection);
}

Shader Camera::getShader()
{
    return camShader;
}

glm::mat4 Camera::getModel()
{
    return model;
}
glm::vec3 Camera::getCamPos()
{
    return camPos;
}

bool Camera::isMovementAllowed(){return movementEnabled;}

void Camera::setMovementAllowed(bool movementAllowed){movementEnabled=movementAllowed;}

void Camera::translateModel(glm::vec3 pos)
{
    model =glm::translate(model,pos);
    // std::cout<<pos.x <<;
}


void Camera::handleCameraInput(GLFWwindow *targetWindow, float deltaTime)
{
    if(isMovementAllowed())
    {
        
        //forward
        std::cout<< "x: " << camPos.x  << ", y: " << camPos.y 
            << ", z: " << camPos.z << std::endl;
        float localSpeed = speed*deltaTime;
        if(glfwGetKey(targetWindow,GLFW_KEY_W)==GLFW_PRESS)
        {
            camPos+=speed*camFront;
            
        }
        if(glfwGetKey(targetWindow,GLFW_KEY_S)==GLFW_PRESS)
            camPos-=speed*camFront;
        if(glfwGetKey(targetWindow,GLFW_KEY_A)==GLFW_PRESS)
            camPos-=speed*glm::normalize(glm::cross(camFront,camUp));
        if(glfwGetKey(targetWindow,GLFW_KEY_D)==GLFW_PRESS)
            camPos+=speed*glm::normalize(glm::cross(camFront,camUp));
        if(glfwGetKey(targetWindow,GLFW_KEY_SPACE)==GLFW_PRESS)
            camPos+=speed*camUp;
        if(glfwGetKey(targetWindow,GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS)
            camPos-=speed*camUp;
    }
    else
    {

    }

}

