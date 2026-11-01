#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

uniform mat4 modelMatrix=mat4(1.0);
uniform mat4 viewMatrix=mat4(1.0);
uniform mat4 projectionMatrix=mat4(1.0);

out vec3 worldPosition=vec3(0.0);
out vec3 vertexColor;
out vec3 worldNormal=vec3(0.0,1.0,0.0);


void main(void){
    vec4 pos = modelMatrix * vec4(position,1.0f);
    worldPosition = pos.xyz/pos.w;
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNormal = transpose(inverse(mat3(modelMatrix))) * normal;
    // mat3(modelMatrix) * normal;transpose(inverse(mat3(modelMatrix))) * normal;
    //

    vertexColor = color;
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(position,1.0f);
}