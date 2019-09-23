#version 330 core
layout (location = 0) in vec3 uiPos;




void main()
{
    gl_Position= vec4(uiPos.x,uiPos.y,uiPos.z,1.0)
}

