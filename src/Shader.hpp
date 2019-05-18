#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw3.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


class Shader
{
    private:
        std::string readFile(const char* fp);
        GLuint ID;

    public:
        Shader(const char* vert_shader, const char* frag_shader);
        void use();
        void SetBool(const std::string &name, bool value) const;
        void SetInt(const std::string &name, int value) const;
        void SetFloat(const std::string &name, float value) const; 
        GLuint getID();





};

#endif