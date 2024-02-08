#version 410 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
flat out vec3 startPos;
out vec3 vertPos;


uniform vec3 translateVector;
uniform vec3 rotateVector;
uniform vec3 scaleVector;
uniform mat4 perspectiveMatrix;

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

mat4 Perspective() {
  float near = 0.1f;
  float far = 9.0f;
  float right = 1.1f;
  float top = 1.1f;
  mat4 perspective = mat4(near / right, 0.0f, 0.0f, 0.0f,                     //
                          0.0f, near / top, 0.0f, 0.0f,                       //
                          0.0f, 0.0f, -(far + near) / (far - near), -1.0f,    //
                          0.0f, 0.0f, -2 * far * near / (far - near), 0.0f);  //

  return perspective;
}

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

void main() {
  mat4 perspective = perspectiveMatrix;
  mat4 rotation = Rotation();
  mat4 translation = Translation();
  mat4 scaling = Scaling();
  vec4 myPos = vec4(aPos, 1.0);

  mat4 mvp = perspective * translation * rotation * scaling;

  gl_Position = mvp * myPos;
  FragPos = vec3(translation * rotation * scaling * myPos);
  Normal = normal;
  TexCoord = texCoord;

  vertPos = gl_Position.xyz / gl_Position.w;
  startPos = vertPos;
}
