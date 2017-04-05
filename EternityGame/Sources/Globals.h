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
extern int gameFrameH;
extern int gameFrameW;

/**************************
* Game / Core
*
**************************/

extern double deltaTime;
extern double oldDeltatime;
extern __int64 tickCount;

extern void * pFont;

/**************************
* Game / Textures
*
**************************/

extern unsigned int texModHover;
extern int gameStatus;

extern unsigned int  targetTextureMap;
extern int targetTextureMapSizeX;
extern int targetTextureMapSizeY;

extern bool mouseClickR;
extern bool mouseClickL;
extern bool mouseClickM;

extern bool mouseClickBlockR;
extern bool mouseClickBlockL;
extern bool mouseClickBlockM;

extern bool mouseDownR;
extern bool mouseDownL;
extern bool mouseDownM;

/**************************
* Other
*
**************************/

extern float theta;
extern int x, y;
extern int listSize;
extern int mouseX, mouseY;
extern int xPos, yPos;
extern bool lMouseBotton;
extern int SelectedItemId;

const float vdiv = 0.707106781f; // sqrt(2)/2