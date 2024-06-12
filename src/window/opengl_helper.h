#ifndef OPENGL_HELPER_H
#define OPENGL_HELPER_H

#include <windows.h>

typedef HGLRC WINAPI wglCreateContextAttribsARB_t(HDC hdc, HGLRC hSharedContext, const int *attribList);
extern wglCreateContextAttribsARB_t *wglCreateContextAttribsARB;

/// @name Context attributes
/// @{
#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
/// @}

/// @name Context attributes values
/// @{
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001
/// @}

/// @brief See [khronos registry](https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt).
typedef BOOL WINAPI wglChoosePixelFormatARB_t(HDC hdc, const int *piAttribIList, const float *pfAttribFList,
                                              unsigned int nMaxFormats, int *piFormats, unsigned int *nNumFormats);
/// @brief Pointer for retrieved function.
extern wglChoosePixelFormatARB_t *wglChoosePixelFormatARB;

/// @{ @name Pixel format attributes
#define WGL_DRAW_TO_WINDOW_ARB     0x2001
#define WGL_ACCELERATION_ARB       0x2003
#define WGL_SUPPORT_OPENGL_ARB     0x2010
#define WGL_DOUBLE_BUFFER_ARB      0x2011
#define WGL_PIXEL_TYPE_ARB         0x2013
#define WGL_COLOR_BITS_ARB         0x2014
#define WGL_DEPTH_BITS_ARB         0x2022
#define WGL_STENCIL_BITS_ARB       0x2023
/// @}
/// @{ @name Pixel format attribute values
#define WGL_FULL_ACCELERATION_ARB  0x2027
#define WGL_TYPE_RGBA_ARB          0x202B
///@}

/// @brief Function for retriving openGL function pointer either via wgl or directly from dll.
///
/// For more info go to [khronos wiki](https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#Windows).
void* GetAnyGLFuncAddress(const char *name);
/// @brief Function for initializing openGL context
///
/// For more info go to[khronos wiki](https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)).
///
/// @returns Handle to OpenGL rendering context.
HGLRC InitOpenGLContext(HDC hdc);
/// @brief Wrapper for loading functions with using
/// [glad](https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library#glad_(Multi-Language_GL/GLES/EGL/GLX/WGL_Loader-Generator)).
void LoadOpenGLFunctions(void);

#endif
