#version 410 core
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
flat in vec3 startPos;
in vec3 vertPos;


out vec4 FragColor;

uniform vec3 modelColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture;
uniform int vertexType;

uniform bool dashedLines;
uniform float dashSize;
uniform float gapSize;
uniform vec2 resolution;

void main() {
  float ambientStrength = 0.1f;
  vec3 ambient = ambientStrength * lightColor;
  vec3 normal = normalize(Normal);

  vec3 lightPos = vec3(1.0f, 1.0f, 1.0f);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(normal, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 result = (ambient + diffuse) * modelColor;

  vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
  if (vertexType == 2 && dot(circCoord, circCoord) > 1.0) {
    discard;
  }

  if (dashedLines && vertexType == 0) {
    vec2 dir  = (vertPos.xy - startPos.xy) * resolution / 2.0;
    float dist = length(dir);
    if (fract(dist / (dashSize + gapSize)) > dashSize / (dashSize + gapSize))
        discard;
  }


  FragColor = vec4(result, 1.0f);
}
