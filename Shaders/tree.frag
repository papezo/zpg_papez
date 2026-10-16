#version 330 core

in vec3 vertexNormal;
in vec3 vertexColor;

out vec4 FragColor;

void main()
{
    float shade = 0.3 + 0.7 * abs(normalize(vertexNormal).y);

    if (vertexColor.g > vertexColor.r)
        FragColor = vec4(shade * vertexColor, 1.0);
    else
        FragColor = vec4(vertexColor, 1.0);
}
