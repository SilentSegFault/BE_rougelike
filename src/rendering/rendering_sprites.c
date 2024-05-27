#include "rendering_sprites.h"
#include "cglm/cglm.h"
#include "glad/glad.h"
#include <minwindef.h>

static unsigned int rendererVAO;
void InitSpriteRenderer()
{
  unsigned int VBO;

  float vertices[] =
  {
    //pos       //tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

  glGenVertexArrays(1, &rendererVAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(rendererVAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void DrawSprite(Sprite *sprite, mat4 *projection, vec2 position, vec2 size, float rotation, int flipX, int flipY)
{
  UseShader(sprite->shader);

  mat4 model = GLM_MAT4_IDENTITY_INIT;

  glm_translate(model, (vec3){position[0], position[1], 0.0f});

  glm_rotate_at(model, (vec3){0.5f * size[0], 0.5f * size[1], 0.0f}, rotation, (vec3){0.0f, 0.0f, 1.0f});

  glm_scale(model, (vec3){size[0], size[1], 1.0f});

  ShaderSetMat4(sprite->shader, "model", model, TRUE);
  ShaderSetVector3(sprite->shader, "spriteColor", sprite->colorMask, FALSE);
  ShaderSetMat4(sprite->shader, "projection", *projection, FALSE);
  ShaderSetInteger(sprite->shader, "flipX", flipX, FALSE);
  ShaderSetInteger(sprite->shader, "flipY", flipY, FALSE);

  glActiveTexture(GL_TEXTURE0);
  BindTexture(sprite->texture);

  glBindVertexArray(rendererVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void DisposeSpriteRenderer()
{
  glDeleteVertexArrays(1, &rendererVAO);
}
