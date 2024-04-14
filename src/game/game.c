#include "game.h"
#include "../window/window.h"
#include "../resource_manager/resource_manager.h"
#include "../rendering/rendering_sprites.h"
#include "glad/glad.h"
#include "pico_headers/pico_log.h"
#include <minwindef.h>
#include "cglm/cglm.h"

Sprite testSprite;

void InitGame(void)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, windowWidth, windowHeight);
  InitSpriteRenderer();

  testSprite.shader = LoadShader("../../assets/shaders/default.vert", "../../assets/shaders/default.frag", NULL, "default");
  testSprite.texture = LoadTexture("../../assets/textures/smiley-face-icon.png", TRUE, "face");
  testSprite.colorMask[0] = 1.0f;
  testSprite.colorMask[1] = 1.0f;
  testSprite.colorMask[2] = 1.0f;
}

void Update(double deltaTime)
{

}

void Render(HDC hdc)
{
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);


  mat4 projection;
  glm_ortho(0, windowWidth, windowHeight, 0, -1.0f, 1.0f, projection);

  ShaderSetMat4(testSprite.shader, "projection", projection);

  DrawSprite(testSprite, (vec2){10.0f, 10.0f}, (vec2){100.0f, 100.0f}, 0);

  SwapBuffers(hdc);
}

void DisposeGame()
{
  log_info("Clearing resources.");
  DisposeSpriteRenderer();
  log_info("Resources cleared.");
}
