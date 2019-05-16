/*
REFERENCE:
    https://badvertex.com/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c.html
*/



#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::string readFile(const char* fp)
{
    std::string body;
    std::ifstream file(fp,std::ios::in);

    if(!file.is_open())
    {
        std::cerr << "Could not read or find file " << fp << "." << std::endl;
    }
}