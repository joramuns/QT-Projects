#version 410 core
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec4 modelColor;
uniform vec4 lightColor;

void main()
{   
    float ambientStrength = 0.1f;
    vec4 ambient = ambientStrength * lightColor;
    
    vec3 lightPos = vec3(0.5f);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 normal = normalize(Normal);
    float diff = max(dot(normal, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;

    FragColor = (ambient + diffuse) * modelColor;
}