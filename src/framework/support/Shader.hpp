#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
// Shader(const char* vert_shader = "shaders/default.vert", const char* frag_shader = "shaders/default.frag");

class Shader
{
    private:
        std::string readFile(const char* fp);
        GLuint ID;

    public:
        Shader();
        Shader(const char* vert_shader , const char* frag_shader );
        void use();
        void SetBool(const std::string &name, bool value) const;
        void SetInt(const std::string &name, int value) const;
        void SetFloat(const std::string &name, float value) const; 
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        GLuint getID();

};

#endif