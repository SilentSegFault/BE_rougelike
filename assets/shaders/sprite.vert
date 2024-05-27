#version 330 core

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform int flipX;
uniform int flipY;

void main()
{
  TexCoords = vertex.zw;

  if(flipX == 1)
    TexCoords.x = 1 - TexCoords.x;

  if(flipY == 1)
    TexCoords.y = 1 - TexCoords.y;

  gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}
