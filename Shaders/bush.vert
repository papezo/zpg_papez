#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

out vec3 worldPosition;
out vec3 worldNormal;
out vec3 vertexColor;

void main()
{
    vec4 worldPos = modelMatrix * vec4(position, 1.0);
    worldPosition = worldPos.xyz;

    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNormal = normalMatrix * normal;

    vertexColor = vec3(0.1, 0.5, 0.1);

    gl_Position = projectionMatrix * viewMatrix * worldPos;
}