#include "rendering_debug.h"
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "../shader/shader.h"
#include "../resource_management/assets_library.h"

static unsigned int debugVAO;
void InitDebugRenderer()
{
  unsigned int VBO;

  float vertices[] =
  {
    //pos
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
  };

  glGenVertexArrays(1, &debugVAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(debugVAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void DrawRect(mat4 *projection, vec2 pos, vec2 size, float rotation, vec3 color)
{
  Shader shader = *GetShader("debug");

  mat4 model = GLM_MAT4_IDENTITY_INIT;
  glm_translate(model, (vec3){pos[0], pos[1], 0.0f});
  glm_rotate_at(model, (vec3){0.5f * size[0], 0.5f * size[1], 0.0f}, rotation, (vec3){0.0f, 0.0f, 1.0f});
  glm_scale(model, (vec3){size[0], size[1], 1.0f});

  ShaderSetMat4(shader, "model", model, TRUE);
  ShaderSetVector3(shader, "color", color, FALSE);
  ShaderSetMat4(shader, "projection", *projection, FALSE);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBindVertexArray(debugVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void DisposeDebugRenderer()
{
  glDeleteVertexArrays(1, &debugVAO);
}
