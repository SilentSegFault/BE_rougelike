#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include "cglm/types.h"

typedef struct 
{
  HWND hwnd;
  HDC hdc;
  HGLRC hglrc;
  int width;
  int height;
  BOOL shouldClose;
  mat4 projection;
  WINDOWPLACEMENT prevPlacement;
} Window;

void InitGameWindow(const char *name, int width, int height, BOOL resizable);
int GetGameWindowWidth();
int GetGameWindowHeight();
float GetMouseX();
float GetMouseY();
void UpdateGameWindowSize(int width, int height);
void SwapGameWindowBuffers();
void PollGameWindowEvents();
BOOL GameWindowShouldClose();
mat4* GetProjectionMatrix();
void UpdateProjectionMatrix();
void ToggleFullScreen();
void QuitApp();

#endif
