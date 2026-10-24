#version 330

out vec4 FragColor;

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {

    vec3 norm = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = diffuse * objectColor;
    FragColor = vec4(result, 1.0);

}