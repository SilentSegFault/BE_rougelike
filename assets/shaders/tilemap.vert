#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform int layer;

void main()
{
  TexCoords = aTexCoords;
  gl_Position = projection * model * vec4(position, layer/100.0, 1.0);
}
