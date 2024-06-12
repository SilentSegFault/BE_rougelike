#ifndef WIN32_HELPER_H
#define WIN32_HELPER_H

#include <windows.h>
#include <winuser.h>
#include "window.h"

extern int mouseX;
extern int mouseY;

typedef void WindowSizing(HWND hwnd, int newWidth, int newHeight);

LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam);

HWND CreateMainWindow(const char *title, int width, int height);

void SetWindowSizingCallback(WindowSizing *callback);

void PollEvents(BOOL *bWindowShouldClose);

typedef enum
{
  KEY_NONE  = -1,
  KEY_MOUSELEFT = VK_LBUTTON,
  KEY_MOUSERIGHT = VK_RBUTTON,
  KEY_MOUSEMIDDLE = VK_MBUTTON,

  KEY_BACKSPACE = VK_BACK,
  KEY_TAB = VK_TAB,
  KEY_ENTER = VK_RETURN,
  KEY_LSHIFT = VK_LSHIFT,
  KEY_RSHIFT = VK_RSHIFT,
  KEY_LCTRL = VK_LCONTROL,
  KEY_RCTRL = VK_RCONTROL,
  KEY_LALT = VK_LMENU,
  KEY_RALT = VK_RMENU,
  KEY_CAPS = VK_CAPITAL,
  KEY_ESC = VK_ESCAPE,
  KEY_SPACE = VK_SPACE,
  KEY_PAGEUP = VK_PRIOR,
  KEY_PAGEDOWN = VK_NEXT,
  
  KEY_ARROW_LEFT = VK_LEFT,
  KEY_ARROW_RIGTH = VK_RIGHT,
  KEY_ARROW_UP = VK_UP,
  KEY_ARROW_DOWN = VK_DOWN,

  KEY_0 = 0x30,
  KEY_1 = 0x31,
  KEY_2 = 0x32,
  KEY_3 = 0x33,
  KEY_4 = 0x34,
  KEY_5 = 0x35,
  KEY_6 = 0x36,
  KEY_7 = 0x37,
  KEY_8 = 0x38,
  KEY_9 = 0x39,

  KEY_A = 0x41,
  KEY_B = 0x42,
  KEY_C = 0x43,
  KEY_D = 0x44,
  KEY_E = 0x45,
  KEY_F = 0x46,
  KEY_G = 0x47,
  KEY_H = 0x48,
  KEY_I = 0x49,
  KEY_J = 0x4A,
  KEY_K = 0x4B,
  KEY_L = 0x4C,
  KEY_M = 0x4D,
  KEY_N = 0x4E,
  KEY_O = 0x4F,
  KEY_P = 0x50,
  KEY_Q = 0x51,
  KEY_R = 0x52,
  KEY_S = 0x53,
  KEY_T = 0x54,
  KEY_U = 0x55,
  KEY_V = 0x56,
  KEY_W = 0x57,
  KEY_X = 0x58,
  KEY_Y = 0x59,
  KEY_Z = 0x5A,

  KEY_F1 = VK_F1,
  KEY_F2 = VK_F2,
  KEY_F3 = VK_F3,
  KEY_F4 = VK_F4,
  KEY_F5 = VK_F5,
  KEY_F6 = VK_F6,
  KEY_F7 = VK_F7,
  KEY_F8 = VK_F8,
  KEY_F9 = VK_F9,
  KEY_F10 = VK_F10,
  KEY_F11 = VK_F11,
  KEY_F12 = VK_F12,
} Key;

BOOL KeyPressed(Key key);

BOOL KeyDown(Key key);

#endif
