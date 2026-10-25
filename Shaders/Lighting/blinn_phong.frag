#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;

out vec4 FragColor;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float shiness;

void main()
{
    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 viewDir = normalize(cameraPosition - worldPosition);

    // Ambient
    vec3 ambient = 0.1 * lightColor;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float spec = 0.0;

    if (diff > 0.0)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), shiness);
    }

    vec3 specular = 0.5 * lightColor * spec;

    vec3 result = (ambient + diffuse) * objectColor + specular;
    FragColor = vec4(result, 1.0);
}