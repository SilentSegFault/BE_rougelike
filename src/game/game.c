#include "game.h"
#include "../window/window.h"
#include "../window/win32_helper.h"
#include "stb/stb_ds.h"
#include "flecs/flecs.h"
#include "../ecs/factories.h"
#include "../ecs/components.h"
#include "../ecs/systems.h"
#include "../scripting/script_engine.h"
#include <stdlib.h>
#include "../resource_management/assets_library.h"
#include "../logger/logger.h"

Game currentGame = {0};
ecs_world_t *world;

void InitGame(void)
{
  LoadScene(GetScene("testScene"));
}

void Update(double deltaTime)
{
  currentGame.gameTime += deltaTime;
  currentGame.frameCount += 1;

  if(KeyDown(KEY_F11))
    ToggleFullScreen();

  UpdateEntities(deltaTime);
}

void Render(void)
{
  UpdateProjectionMatrix();
  ecs_run(GetCurrentScene()->world, ecs_id(SpriteRenderSystem), 0, NULL);
}

void DisposeGame(void)
{
  ecs_fini(GetCurrentScene()->world);
}

void LoadScene(Scene *scene)
{
  InitScene(scene);
  currentGame.currentScene = scene;
}

Scene* GetCurrentScene()
{
  return currentGame.currentScene;
}

void UnloadScene()
{
}


