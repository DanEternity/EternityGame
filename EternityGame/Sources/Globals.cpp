#include <Globals.h>
#include <windows.h>

/**************************
* WinAPI / OpenGL
*
**************************/

WNDCLASS wc;
HWND hWnd;
HDC hDC;
HGLRC hRC;
MSG msg;
BOOL bQuit = FALSE;
BOOL keyState[0xffff];

/**************************
* Options
*
**************************/

int wndHeight = 768;
int wndWidth = 1280;
int gameFrameH = 768;
int gameFrameW = 1080;

/**************************
* Game / Core
*
**************************/

double deltaTime;
double oldDeltatime;
__int64 tickCount;

void * pFont = nullptr;

/**************************
* Game / Textures
*
**************************/

unsigned int texModHover = 0;

/**************************
* Other
*
**************************/

float theta = 0.0f;
int x = 400, y = 400;
int listSize = 0;