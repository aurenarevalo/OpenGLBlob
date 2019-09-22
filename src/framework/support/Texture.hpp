
#ifndef TEXTURE_H
#define TEXTURE_H
#define STB_IMAGE_IMPELMENTATION
#include "GLAD/glad.h"
#include "glfw3.h"
#include "stb_image.h"
#include <iostream>


class Texture
{
    private:
        int width, height, nrChannels, ID;
        unsigned int texture[32];
        unsigned char* data;
        void setWidth(int w);
        void setHeight(int h);
        void setChannels(int nrc);
        void setTexture(unsigned int txtr, int texture_num);

    public:
        Texture(const char* fpath = "");
        void generate(int texture_num);
        unsigned int getTexture(int texture_num);
        void bind(int texture_num = 0);
        void activate();



};

#endif