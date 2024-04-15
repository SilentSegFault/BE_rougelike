#include "game.h"
#include "../window/window.h"
#include "../resource_manager/resource_manager.h"
#include "../rendering/rendering_sprites.h"
#include "../ecs/ecs.h"
#include "../utility/error.h"
#include "glad/glad.h"
#include "pico_headers/pico_log.h"
#include "cglm/cglm.h"

ecs_t *ecs = NULL;

Sprite test;

void InitGame(void)
{
  log_info("Game initialization started.");
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, windowWidth, windowHeight);
  InitSpriteRenderer();

  test.shader = LoadShader("../../assets/shaders/default.vert", "../../assets/shaders/default.frag", NULL, "default");
  test.texture = LoadTexture("../../assets/textures/smiley-face-icon.png", TRUE, "smiley");

  test.colorMask[0] = 1.0f;
  test.colorMask[1] = 1.0f;
  test.colorMask[2] = 1.0f;

  log_debug("Creating ecs context");
  ecs = ecs_new(1024, NULL);

  RegisterComponents(ecs);
  RegisterSystems(ecs);

  CreateSmiley(ecs, 10.0f, 10.0f);
  CreateSmiley(ecs, 100.0f, 10.0f);
  CreateSmiley(ecs, 10.0f, 100.0f);

  log_info("Game initialization finished.");
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
  ShaderSetMat4(GetShader("default"), "projection", projection);
  
  ecs_update_system(ecs, SpriteRenderSys, 1.0f);

  //vec2 pos = {100.0f, 10.0f};
  //vec2 size = {30.0f, 30.0f};
  //float rotation = 0;
  //DrawSprite(test, pos, size, rotation);


  //pos[1] = 100.0f;
  //DrawSprite(test, pos, size, rotation);

  SwapBuffers(hdc);
}

void DisposeGame()
{
  log_info("Clearing resources.");
  DisposeSpriteRenderer();
  ecs_free(ecs);
  log_info("Resources cleared.");
}
