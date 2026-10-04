#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

uniform vec3 uTranslation; // posun
uniform vec3 uScale; // meritko
uniform float uAngle; // uhel v radianecvh

void main()
{
    vec3 p1 = position  * uScale;
    vec3 p2;

    p2.x = p1.x * cos(uAngle) + sin(uAngle) * p1.z;
    p2.y = p1.y;
    p2.z = -sin(uAngle) * p1.x + cos(uAngle) * p1.z;

    vec3 p3 = p2 + uTranslation;

    vertexColor = color;
    gl_Position = vec4(p3, 1.0);
}