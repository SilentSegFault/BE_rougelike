#include "win32_helper.h"
#include "pico_headers/pico_log.h"
#include "../utility/error.h"
#include <minwindef.h>
#include <winuser.h>

unsigned int windowWidth, windowHeight;
int mouseX, mouseY;
WindowSizing *windowSizingCallback = NULL;

static struct
{
  BOOL IsKeyDown;
  BOOL WasKeyDown;
} keyStates[256] = {0};

LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
    case WM_CREATE:
      break;

    case WM_CLOSE:
      log_trace("Close message received.");
      DestroyWindow(hwnd);
      break;

    case WM_DESTROY:
      log_trace("Destroy message received.");
      PostQuitMessage(0);
      break;

    case WM_KEYUP:
    case WM_SYSKEYUP:
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
      keyStates[wParam].IsKeyDown = (lParam & (1 << 31)) == 0;
      keyStates[wParam].WasKeyDown = (lParam & (1 << 30)) != 0;
      break;

    case WM_MOUSEMOVE:
      mouseX = LOWORD(lParam); 
      mouseY = HIWORD(lParam);
      break;

    case WM_LBUTTONDOWN:
      keyStates[KEY_MOUSELEFT].WasKeyDown = keyStates[KEY_MOUSELEFT].IsKeyDown;
      keyStates[KEY_MOUSELEFT].IsKeyDown = TRUE;
      break;

    case WM_LBUTTONUP:
      keyStates[KEY_MOUSELEFT].WasKeyDown = keyStates[KEY_MOUSELEFT].IsKeyDown;
      keyStates[KEY_MOUSELEFT].IsKeyDown = FALSE;
      break;

    case WM_SIZE:
    case WM_SIZING:
      {
        log_trace("Sizing message recived.");
        RECT rc;
        GetClientRect(hwnd, &rc);
        windowWidth = rc.right - rc.left;
        windowHeight = rc.bottom - rc.top;

        if(windowSizingCallback != NULL)
          windowSizingCallback(hwnd, windowWidth, windowHeight);
      }
      break;
    
    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  return 0;
}

HWND CreateMainWindow(const char *title, int width, int height)
{
  log_info("Creating main window.");
  WNDCLASSEX wc;

  wc.cbSize        = sizeof(wc);
  wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc   = WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = GetModuleHandle(NULL);
  wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = "MaindWndClass";
  wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

  if(!RegisterClassEx(&wc))
  {
    log_fatal("Failed to initialize main window class.");
    FATAL_ERROR();
  }

  RECT rc;
  SetRect(&rc, 0, 0, width, height);
  AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
  windowWidth  = rc.right  - rc.left;
  windowHeight = rc.bottom - rc.top;
  

  HWND hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_TOPMOST, wc.lpszClassName, title, WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
                             NULL, NULL, GetModuleHandle(NULL), NULL);

  if(hwnd == NULL)
  {
    log_fatal("Failed to create main window.");
    FATAL_ERROR();
  }

  log_info("Main window created.");
  return hwnd;
}

void SetWindowSizingCallback(WindowSizing *callback)
{
  windowSizingCallback = callback;
}

void PollEvents(BOOL *bWindowShouldClose)
{
  static MSG msg;
  (*bWindowShouldClose) = FALSE;
  while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    if(msg.message == WM_QUIT)
    {
      (*bWindowShouldClose) = TRUE;
    }
    else
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

BOOL KeyPressed(Key key)
{
  return keyStates[key].IsKeyDown;
}

BOOL KeyDown(Key key)
{
  return keyStates[key].IsKeyDown && (GetAsyncKeyState(key) & 0x1) && !keyStates[key].WasKeyDown;
}
