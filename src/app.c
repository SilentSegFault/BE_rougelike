#include "scripting/script_engine.h"
#include "window/win32_helper.h"
#include "window/opengl_helper.h"
#include "glad/glad.h"
#include "gl/GL.h"
#include "utility/rand.h"
#include "utility/timer.h"
#include "logger/logger.h"
#include "window/window.h"
#include <synchapi.h>

#include "rendering/rendering_text.h"
#include "rendering/rendering_sprites.h"
#include "rendering/rendering_debug.h"

#include "resource_management/assets_loader.h"
#include "resource_management/assets_library.h"

#include "game/game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_DS_IMPLEMENTATION
#include "stb/stb_ds.h"

#define CUTE_C2_IMPLEMENTATION
#include "cute_headers/cute_c2.h"

#include <time.h>

void ExitHandler(void);
void ViewportSizingUpdate(HWND hwnd, int width, int height);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
  atexit(ExitHandler);

  AllocConsole();
  SetConsoleTitleA("Dev Console");

  // Redirect standard input/output to the console
  FILE* pFile;
  freopen_s(&pFile, "CONIN$", "r", stdin);
  freopen_s(&pFile, "CONOUT$", "w", stdout);
  freopen_s(&pFile, "CONOUT$", "w", stderr);

  StartTimer();

  //Init logger module
  CreateDirectory("../LOGS", NULL);
  InitLogger("../LOGS");

  LogTagInfo("Initialization", "App starting.");

  //Init game window module
  InitGameWindow("Main Window", 640, 360, FALSE);
  LoadOpenGLFunctions();
  SetWindowSizingCallback(ViewportSizingUpdate);
  LogTagInfo("Initialization", "Window Created.");

  //Init utility modules
  InitRand();

  //Init renderers modules
  InitTextRenderer();
  InitSpriteRenderer();
  InitDebugRenderer();

  //Init resource management modules
  InitAssetsLoader("../../assets");
  InitAssetsLibrary();

  //Init ecs modules
  //Init Scripting api
  InitScriptingEngine();
  int ok = RunScript("../../scripts/loader.lua");
  if(!ok)
  {
    LogDebug("Script doesnt run properly");
  }

  LogTagInfo("Initialization", "Required modules loaded.");

  //Load assets
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  LoadAssets();
  LogTagInfo("Initialization", "Assets loaded.");

  long timeStarting = StopTimerMs();
  LogTagInfo("Initialization", "App started [%lums].", timeStarting);

  const int FPS = 144;
  StartTimer();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, GetGameWindowWidth(), GetGameWindowHeight());

  InitGame();

  LogTagInfo("GameInitialization", "Game Started");

  while(!GameWindowShouldClose())
  {
    float deltaTime = StopTimerSec();
    StartTimer();

    PollGameWindowEvents();
    Update(deltaTime);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Render();
    SwapGameWindowBuffers();

    int st = (1000.f / FPS) - deltaTime;
    if(st > 0)
      Sleep(st);
  }

  return 0;
}

void ViewportSizingUpdate(HWND hwnd, int width, int height)
{
  glViewport(0, 0, width, height);
  UpdateGameWindowSize(width, height);

  float deltaTime = StopTimerSec();
  StartTimer();

  PollGameWindowEvents();
  Update(deltaTime);

  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  Render();
  SwapGameWindowBuffers();
}

void ExitHandler(void)
{
  LogTagInfo("Quiting", "Disposing resources");
  DisposeGame();
  DisposeAssets();
  DisposeTextRenderer();
  DisposeSpriteRenderer();
  DisposeDebugRenderer();
  DisposeScriptingEngine();
  LogTagInfo("Quiting", "Closing app");
  DisposeLogger();
}
