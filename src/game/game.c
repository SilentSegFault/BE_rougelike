#include "game.h"
#include "../window/win32_helper.h"
#include "../resource_manager/resource_manager.h"
#include "../rendering/rendering_sprites.h"
#include "../ecs/ecs.h"
#include "glad/glad.h"
#include "pico_headers/pico_log.h"
#include "cglm/cglm.h"
#include <stdio.h>

#define GLT_IMPLEMENTATION
#include "glText/gltext.h"

ecs_t *ecs = NULL;
GLTtext *fpsText;
unsigned long long frameCount = 0;

void InitGame(void)
{
  log_info("Game initialization started.");
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, windowWidth, windowHeight);
  InitSpriteRenderer();
  gltInit();

  LoadShader("../../assets/shaders/default.vert", "../../assets/shaders/default.frag", NULL, "default");
  LoadTexture("../../assets/textures/smiley-face-icon.png", TRUE, "smiley");
  LoadTexture("../../assets/textures/soldier.png", TRUE, "soldier");
  LoadTexture("../../assets/textures/bullet.png", TRUE, "bullet");

  fpsText = gltCreateText();

  log_debug("Creating ecs context");
  ecs = ecs_new(1024, NULL);

  RegisterComponents(ecs);
  RegisterSystems(ecs);

  CreatePlayer(ecs, 200.0f, 200.0f);

  log_info("Game initialization finished.");
}

void Update(double deltaTime)
{
  frameCount++;
  if(frameCount % 10 == 0)
  {
    char fps[50];
    sprintf_s(fps, 50, "%i FPS", (int)(1.0/deltaTime));
    gltSetText(fpsText, fps);
  }

  ecs_update_system(ecs, PlayerControllerSys, deltaTime);
  ecs_update_system(ecs, ProjectileSys, deltaTime);
}

void Render(HDC hdc)
{
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);


  mat4 projection;
  glm_ortho(0, windowWidth, windowHeight, 0, -1.0f, 1.0f, projection);
  ShaderSetMat4(GetShader("default"), "projection", projection);
  
  ecs_update_system(ecs, SpriteRenderSys, 1.0f);

  gltBeginDraw();

  gltDrawText2D(fpsText, 0, 0, 1.0f);

  gltEndDraw();

  SwapBuffers(hdc);
}

void DisposeGame()
{
  log_info("Clearing resources.");
  DisposeSpriteRenderer();
  gltDeleteText(fpsText);
  gltTerminate();
  ecs_free(ecs);
  log_info("Resources cleared.");
}
