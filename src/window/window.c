#include "window.h"
#include "win32_helper.h"
#include "opengl_helper.h"
#include "cglm/cglm.h"
#include <windows.h>

static Window gameWindow;

void InitGameWindow(const char *title, int width, int height, BOOL resizable)
{
  gameWindow.hwnd = CreateMainWindow(title, width, height);
  gameWindow.hdc = GetDC(gameWindow.hwnd);
  gameWindow.hglrc = InitOpenGLContext(gameWindow.hdc);
  gameWindow.width = width;
  gameWindow.height = height;
  gameWindow.shouldClose = FALSE;
  gameWindow.prevPlacement.length = sizeof(WINDOWPLACEMENT);

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

float GetMouseX()
{
  float ratio = (float)mouseX / gameWindow.width;
  return ratio * 1920;
}

float GetMouseY()
{
  float ratio = (float)mouseY / gameWindow.height;
  return ratio * 1080;
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

void ToggleFullScreen()
{
  DWORD dwStyle = GetWindowLong(gameWindow.hwnd, GWL_STYLE);
  if (dwStyle & WS_OVERLAPPEDWINDOW) {
    MONITORINFO mi = { sizeof(mi) };
    if (GetWindowPlacement(gameWindow.hwnd, &gameWindow.prevPlacement) &&
        GetMonitorInfo(MonitorFromWindow(gameWindow.hwnd,
                       MONITOR_DEFAULTTOPRIMARY), &mi)) {
      SetWindowLong(gameWindow.hwnd, GWL_STYLE,
                    dwStyle & ~WS_OVERLAPPEDWINDOW);
      SetWindowPos(gameWindow.hwnd, HWND_TOP,
                   mi.rcMonitor.left, mi.rcMonitor.top,
                   mi.rcMonitor.right - mi.rcMonitor.left,
                   mi.rcMonitor.bottom - mi.rcMonitor.top,
                   SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }
  } else {
    SetWindowLong(gameWindow.hwnd, GWL_STYLE,
                  dwStyle | WS_OVERLAPPEDWINDOW);
    SetWindowPlacement(gameWindow.hwnd, &gameWindow.prevPlacement);
    SetWindowPos(gameWindow.hwnd, NULL, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                 SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
  }
}

void QuitApp()
{
  gameWindow.shouldClose = TRUE;
}
