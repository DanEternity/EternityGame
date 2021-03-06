#include <Globals.h>
#include <windows.h>
#include <vector>
#include <Types.h>

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
BOOL keyPress[0xffff];
BOOL keyBlock[0xffff];

/**************************
* Options
*
**************************/

int wndHeight = 720;
int wndWidth = 1280;
int gameFrameH = 720;
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
std::vector<textureStorage> texture;
int gameStatus = -1;

unsigned int targetTextureMap = 0;
int targetTextureMapSizeX = 0;
int targetTextureMapSizeY = 0;

bool mouseClickR = false;
bool mouseClickL = false;
bool mouseClickM = false;

bool mouseClickBlockR = false;
bool mouseClickBlockL = false;
bool mouseClickBlockM = false;

bool mouseDownR = false;
bool mouseDownL = false;
bool mouseDownM = false;

/**************************
* Other
*
**************************/

float theta = 0.0f;
int x = 400, y = 400;
int listSize = 0;
int mouseX = 0, mouseY = 0;
int xPos = 0, yPos = 0;
int SelectedItemId = -1;
bool lMouseBotton = false;
char lastChar = '0';
float shipX = 0, shipY = 0;