#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 hourMatrix;
uniform mat4 minuteMatrix;
uniform mat4 secondMatrix;

out vec3 vertexColor;

void main()
{
    vec4 pos = vec4(position, 1.0);
    vertexColor = color;

    if (color.b > 0.9 && color.r < 0.1 && color.g < 0.1) {
        pos = hourMatrix * pos; // red hand
    }
    else if (color.g > 0.9 && color.r < 0.1 && color.b < 0.1) {
        pos = minuteMatrix * pos; // gree hand
    }
    else if (color.r > 0.9 && color.g < 0.1 && color.b < 0.1) {
        pos = secondMatrix * pos; // blue hand
    } 
    else if(color == vec3(1.0, 1.0, 0.0)) {
        vertexColor = vec3(0.02, 0.76, 0.87); // to set logo color
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * pos;
}