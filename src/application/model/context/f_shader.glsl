#version 410 core
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
flat in vec3 startPos;
in vec3 vertPos;
in vec3 fragLightPos;
in vec3 gouraudLight;
out vec4 FragColor;
uniform vec3 modelColor;
uniform vec3 lightColor;
uniform int lightMode;
uniform sampler2D ourTexture;
uniform int vertexType;
uniform bool dashedLines;
uniform float dashSize;
uniform float gapSize;
uniform vec2 resolution;

vec3 calculateLighting() {
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    if (lightMode == 0) {
        return lightColor;
    }
    else if (lightMode == 1) {
        // Flat shading - use face normal
        vec3 normal = normalize(cross(dFdx(FragPos), dFdy(FragPos)));
        vec3 lightDir = normalize(fragLightPos - FragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        return (ambient + diffuse);
    }
    else if (lightMode == 2) {
        // Gouraud shading - use interpolated lighting from vertex shader
        return gouraudLight;
    }
    else {
        // Phong shading - calculate lighting per fragment
        vec3 normal = normalize(Normal);
        vec3 lightDir = normalize(fragLightPos - FragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        return (ambient + diffuse);
    }
}

void main() {
    vec3 result = calculateLighting() * modelColor;

    vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
    if (vertexType == 2 && dot(circCoord, circCoord) > 1.0) {
        discard;
    }

    if (dashedLines && vertexType == 0) {
        vec2 dir = (vertPos.xy - startPos.xy) * resolution / 2.0;
        float dist = length(dir);
        if (fract(dist / (dashSize + gapSize)) > dashSize / (dashSize + gapSize))
            discard;
    }

    FragColor = vec4(result, 1.0f);
}

