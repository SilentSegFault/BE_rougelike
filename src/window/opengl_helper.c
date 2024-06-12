#include "opengl_helper.h"
#include "glad/glad.h"
#include "../utility/error.h"
#include "../logger/logger.h"

wglCreateContextAttribsARB_t *wglCreateContextAttribsARB;
wglChoosePixelFormatARB_t *wglChoosePixelFormatARB;

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

void _InitGLContextExtensions(void)
{
  WNDCLASS wc = {0};
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = DefWindowProc;
  wc.hInstance = GetModuleHandle(NULL);
  wc.lpszClassName = "DummyWndClass";

  if(!RegisterClass(&wc))
  {
    LogFatal("Failed to initialize dummy window class.");
    FATAL_ERROR();
  }

  HWND hDummyWindow = CreateWindow(wc.lpszClassName, NULL, 0,
                                   0, 0, 0, 0,
                                   NULL, NULL, wc.hInstance, NULL);

  if(hDummyWindow == NULL)
  {
    LogFatal("Failed to create dummy window.");
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
    LogFatal("Failed to initialize dummy pixel format.");
    FATAL_ERROR();
  }

  if(!SetPixelFormat(hDummyDC, pixelFormat, &pfd))
  {
    LogFatal("Failed to set dummy pixel format.");
    FATAL_ERROR();
  }

  HGLRC hDummyRC = wglCreateContext(hDummyDC);
  if(!hDummyRC)
  {
    LogFatal("Failed to create dummy rendering context.");
    FATAL_ERROR();
  }

  if(!wglMakeCurrent(hDummyDC, hDummyRC))
  {
    LogFatal("Failed setting current dummy rendering context.");
    FATAL_ERROR();
  }

  wglCreateContextAttribsARB = GetAnyGLFuncAddress("wglCreateContextAttribsARB");
  wglChoosePixelFormatARB = GetAnyGLFuncAddress("wglChoosePixelFormatARB");

  if(!wglCreateContextAttribsARB || ! wglChoosePixelFormatARB)
  {
    LogFatal("Failed loading functions required for setting openGL context.");
    FATAL_ERROR();
  }

  wglMakeCurrent(hDummyDC, 0);
  wglDeleteContext(hDummyRC);
  ReleaseDC(hDummyWindow, hDummyDC);
  DestroyWindow(hDummyWindow);
}

HGLRC InitOpenGLContext(HDC hdc)
{
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
    LogFatal("Failed to choose pixel format.");
    FATAL_ERROR();
  }

  PIXELFORMATDESCRIPTOR pfd;
  DescribePixelFormat(hdc, iPixelFormat, sizeof(pfd), &pfd);
  if(!SetPixelFormat(hdc, iPixelFormat, &pfd))
  {
    LogFatal("Failed to set pixel format.");
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
    LogFatal("Failed to create context attributes.");
    FATAL_ERROR();
  }

  if(!wglMakeCurrent(hdc, hglrc))
  {
    LogFatal("Failed to set current rendering context.");
    FATAL_ERROR();
  }
  return hglrc;
}

void LoadOpenGLFunctions(void)
{
  if(!gladLoadGLLoader(GetAnyGLFuncAddress))
  {
    LogFatal("Failed to load openGL function pointers.");
    FATAL_ERROR();
  }
}


