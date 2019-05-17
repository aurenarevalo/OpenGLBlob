[33mcommit 918a6564c7fa8caca73bfaa0b89f86b02b73e250[m[33m ([m[1;36mHEAD -> [m[1;32mmaster[m[33m)[m
Author: unknown <aaarevalo@crimson.ua.edu>
Date:   Fri May 17 02:01:20 2019 -0500

    Base Shader class.

[1mdiff --git a/GSLoader.cpp b/GSLoader.cpp[m
[1mdeleted file mode 100644[m
[1mindex 98b0a8b..0000000[m
[1m--- a/GSLoader.cpp[m
[1m+++ /dev/null[m
[36m@@ -1,23 +0,0 @@[m
[31m-/*[m
[31m-REFERENCE:[m
[31m-    https://badvertex.com/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c.html[m
[31m-*/[m
[31m-[m
[31m-[m
[31m-[m
[31m-#include <string>[m
[31m-#include <iostream>[m
[31m-#include <fstream>[m
[31m-#include <vector>[m
[31m-#include <algorithm>[m
[31m-[m
[31m-std::string readFile(const char* fp)[m
[31m-{[m
[31m-    std::string body;[m
[31m-    std::ifstream file(fp,std::ios::in);[m
[31m-[m
[31m-    if(!file.is_open())[m
[31m-    {[m
[31m-        std::cerr << "Could not read or find file " << fp << "." << std::endl;[m
[31m-    }[m
[31m-}[m
\ No newline at end of file[m
[1mdiff --git a/GSLoader.hpp b/GSLoader.hpp[m
[1mdeleted file mode 100644[m
[1mindex cdaf4cd..0000000[m
[1m--- a/GSLoader.hpp[m
[1m+++ /dev/null[m
[36m@@ -1,11 +0,0 @@[m
[31m-#ifndef GSLOADER_H[m
[31m-#define GSLOADER_H[m
[31m-[m
[31m-#include <glad/glad.h>[m
[31m-#include <glfw3.h>[m
[31m-[m
[31m-[m
[31m-GLuint* LoadShader(const char* vert_path, const char* frag_path);[m
[31m-[m
[31m-[m
[31m-#endif[m
\ No newline at end of file[m
[1mdiff --git a/Shader.cpp b/Shader.cpp[m
[1mnew file mode 100644[m
[1mindex 0000000..bcdab5c[m
[1m--- /dev/null[m
[1m+++ b/Shader.cpp[m
[36m@@ -0,0 +1,94 @@[m
[32m+[m[32m#include "Shader.hpp"[m
[32m+[m
[32m+[m
[32m+[m[32mstd::string Shader::readFile(const char* fp)[m
[32m+[m[32m{[m
[32m+[m[32m    std::string body;[m
[32m+[m[32m    std::ifstream file(fp,std::ios::in);[m
[32m+[m
[32m+[m[32m    if(!file.is_open())[m
[32m+[m[32m    {[m
[32m+[m[32m        std::cerr << "Could not read or find file " << fp << "." << std::endl;[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    std::string line = "";[m
[32m+[m[32m    while(!file.eof())[m
[32m+[m[32m    {[m
[32m+[m[32m        std::getline(file,line);[m
[32m+[m[32m        body.append(line + "\n");[m
[32m+[m[32m    }[m
[32m+[m[32m    file.close();[m
[32m+[m[32m    return body;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m
[32m+[m[32m Shader::Shader(const char* vert_shader, const char* frag_shader)[m
[32m+[m[32m{[m
[32m+[m[32m    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);[m
[32m+[m[32m    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);[m
[32m+[m
[32m+[m[32m    const char* vertShaderSrc = readFile(vert_shader).c_str();[m
[32m+[m[32m    const char* fragShaderSrc = readFile(frag_shader).c_str();[m
[32m+[m[32m    GLint success;[m
[32m+[m[32m    GLchar infoLog[512];[m
[32m+[m[32m    //Vert shader[m
[32m+[m[32m    glShaderSource(vertexShader,1,&vertShaderSrc,NULL);[m
[32m+[m[32m    glCompileShader(vertexShader);[m
[32m+[m
[32m+[m[32m    //check vert shader compilation[m
[32m+[m[32m    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);[m
[32m+[m[32m    if(!success)[m
[32m+[m[32m    {[m
[32m+[m[32m        glGetShaderInfoLog(vertexShader,512,NULL, infoLog);[m
[32m+[m[32m        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    //compile frag shader[m
[32m+[m[32m    glShaderSource(fragmentShader,1,&fragShaderSrc,NULL);[m
[32m+[m[32m    glCompileShader(fragmentShader);[m
[32m+[m
[32m+[m[32m    //check Successfull comp[m
[32m+[m[32m    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);[m
[32m+[m[32m    if(!success)[m
[32m+[m[32m    {[m
[32m+[m[32m        glGetShaderInfoLog(fragmentShader,512,NULL, infoLog);[m
[32m+[m[32m        std::cerr<< "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;[m
[32m+[m[32m    }[m
[32m+[m[32m    GLuint prog = glCreateProgram();[m
[32m+[m[32m    glAttachShader(prog, vertexShader);[m
[32m+[m[32m    glAttachShader(prog,fragmentShader);[m
[32m+[m[32m    glLinkProgram(prog);[m
[32m+[m
[32m+[m[32m    glGetProgramiv(prog,GL_LINK_STATUS,&success);[m
[32m+[m[32m    if(!success)[m
[32m+[m[32m    {[m
[32m+[m[32m         glGetShaderInfoLog(fragmentShader,512,NULL, infoLog);[m
[32m+[m[32m        std::cerr << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    glDeleteShader(vertexShader);[m
[32m+[m[32m    glDeleteShader(fragmentShader);[m
[32m+[m
[32m+[m[32m    ID =prog;[m
[32m+[m[32m}[m[41m   [m
[32m+[m
[32m+[m
[32m+[m[32mvoid Shader::use()[m
[32m+[m[32m{[m
[32m+[m[32m    glUseProgram(ID);[m
[32m+[m[32m}[m
[32m+[m[32mvoid Shader::SetBool(const std::string &name, bool value) const[m
[32m+[m[32m{[m
[32m+[m[32m    glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);[m
[32m+[m[32m}[m
[32m+[m[32mvoid Shader::SetInt(const std::string &name, int value) const[m
[32m+[m[32m{[m
[32m+[m[32m    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);[m
[32m+[m[32m}[m
[32m+[m[32mvoid Shader::SetFloat(const std::string &name, float value) const[m
[32m+[m[32m{[m
[32m+[m[32m    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);[m
[32m+[m[32m}[m
[32m+[m
[32m+[m
[32m+[m
[1mdiff --git a/Shader.hpp b/Shader.hpp[m
[1mnew file mode 100644[m
[1mindex 0000000..239d454[m
[1m--- /dev/null[m
[1m+++ b/Shader.hpp[m
[36m@@ -0,0 +1,33 @@[m
[32m+[m[32m#ifndef SHADER_H[m
[32m+[m[32m#define SHADER_H[m
[32m+[m
[32m+[m[32m#include <glad/glad.h>[m
[32m+[m[32m#include <glfw3.h>[m
[32m+[m
[32m+[m[32m#include <string>[m
[32m+[m[32m#include <iostream>[m
[32m+[m[32m#include <fstream>[m
[32m+[m[32m#include <vector>[m
[32m+[m[32m#include <algorithm>[m
[32m+[m
[32m+[m
[32m+[m[32mclass Shader[m
[32m+[m[32m{[m
[32m+[m[32m    private:[m
[32m+[m[32m        std::string readFile(const char* fp);[m
[32m+[m[32m        GLuint ID;[m
[32m+[m
[32m+[m[32m    public:[m
[32m+[m[32m        Shader(const char* vert_shader, const char* frag_shader);[m
[32m+[m[32m        void use();[m
[32m+[m[32m        void SetBool(const std::string &name, bool value) const;[m
[32m+[m[32m        void SetInt(const std::string &name, int value) const;[m
[32m+[m[32m        void SetFloat(const std::string &name, float value) const;[m[41m [m
[32m+[m
[32m+[m
[32m+[m
[32m+[m
[32m+[m
[32m+[m[32m};[m
[32m+[m
[32m+[m[32m#endif[m
\ No newline at end of file[m
