#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

out vec4 FragColor;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 lightColor;
// maybe add shiness uniform?

void main()
{
    // Ambient
    vec3 ambient = 0.1 * lightColor;

    // Diffuse
    vec3 norm = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    vec3 V = normalize(cameraPosition - worldPosition);
    vec3 R = reflect(-lightDir, norm);

    float spec = 0.0;
    if (diff > 0.0)
    {
        spec = pow(max(dot(V, R), 0.0), 32.0);
    }

    vec3 specular = 0.5 * spec * lightColor;

    vec3 result = (ambient + diffuse) * vertexColor + specular;
    FragColor = vec4(result, 1.0);
}