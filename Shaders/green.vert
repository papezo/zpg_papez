#version 330 core

layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position * 0.1 + vec3(0.5, 0.0, 0.0), 1.0);
}