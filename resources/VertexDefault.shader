#version 430 core

layout(location = 0) in vec3 position;

out vec3 vertColor;
void main()
{
    gl_Position = vec4(position, 1.0);
    vertColor = position + 0.5;
}
