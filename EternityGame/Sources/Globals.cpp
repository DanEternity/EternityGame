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

int wndHeight = 600;
int wndWidth = 800;

/**************************
* Game / Core
*
**************************/

double deltaTime;
double oldDeltatime;

/**************************
* Other
*
**************************/

float theta = 0.0f;
int x = 400, y = 400;
int listSize = 0;