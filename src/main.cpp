
#include<windows.h>
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

//user
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include "Shader.hpp"
// #include "Texture.hpp"
#include "Object.hpp"

using namespace std;

int main(int argc, char** args)
{
    Object lel("Cube.obj");
    lel.Debug();
return 0;
}