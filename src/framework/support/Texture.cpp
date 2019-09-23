#include "Texture.hpp"





Texture::Texture(const char* fpath)
{
    int w,h,nr;
    Texture::data = stbi_load(fpath,&w,&h,&nr,0);
    if(!Texture::data) std::cout << " Could not load texture from path: " << fpath << std::endl;
    setWidth(w);
    setHeight(h);
    setChannels(nr);
}

void Texture::setWidth(int w)
{
    Texture::width = w;
}
void Texture::setHeight(int h)
{
    Texture::height = h;
}
void Texture::setChannels(int nrc)
{
    Texture::nrChannels =nrc;
}
 void Texture::setTexture(unsigned int txtr, int texture_num)
 {
     Texture::texture[texture_num] = txtr;
 }
void Texture::generate(int texture_num)
{
    unsigned int tmp_txtr;
    glGenTextures(1,&tmp_txtr);
    setTexture(tmp_txtr,texture_num);
    glBindTexture(GL_TEXTURE_2D,Texture::texture[texture_num]);
    if(Texture::data)
    {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Texture::width,Texture::height,0,GL_RGB,GL_UNSIGNED_BYTE,Texture::data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "failed to load" << std::endl;
    }
    
    stbi_image_free(Texture::data);
}


unsigned int Texture::getTexture(int texture_num)
{
    return Texture::texture[texture_num];
}

void Texture::bind(int texture_num)
{
    switch(texture_num)
    {
        case 0:
            glActiveTexture(GL_TEXTURE0);
            break;
        case 1:
            glActiveTexture(GL_TEXTURE1);
            break;
        case 2:
            glActiveTexture(GL_TEXTURE2);
            break;
        case 3:
            glActiveTexture(GL_TEXTURE3);
            break;
        case 4:
            glActiveTexture(GL_TEXTURE4);
            break;
        case 5:
            glActiveTexture(GL_TEXTURE5);
            break;
        case 6:
            glActiveTexture(GL_TEXTURE6);
            break;
        case 7:
            glActiveTexture(GL_TEXTURE7);
            break;
        case 8:
            glActiveTexture(GL_TEXTURE8);
            break;
        case 9:
            glActiveTexture(GL_TEXTURE9);
            break;
        case 10:
            glActiveTexture(GL_TEXTURE10);
            break;
        case 11:
            glActiveTexture(GL_TEXTURE11);
            break;
        case 12:
            glActiveTexture(GL_TEXTURE12);
            break;
        case 13:
            glActiveTexture(GL_TEXTURE13);
            break;
        case 14:
            glActiveTexture(GL_TEXTURE14);
            break;
        case 15:
            glActiveTexture(GL_TEXTURE15);
            break;
        case 16:
            glActiveTexture(GL_TEXTURE16);
            break;
        case 17:
            glActiveTexture(GL_TEXTURE17);
            break;
        case 18:
            glActiveTexture(GL_TEXTURE18);
            break;
        case 19:
            glActiveTexture(GL_TEXTURE19);
            break;
        case 20:
            glActiveTexture(GL_TEXTURE20);
            break;
        case 21:
            glActiveTexture(GL_TEXTURE21);
            break;
        case 22:
            glActiveTexture(GL_TEXTURE22);
            break;
        case 23:
            glActiveTexture(GL_TEXTURE23);
            break;
        case 24:
            glActiveTexture(GL_TEXTURE24);
            break;
        case 25:
            glActiveTexture(GL_TEXTURE25);
            break;
        case 26:
            glActiveTexture(GL_TEXTURE26);
            break;
        case 27:
            glActiveTexture(GL_TEXTURE27);
            break;
        case 28:
            glActiveTexture(GL_TEXTURE28);
            break;
        case 29:
            glActiveTexture(GL_TEXTURE29);
            break;
        case 30:
            glActiveTexture(GL_TEXTURE30);
            break;
        case 31:
            glActiveTexture(GL_TEXTURE31);
            break;
    }
    Texture::ID = texture_num;
    glBindTexture(GL_TEXTURE_2D,Texture::texture[texture_num]);
}


void Texture::activate()
{

}