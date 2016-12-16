#pragma once
#include <windows.h>

/**************************
* WinAPI / OpenGL
*
**************************/

extern WNDCLASS wc;
extern HWND hWnd;
extern HDC hDC;
extern HGLRC hRC;
extern MSG msg;
extern BOOL bQuit;
extern BOOL keyState[0xffff];

/**************************
* Options
*
**************************/

extern int wndHeight;
extern int wndWidth;

/**************************
* Game / Core
*
**************************/

extern double deltaTime;
extern double oldDeltatime;

/**************************
* Other
*
**************************/

extern float theta;
extern int x, y;
extern int listSize;