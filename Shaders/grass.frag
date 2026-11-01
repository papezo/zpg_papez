#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

out vec4 FragColor;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 lightColor;
uniform float shiness;

uniform float attenuationConstant;
uniform float attenuationLinear;
uniform float attenuationQuadratic;

float attenuation(float d, float c, float l, float q)
{
    // d = distance from the light to the fragment
    // c = constant attenuation factor
    // l = linear attenuation factor
    // q = quadratic attenuation factor
    float att=1.0/ (c + l*d + q*d*d);
    return clamp(att , 0.0 , 1.0);
}

void main()
{
    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 viewDir = normalize(cameraPosition - worldPosition);

    // Ambient
    vec3 ambient = 1.0 * lightColor;

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

    float dist = length(lightPosition - worldPosition );

    float att = attenuation(dist, attenuationConstant, attenuationLinear, attenuationQuadratic);

    vec3 result = att * ((ambient + diffuse) * vertexColor + specular);
    FragColor = vec4(result, 1.0);
}