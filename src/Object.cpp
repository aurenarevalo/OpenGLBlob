#include "Object.hpp"


Object::Object(std::string objName)
{
    // const char *path = std_dir + objName;
    std::cout << "?????" << std::endl;
    loadObj(Object::std_dir+objName);
}

void Object::loadObj(std::string path)
{
    std::vector<glm::vec3> tmpVerts;
    std::vector<glm::vec2> tmpUVs;
    std::vector<glm::vec3> tmpNorms;
    std::vector<std::string> fileVector; 
    // std::ifstream inFile(path);
    // std::string line;
    std::cout << "?????" << std::endl;
    FILE* inFile = fopen(path.c_str(), "r");
    if(inFile == NULL)
    {
        std::cerr << "ERROR::FILE_NOT_FOUND > " << path << std::endl;
        return;
    }
    char line[256];
    while(1)
    {
        int res = fscanf(inFile, "%s",&line);
        if(res==EOF) break;
        std::cout << std::endl << line;
        if(!strcmp(line,"v"))
        {
            glm::vec3 vert;
            fscanf(inFile,"%f %f %f\n",&vert.x,&vert.y,&vert.z);
            tmpVerts.push_back(vert);
        }
        else if (!strcmp(line,"vt"))
        {
            glm::vec2 UV;
            fscanf(inFile,"%f %f\n",&UV.x,&UV.y);
            tmpUVs.push_back(UV);
        }
        else if(!strcmp(line,"vn"))
        {
            glm::vec3 norm;
            fscanf(inFile,"%f %f %f\n",&norm.x,&norm.y,&norm.z);
            tmpNorms.push_back(norm);
        }
        else if(!strcmp(line,"f"))
        {
            std::string v1, v2, v3;
            GLuint vertIndx1[3], vertIndx2[3];//, vertIndx3[3];
            int matches = fscanf(inFile,"%d//%d %d//%d %d//%d\n",&vertIndx1[0],&vertIndx2[0],
                                            &vertIndx1[1],&vertIndx2[1],
                                            &vertIndx1[2],&vertIndx2[2]);
            // std::cout << std::endl << std::endl << matches << std::endl;
            if(matches<6)
            {
                std::cout << "Can't be read" << std::endl << std::endl;
                return;
            }
            // std::cout << vertIndx1[0] << std::endl;
            Object::vInd.push_back(vertIndx1[0]);
            Object::vInd.push_back(vertIndx1[1]);
            Object::vInd.push_back(vertIndx1[2]);

            Object::uvInd.push_back(vertIndx2[0]);
            Object::uvInd.push_back(vertIndx2[1]);
            Object::uvInd.push_back(vertIndx2[2]);

            // Object::normInd.push_back(vertIndx3[0]);
            // Object::normInd.push_back(vertIndx3[1]);
            // Object::normInd.push_back(vertIndx3[2]);
        }
        else{}
        
    }
    fclose(inFile);
}


void Object::Debug()
{
    for(int i = 0; i < Object::vInd.size();i++)
    {
        std::cout << vInd.at(i) << std::endl;
    }
}