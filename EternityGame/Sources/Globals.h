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
extern BOOL keyPress[0xffff];
extern BOOL keyBlock[0xffff];

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
extern char lastChar;

const float vdiv = 0.707106781f; // sqrt(2)/2

#define M_E        2.71828182845904523536   // e
#define M_LOG2E    1.44269504088896340736   // log2(e)
#define M_LOG10E   0.434294481903251827651  // log10(e)
#define M_LN2      0.693147180559945309417  // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4
#define M_1_PI     0.318309886183790671538  // 1/pi
#define M_2_PI     0.636619772367581343076  // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)

/* Keys  */

#define mKey_I	73