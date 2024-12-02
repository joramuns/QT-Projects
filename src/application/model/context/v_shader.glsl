#version 410 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
flat out vec3 startPos;
out vec3 vertPos;
out vec3 fragLightPos;
out vec3 gouraudLight;
uniform vec3 translateVector;
uniform vec3 rotateVector;
uniform vec3 scaleVector;
uniform mat4 perspectiveMatrix;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform int lightMode;

mat4 RotateX() {
    mat4 rotation = mat4(1.0f);
    float sin = sin(rotateVector.x);
    float cos = cos(rotateVector.x);
    rotation[1][1] = cos;
    rotation[1][2] = sin;
    rotation[2][1] = -sin;
    rotation[2][2] = cos;
    return rotation;
}

mat4 RotateY() {
    mat4 rotation = mat4(1.0f);
    float sin = sin(rotateVector.y);
    float cos = cos(rotateVector.y);
    rotation[0][0] = cos;
    rotation[2][0] = sin;
    rotation[0][2] = -sin;
    rotation[2][2] = cos;
    return rotation;
}

mat4 RotateZ() {
    mat4 rotation = mat4(1.0f);
    float sin = sin(rotateVector.z);
    float cos = cos(rotateVector.z);
    rotation[0][0] = cos;
    rotation[0][1] = sin;
    rotation[1][0] = -sin;
    rotation[1][1] = cos;
    return rotation;
}

mat4 Rotation() { return RotateX() * RotateY() * RotateZ(); }

mat4 Translation() {
    mat4 translation = mat4(1.0f);
    translation[3] = vec4(translateVector.xy, translateVector.z - 1.0f, 1.0f);
    return translation;
}

mat4 Scaling() {
    mat4 scaling = mat4(1.0f);
    scaling[0][0] = scaleVector.x;
    scaling[1][1] = scaleVector.y;
    scaling[2][2] = scaleVector.z;
    return scaling;
}

vec3 calculateGouraudLighting(vec3 fragPos, vec3 normal) {
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    vec3 lightDir = normalize(fragLightPos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    return ambient + diffuse;
}

void main() {
    mat4 rotation = Rotation();
    mat4 translation = Translation();
    mat4 scaling = Scaling();
    vec4 myPos = vec4(position, 1.0);
    mat4 mvp = perspectiveMatrix * translation * rotation * scaling;

    gl_Position = mvp * myPos;
    FragPos = vec3(translation * rotation * scaling * myPos);
    Normal = mat3(translation) * mat3(rotation) * normal;
    TexCoord = texCoord;
    vertPos = gl_Position.xyz / gl_Position.w;
    startPos = vertPos;
    fragLightPos = (translation * vec4(lightPos, 1.0)).xyz;

    // Calculate Gouraud lighting in vertex shader
    if (lightMode == 2) {
        gouraudLight = calculateGouraudLighting(FragPos, Normal);
    }
}

