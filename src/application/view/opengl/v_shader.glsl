#version 410 core
layout(location = 0) in vec3 aPos;

uniform vec3 translateVector;
uniform vec3 rotateVector;
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
  float near = 10.0f;
  float far = 90.0f;
  float right = 10.0f;
  float top = 10.0f;
  mat4 perspective = mat4(near / right, 0.0f, 0.0f, 0.0f,                    //
                          0.0f, near / top, 0.0f, 0.0f,                      //
                          0.0f, 0.0f, (far + near) / (near - far), -1.0f,    //
                          0.0f, 0.0f, 2.0f * far * near / (near - far), 0.0f);  //

  return perspective;
}

mat4 Translation() {
  mat4 translation = mat4(1.0f);
  translation[3] = vec4(translateVector, 1.0f);

  return translation;
}

void main() {
  mat4 translation = Translation();
  mat4 perspective = Perspective();
  mat4 rotation = Rotation();
  vec4 myPos = vec4(aPos, 1.0);


  gl_Position = perspectiveMatrix * translation * rotation * myPos;
}
