#include "Shader.hpp"


std::string Shader::readFile(const char* fp)
{
    std::string body;
    std::ifstream file(fp,std::ios::in);

    if(!file.is_open())
    {
        std::cerr << "Could not read or find file " << fp << "." << std::endl;
    }

    std::string line = "";
    while(!file.eof())
    {
        std::getline(file,line);
        body.append(line + "\n");
    }
    file.close();
    return body;
}


 Shader::Shader(const char* vert_shader, const char* frag_shader)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertShaderSrc = readFile(vert_shader).c_str();
    const char* fragShaderSrc = readFile(frag_shader).c_str();
    GLint success;
    GLchar infoLog[512];
    //Vert shader
    glShaderSource(vertexShader,1,&vertShaderSrc,NULL);
    glCompileShader(vertexShader);

    //check vert shader compilation
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512,NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //compile frag shader
    glShaderSource(fragmentShader,1,&fragShaderSrc,NULL);
    glCompileShader(fragmentShader);

    //check Successfull comp
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader,512,NULL, infoLog);
        std::cerr<< "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vertexShader);
    glAttachShader(prog,fragmentShader);
    glLinkProgram(prog);

    glGetProgramiv(prog,GL_LINK_STATUS,&success);
    if(!success)
    {
         glGetShaderInfoLog(fragmentShader,512,NULL, infoLog);
        std::cerr << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    ID =prog;
}   


void Shader::use()
{
    glUseProgram(ID);
}
void Shader::SetBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}
void Shader::SetInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}
void Shader::SetFloat(const std::string &name, float value) const
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}



