#include "game.h"
#include "../window/window.h"
#include "../window/win32_helper.h"
#include "stb/stb_ds.h"
#include "../ecs/systems.h"
#include "../resource_management/assets_library.h"
#include "../logger/logger.h"
#include "../ecs/ecs.h"
#include "../scripting/script_engine.h"
#include "../rendering/rendering_text.h"
#include "../ecs/factories.h"

Game currentGame = {0};
int pause = 0;
int drawDebug = 0;
const char *sceneToLoad = NULL;

void InitGame(void)
{
  currentGame.currentScene = NULL;
  LoadScene("StartMenu");
}

void Update(double deltaTime)
{
  currentGame.gameTime += deltaTime;
  currentGame.frameCount += 1;

  if(sceneToLoad != NULL)
  {
    LoadScene(sceneToLoad);
    sceneToLoad = NULL;
  }

  if(KeyDown(KEY_F11))
    ToggleFullScreen();

  if(KeyDown(KEY_F1))
    drawDebug = !drawDebug;

  if(KeyDown(KEY_ESC))
    pause = !pause;

  if(pause)
    return;

  Scene *scene = GetCurrentScene();
  if(scene == NULL)
    return;
  EcsUpdateSystem(scene->world, StartSystem, 0);
  EcsUpdateSystem(scene->world, UpdateSystem, deltaTime);
  EcsUpdateSystem(scene->world, AnimationSystem, 0);
  EcsUpdateSystem(scene->world, CollisionSystem, 0);
  EcsUpdateSystem(scene->world, DestroySystem, 0);
}

void Render(void)
{
  UpdateProjectionMatrix();

  Scene *scene = GetCurrentScene();
  if(scene == NULL)
    return;

  EcsUpdateSystem(scene->world, TilemapRenderSystem, 0);
  EcsUpdateSystem(scene->world, SpriteRenderSystem, 0);
  EcsUpdateSystem(scene->world, AnimationRenderSystem, 0);
  EcsUpdateSystem(scene->world, TextRenderSystem, 0);
  if(drawDebug)
    EcsUpdateSystem(GetCurrentScene()->world, RenderDebugColliderSystem, 0);

  if(pause)
    RenderText(GetShader("text"),
               GetProjectionMatrix(),
               0,
               GetFont("arial"),
               "PAUSE",
               (vec2) {GetGameWindowWidth() * 0.25f, GetGameWindowHeight() * 0.5f},
               3,
               (vec3){1.0f, 0.9f, 0.2f});
}

void DisposeGame(void)
{
  DisposeScene(GetCurrentScene());
}

void LoadScene(const char *sceneName)
{
  LogInfo("Loading scene %s", sceneName);
  Scene *scene = GetScene(sceneName);
  LoadLuaScene(sceneName);
  InitScene(scene);
  currentGame.currentScene = scene;
}

void QueueLoadScene(const char *sceneName)
{
  sceneToLoad = sceneName;
}

Scene* GetCurrentScene()
{
  return currentGame.currentScene;
}

void UnloadScene()
{
}


