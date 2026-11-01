#version 330 core
uniform vec3 glowColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(glowColor, 1.0);
}