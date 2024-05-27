#include "window.h"
#include "win32_helper.h"
#include "opengl_helper.h"
#include "cglm/cglm.h"

static Window gameWindow;

void InitGameWindow(const char *title, int width, int height, BOOL resizable)
{
  gameWindow.hwnd = CreateMainWindow(title, width, height);
  gameWindow.hdc = GetDC(gameWindow.hwnd);
  gameWindow.hglrc = InitOpenGLContext(gameWindow.hdc);
  gameWindow.width = width;
  gameWindow.height = height;
  gameWindow.shouldClose = FALSE;

  ShowWindow(gameWindow.hwnd, SW_SHOW);
  UpdateWindow(gameWindow.hwnd);
}

int GetGameWindowWidth()
{
  return gameWindow.width;
}

int GetGameWindowHeight()
{
  return gameWindow.height;
}

void UpdateGameWindowSize(int width, int height)
{
  gameWindow.width = width;
  gameWindow.height = height;
}

void SwapGameWindowBuffers()
{
  SwapBuffers(gameWindow.hdc);
}

void PollGameWindowEvents()
{
  PollEvents(&gameWindow.shouldClose);
}

BOOL GameWindowShouldClose()
{
  return gameWindow.shouldClose;
}

mat4* GetProjectionMatrix()
{
  return &gameWindow.projection;
}

void UpdateProjectionMatrix()
{
  glm_ortho(0, gameWindow.width, gameWindow.height, 0, -1.0f, 1.0f, gameWindow.projection);
}
