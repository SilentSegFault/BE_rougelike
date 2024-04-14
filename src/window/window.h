/// @file
#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

/// @brief See [khronos registry](https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt).
typedef HGLRC WINAPI wglCreateContextAttribsARB_t(HDC hdc, HGLRC hSharedContext, const int *attribList);
/// @brief Pointer for retrieved function.
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

/// Callback function typedef for window resize event.
///
/// @param hwnd Handle to resized window.
/// @param newWidth Width that window was resized to.
/// @param newHeight Height that widnow was resized to.
typedef void WindowSizing(HWND hwnd, int newWidth, int newHeight);

/// @brief Window procedure for handling window messages.
///
/// For more info go to [Microsoft docs](https://learn.microsoft.com/en-us/windows/win32/winmsg/window-procedures).
LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam);
/// @brief Function for retriving openGL function pointer either via wgl or directly from dll.
///
/// For more info go to [khronos wiki](https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#Windows).
void* GetAnyGLFuncAddress(const char *name);
/// @brief Function responsible for creating main window of application.
///
/// It also sets correct styles for openGL window and handles converting window size to client area size 
/// For more see [Microsoft docs](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-adjustwindowrect).
///
/// @param[in] title Title of window.
/// @param[in] width Width of client area.
/// @param[in] height Height of client area.
/// @returns Handle to window.
HWND CreateMainWindow(const char *title, int width, int height);
/// @brief Function for initializing openGL context
///
/// For more info go to[khronos wiki](https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)).
///
/// @returns Handle to OpenGL rendering context.
HGLRC InitOpenGLContext(HDC hdc);
/// @brief Wrapper for loading functions with using
/// [glad](https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library#glad_(Multi-Language_GL/GLES/EGL/GLX/WGL_Loader-Generator)).
void LoadOpenGLFunctions(void);
/// @brief Function for polling window events from message queue.
///
/// @param[out] bWindowShouldClose Returns if window received WM_QUIT message.
void PollEvents(BOOL *bWindowShouldClose);
/// @brief Sets callback for WM_SIZING and WM_SIZE message.
///
/// @param[in] callback Pointer to function which will be called when WM_SIZING or WM_SIZE messages are received.
void SetWindowSizingCallback(WindowSizing *callback);

extern unsigned int windowWidth; ///< Current width of window.
extern unsigned int windowHeight; ///< Current height of window.

#endif
