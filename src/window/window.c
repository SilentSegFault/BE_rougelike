#include "window.h"
#include "glad/glad.h"
#include <Windows.h>
#include "pico_headers/pico_log.h"
#include "../utility/error.h"

unsigned int windowWidth, windowHeight;
WindowSizing *windowSizingCallback = NULL;
wglCreateContextAttribsARB_t *wglCreateContextAttribsARB;
wglChoosePixelFormatARB_t *wglChoosePixelFormatARB;

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

void* GetAnyGLFuncAddress(const char *name)
{
  void *p = wglGetProcAddress(name);

  if((p == NULL) || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1))
  {
    HMODULE hModule = LoadLibrary("opengl32.dll");
    p = GetProcAddress(hModule, name);
  }

  return p;
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

void _InitGLContextExtensions(void)
{
  log_debug("Initializing openGL extension required for creating openGL context.");
  WNDCLASS wc = {0};
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = DefWindowProc;
  wc.hInstance = GetModuleHandle(NULL);
  wc.lpszClassName = "DummyWndClass";

  if(!RegisterClass(&wc))
  {
    log_fatal("Failed to initialize dummy window class.");
    FATAL_ERROR();
  }

  HWND hDummyWindow = CreateWindow(wc.lpszClassName, NULL, 0,
                                   0, 0, 0, 0,
                                   NULL, NULL, wc.hInstance, NULL);

  if(hDummyWindow == NULL)
  {
    log_fatal("Failed to create dummy window.");
    FATAL_ERROR();
  }

  HDC hDummyDC = GetDC(hDummyWindow);

  PIXELFORMATDESCRIPTOR pfd;
 
  pfd.nSize        = sizeof(pfd);
  pfd.nVersion     = 1;
  pfd.iPixelType   = PFD_TYPE_RGBA;
  pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.cColorBits   = 32;
  pfd.cAlphaBits   = 8;
  pfd.iLayerType   = PFD_MAIN_PLANE;
  pfd.cDepthBits   = 24;
  pfd.cStencilBits = 8;

  int pixelFormat = ChoosePixelFormat(hDummyDC, &pfd);
  if(!pixelFormat)
  {
    log_fatal("Failed to initialize dummy pixel format.");
    FATAL_ERROR();
  }

  if(!SetPixelFormat(hDummyDC, pixelFormat, &pfd))
  {
    log_fatal("Failed to set dummy pixel format.");
    FATAL_ERROR();
  }

  HGLRC hDummyRC = wglCreateContext(hDummyDC);
  if(!hDummyRC)
  {
    log_fatal("Failed to create dummy rendering context.");
    FATAL_ERROR();
  }

  if(!wglMakeCurrent(hDummyDC, hDummyRC))
  {
    log_fatal("Failed setting current dummy rendering context.");
    FATAL_ERROR();
  }

  wglCreateContextAttribsARB = GetAnyGLFuncAddress("wglCreateContextAttribsARB");
  wglChoosePixelFormatARB = GetAnyGLFuncAddress("wglChoosePixelFormatARB");

  if(!wglCreateContextAttribsARB || ! wglChoosePixelFormatARB)
  {
    log_fatal("Failed loading functions required for setting openGL context.");
    FATAL_ERROR();
  }

  wglMakeCurrent(hDummyDC, 0);
  wglDeleteContext(hDummyRC);
  ReleaseDC(hDummyWindow, hDummyDC);
  DestroyWindow(hDummyWindow);

  log_debug("openGL extensions required for creating context initialized.");
}

HGLRC InitOpenGLContext(HDC hdc)
{
  log_info("Initializing openGL context.");
  _InitGLContextExtensions();


  int pixelFormatAttribs[] =
    {
      WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
      WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
      WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
      WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
      WGL_COLOR_BITS_ARB,     32,
      WGL_DEPTH_BITS_ARB,     24,
      WGL_STENCIL_BITS_ARB,   8,
      0
    };

  int iPixelFormat;
  unsigned int nNumFormats;
  wglChoosePixelFormatARB(hdc, pixelFormatAttribs, 0, 1, &iPixelFormat, &nNumFormats);

  if(!nNumFormats)
  {
    log_fatal("Failed to choose pixel format.");
    FATAL_ERROR();
  }

  PIXELFORMATDESCRIPTOR pfd;
  DescribePixelFormat(hdc, iPixelFormat, sizeof(pfd), &pfd);
  if(!SetPixelFormat(hdc, iPixelFormat, &pfd))
  {
    log_fatal("Failed to set pixel format.");
    FATAL_ERROR();
  }

  int contextAttribs[] = 
    {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      WGL_CONTEXT_MINOR_VERSION_ARB, 3,
      WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      0
    };

  HGLRC hglrc = wglCreateContextAttribsARB(hdc, 0, contextAttribs);
  if(!hglrc)
  {
    log_fatal("Failed to create context attributes.");
    FATAL_ERROR();
  }

  if(!wglMakeCurrent(hdc, hglrc))
  {
    log_fatal("Failed to set current rendering context.");
    FATAL_ERROR();
  }

  log_info("OpenGL context initialized.");
  return hglrc;
}

void LoadOpenGLFunctions(void)
{
  if(!gladLoadGLLoader(GetAnyGLFuncAddress))
  {
    log_fatal("Failed to load openGL function pointers.");
    FATAL_ERROR();
  }
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

void SetWindowSizingCallback(WindowSizing *callback)
{
  windowSizingCallback = callback;
}
