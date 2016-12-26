/**************************
* Includes
*
**************************/

#include <windows.h>
#include <gl/gl.h>
#include <Graphics.h>
#include <Globals.h>
#include <Battle.h>
#include <Modules.h>
#include <UI.h>


/**************************
* Function Declarations
*
**************************/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
void Init();
double GetDeltaTime();

/**************************
* WinMain
*
**************************/

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int iCmdShow)
{
	/* register window class */
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Eternity";
	RegisterClass(&wc);

	/* create main window */
	hWnd = CreateWindow(
		"Eternity", "Game",
		WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
		0, 0, wndWidth, wndHeight,
		NULL, NULL, hInstance, NULL);

	/* enable OpenGL for the window */
	EnableOpenGL(hWnd, &hDC, &hRC);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	/* load test resources*/
	glEnable(GL_TEXTURE_2D);							// Enabling Textures
	GLuint MainShip = LoadTex("Resource/EternityTop.tga");
	GLuint BG = LoadTex("Resource/bg.tga");
	GLuint bul = LoadTex("Resource/shoot01.tga");
	GLuint book = LoadTex("Resource/enemy01.tga");
	GLuint UI_001 = LoadTex("Resource/UI_001.tga");
	texModHover = LoadTex("Resource/UI_002.tga");
	tFont Font = tFont("Resource/Font.tga", 32, 256, 32);
	Font.loadOffset("Resource/FontOffset.dat", 256);
	pFont = &Font;
	Battle gMain = Battle::Battle();
	/* init main ship */
	Ship Eternity = Ship::Ship();
	Eternity.setStats("Eternity", 1000, 1000, 5, 128, MainShip);
	Eternity.pos = { 400, 400 };
	Eternity.Entityid = 1;
	Eternity.side = 0;

	WepModule testWep = WepModule();
	SysModule testSysMod = SysModule();
	/* weapon adjust */
	Projectile Shoot;
	Shoot.setTexture(bul);
	Shoot.speed = 240;
	Shoot.dmg = 10;
	Shoot.vec = { 0, -1 };
	Shoot.ownerID = 1;
	Shoot.side = 0;


	gMain.addShip(Eternity);

	/* ship contlor */
	
	/* enemy ship */
	Ship enemytest = Ship::Ship();
	enemytest.setStats("Enemy01", 100, 100, 5, 128, book);
	enemytest.pos = { 400, 200 };
	enemytest.Entityid = 2;
	enemytest.side = 1;
	gMain.addShip(enemytest);

	Ship * PlaerShip = gMain.getControl(1);
	Shoot.ownerID = PlaerShip->Entityid;
	testWep.init(0.4, front, Shoot);
	testWep.type = weapon;
	strcpy_s(testWep.name, "Weapon Module");
	PlaerShip->ShipSystem.addModule(&testWep);
	testSysMod.type = sys;
	strcpy_s(testSysMod.name, "system module");
	PlaerShip->ShipSystem.addModule(&testSysMod);
	Init();
	/* program main loop */
	while (!bQuit)
	{
		/* check for messages */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* handle or dispatch messages */
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			/* Preparing to update */

			deltaTime = GetDeltaTime();

			/* OpenGL animation code goes here */
			

			

			if (keyState[VK_LEFT])
				x--;
			if (keyState[VK_RIGHT])
				x++;
			if (keyState[VK_DOWN])
				y++;
			if (keyState[VK_UP])
				y--;

			if (keyState[VK_SPACE])
			{
				//Shoot.pos = PlaerShip->pos;
				//gMain.addProjectile(Shoot);
				gMain.command(PlaerShip);
			}
			PlaerShip->pos.x = x;
			PlaerShip->pos.y = y;

			StartDraw2D(wndWidth, wndHeight);	

			glBindTexture(GL_TEXTURE_2D, BG);
	
			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 1.0f); 		glVertex2f(0, 0);
			glTexCoord2f(1.0f, 1.0f);		glVertex2f(gameFrameW, 0);
			glTexCoord2f(1.0f, 0.0f); 		glVertex2f(gameFrameW, gameFrameH);
			glTexCoord2f(0.0f, 0.0f); 		glVertex2f(0, gameFrameH);

			glEnd();

			gMain.update(deltaTime);

			char st[10];
			_itoa_s(listSize, st, 10);
			Font.outText(100, 100, st);

			DrawShipUI(PlaerShip, UI_001);

			EndDraw2D();


			SwapBuffers(hDC);
			
		}
	}

	/* shutdown OpenGL */
	DisableOpenGL(hWnd, hDC, hRC);

	/* destroy the window explicitly */
	DestroyWindow(hWnd);

	return msg.wParam;
}


/********************
* Window Procedure
*
********************/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		default:
			keyState[wParam] = TRUE;
		}
		return 0;
	case WM_KEYUP:
		keyState[wParam] = FALSE;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}


/*******************
* Enable OpenGL
*
*******************/

void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	/* get the device context (DC) */
	*hDC = GetDC(hWnd);

	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
	iFormat = ChoosePixelFormat(*hDC, &pfd);
	SetPixelFormat(*hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	*hRC = wglCreateContext(*hDC);
	wglMakeCurrent(*hDC, *hRC);

}


/******************
* Disable OpenGL
*
******************/

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
}

void Init()
{
	oldDeltatime = GetCurrentTime() / 1000; // Set Current Time as start time;
}

double GetDeltaTime()
{
	double Cur = GetCurrentTime();
	double Old = oldDeltatime;
	oldDeltatime = Cur / 1000;
	return Cur / 1000 - Old;
}
