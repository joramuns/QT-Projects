#version 410 core
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 modelColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture;

void main()
{   
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    vec3 normal = normalize(Normal);
    
    vec3 lightPos = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * modelColor;
    FragColor = vec4(result, 1.0f);
}