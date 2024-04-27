///@file

#include "rendering/rendering_sprites.h"
#include "window/win32_helper.h"
#include "window/opengl_helper.h"
#include "game/game.h"
#include "glad/glad.h"
#include "gl/GL.h"
#include "utility/rand.h"
#include "pico_headers/pico_log.h"
#include <synchapi.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_DS_IMPLEMENTATION
#include "stb/stb_ds.h"

#define PICO_LOG_IMPLEMENTATION
#include "pico_headers/pico_log.h"

#define PICO_ECS_IMPLEMENTATION
#include "pico_headers/pico_ecs.h"

#define GLT_IMPLEMENTATION
#define GLT_MANUAL_VIEWPORT
#include "glText/gltext.h"

#define CUTE_C2_IMPLEMENTATION
#include "cute_headers/cute_c2.h"

#include <time.h>

void InitLogger(char *logDirPath, log_level_t logLevel);
void ExitHandler(void);
void ViewportSizingUpdate(HWND hwnd, int width, int height);
BOOL DirectoryExists(LPCTSTR szPath);
void DisposeLogger(void);

FILE *g_hLogFile = NULL; ///< handler for logs file

////////////////////////////////////////
///
/// @brief Entry point of app.
///
/// Everything that is needed to run app is initialized here. Handles main game/app loop. 
/// For more info on WinMian go to [Microsoft Docs](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain).
///
///////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
  clock_t beginApp = clock();
  CreateDirectory("../LOGS", NULL);
  InitLogger("../LOGS", LOG_LEVEL_DEBUG);
  log_info("App starting.");
  atexit(ExitHandler);
  InitRand();

  HWND hMainWindow = CreateMainWindow("Main Window", 640, 480);
  HDC hMainWindowDC = GetDC(hMainWindow);
  if(hMainWindowDC == NULL)
  {
    log_fatal("main window dc is NULL!!");
  }
  HGLRC hMainWindowRC = InitOpenGLContext(hMainWindowDC);

  LoadOpenGLFunctions();

  InitGame();
  SetWindowSizingCallback(ViewportSizingUpdate);

  ShowWindow(hMainWindow, nCmdShow);
  UpdateWindow(hMainWindow);

  clock_t appStarted = clock();
  unsigned long timeStarting = 1000 * (double)(appStarted - beginApp) / CLOCKS_PER_SEC;
  log_debug("App started [%lums]", timeStarting);

  clock_t start = clock();
  clock_t diff;

  BOOL bWindowShouldClose = FALSE;
  while(!bWindowShouldClose)
  {
    diff = clock() - start;
    float deltaTime = (float)diff / CLOCKS_PER_SEC;
    start = clock();

    PollEvents(&bWindowShouldClose);
    Update(deltaTime);
    Render(hMainWindowDC);

    int st = (1000.f / 144.f) - deltaTime;
    if(st > 0)
      Sleep(st);
  }

  return 0;
}

////////////////////////////////////////
///
/// @brief Runs everytime window is resized.
///
/// Updates openGL viewport and draws one frame. If frame wasn't drawn there would be black borders while resizing window until mouse would be released.
///
/// @param hwnd handle to resized window
/// @param width new window width
/// @param height new window height
///
///////////////////////////////////////
void ViewportSizingUpdate(HWND hwnd, int width, int height)
{
  glViewport(0, 0, width, height);
  gltViewport(width, height);
  Render(GetDC(hwnd));
}

////////////////////////////////////////
///
/// @brief Checks if given directory exists (WinApi style).
///
/// @param[in] szPath the path that will be checked
///
////////////////////////////////////////
BOOL DirectoryExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

////////////////////////////////////////
///
/// @brief Creates or opens proper file for logger and initializes it with right format and log level.
///
/// @param[in] logDirPath path to directory in which the logs will be stored
/// @param[in] logLevel level of logs to set during initialization
///
////////////////////////////////////////
void InitLogger(char *logDirPath, log_level_t logLevel)
{

  SYSTEMTIME st;
  GetLocalTime(&st);

  char logsSubDirectory[24];
  sprintf(logsSubDirectory, "Logs_%02d_%02d_%04d", st.wDay, st.wMonth, st.wYear);

  char logsFile[16];
  sprintf(logsFile, "Log_%02d_%02d.log", st.wHour, st.wMinute);

  char pathToSubDirectory[MAX_PATH];
  sprintf(pathToSubDirectory, "%s/%s", logDirPath, logsSubDirectory);

  if(!DirectoryExists(pathToSubDirectory))
    CreateDirectory(pathToSubDirectory, NULL);

  char logFilePath[MAX_PATH];
  sprintf(logFilePath, "%s/%s/%s", logDirPath, logsSubDirectory, logsFile);

  g_hLogFile = fopen(logFilePath, "a");
  log_appender_t logger;
  if(g_hLogFile != NULL)
  {
    logger = log_add_stream(g_hLogFile, logLevel);

    log_set_time_fmt(logger, "%H:%M:%S");
    log_display_timestamp(logger, TRUE);
    log_display_function(logger, TRUE);
  }
}

////////////////////////////////////////
///
/// @brief Closes logger file handler.
///
////////////////////////////////////////
void DisposeLogger(void)
{

  if(g_hLogFile != NULL)
    fclose(g_hLogFile);
}

////////////////////////////////////////
///
/// @brief Callback which handles cleaning up when app exits.
///
////////////////////////////////////////
void ExitHandler(void)
{
  log_info("App closing.");
  DisposeGame();
  log_info("Quiting.");
  DisposeLogger();
}
