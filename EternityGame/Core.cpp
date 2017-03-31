/**************************
* Includes
*
**************************/

#include <windows.h>
#include <gl/gl.h>

#include <Graphics.h>
#include <Globals.h>
#include <Battle.h>
#include <Player.h>
#include <UI.h>
#include <Menu.h>


/**************************
* Function Declarations
*
**************************/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
void Init();
void InitDebug();
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
	GLuint bt_001 = LoadTex("Resource/bt_001.tga");
	GLuint bt_002 = LoadTex("Resource/bt_002.tga");
	GLuint bt_004 = LoadTex("Resource/cell_002.tga");
	GLuint bt_005 = LoadTex("Resource/cell_002s.tga");
	GLuint shipui = LoadTex("Resource/shipui.tga");
	GLuint textureCell_004 = LoadTex("Resource/cell_004.tga");
	GLuint textureCell_004s = LoadTex("Resource/cell_004s.tga");
	GLuint textureScreen_001 = LoadTex("Resource/window_back.tga");
	GLuint textureCellHoverBlue = LoadTex("Resource/cell_hower_blue.tga");
	GLuint textureItemMap = LoadTex("Resource/textureMap.tga");

	texModHover = LoadTex("Resource/UI_002.tga");
	tFont Font = tFont("Resource/Font.tga", 32, 256, 32);
	Font.loadOffset("Resource/FontOffset.dat", 256);
	pFont = &Font;

	Init();

	/*Init test version*/
	tBattle * battle = new tBattle();
	PlayerHandle * player = new PlayerHandle();
	player->setBattle(battle);
	player->shipIndex = battle->addShip();

	battle->setShipStats({ "Test Ship",100,1,0,0,50,0,100, MainShip, 64, 64}, player->shipIndex);
	battle->setShipPosition({ 400, 300 }, player->shipIndex);

	int id = player->addModule(sys);
	player->addAttrToModule(id, { tHull, 100 });
	id = player->addModule(wep);
	player->setWeaponStats(id, { 0.7f, 230, 40, 600, bullet, bul });

	id = battle->addShip();
	battle->setShipStats({ "Meteorite", 100, 0, 0, 0, 1, 0, 1, book, 80, 80, 40 }, id);
	battle->setShipPosition({ 300, 100 }, id);

	id = battle->addShip();
	battle->setShipStats({ "Meteorite", 100, 0, 0, 0, 1, 0, 1, book, 80, 80, 40 }, id);
	battle->setShipPosition({ 400, 150 }, id);

	id = battle->addShip();
	battle->setShipStats({ "Meteorite", 100, 0, 0, 0, 1, 0, 1, book, 80, 80, 40 }, id);
	battle->setShipPosition({ 720, 400 }, id);

	id = battle->addShip();
	battle->setShipStats({ "Meteorite", 300, 0, 0, 0, 1, 0, 1, book, 160, 160, 60 }, id);
	battle->setShipPosition({ 620, 300 }, id);


	PrimaryStore * store = new PrimaryStore(40);
	UIStore * UIComponentStore = new UIStore();
	store->setUIStore(UIComponentStore);
	UIComponentStore->texCell_004 = textureCell_004;
	UIComponentStore->texCell_004s = textureCell_004s;
	UIComponentStore->texBack_001 = textureScreen_001;
	UIComponentStore->texMap = textureItemMap;
	UIComponentStore->createGrid(5, 8, 4, { 64, 64 });
	UIComponentStore->setPosition({ 350, 75 });

	store->addItem(1, resource);
	store->configItem(1, 10, 32, "Iron");

	Botton * bott = new Botton();
	bott->setFont(&Font);
	bott->texbt_001 = bt_001;

	DrawModule * drmod = new DrawModule();

	drmod->setFont(&Font);
	drmod->texbt_001 = bt_001;
	drmod->texbt_002 = bt_002;
	drmod->texbt_004 = bt_004;
	drmod->texbt_005 = bt_005;
	drmod->texbt_006 = UI_001; 	
	drmod->shipui = shipui;

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

			vec2 movement = { 0, 0 };

			if (keyState[VK_LEFT])
			{
				movement.x -= 1;
			}
			if (keyState[VK_RIGHT])
			{
				movement.x += 1;
			}
			if (keyState[VK_DOWN])
			{
				movement.y += 1;
			}
			if (keyState[VK_UP])
				movement.y -= 1;

			player->setShipMovement(movement);

			if (keyState[VK_SPACE])
			{
				player->useWeapon(0);
			}

			/* OpenGL animation code goes here */	

			StartDraw2D(wndWidth, wndHeight);	

			glBindTexture(GL_TEXTURE_2D, BG);
	
			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 1.0f); 		glVertex2f(0, 0);
			glTexCoord2f(1.0f, 1.0f);		glVertex2f(gameFrameW, 0);
			glTexCoord2f(1.0f, 0.0f); 		glVertex2f(gameFrameW, gameFrameH);
			glTexCoord2f(0.0f, 0.0f); 		glVertex2f(0, gameFrameH);

			glEnd();
			//bott->drawBotton(0);
			switch (gameStatus)
			{
				case -1: 	
					//bott->drawBotton(0);
					gameStatus = bott->drawBotton(0);
					break;
				
				case 1: 
					drmod->drawShip();
					drmod->drawModule(0);
					//gameStatus = bott->drawBotton(0);
					

					
					break;
				case 2:
					store->selectItem(xPos, yPos);
					UIComponentStore->DrawStore();

					SelectedItemId = UIComponentStore->selectedId;
					Font.outInt(40, 65, SelectedItemId);

					break;
				case 4: 
					bQuit = true;
					break;
				default:
					gameStatus = -1;
			}
			tickCount++;
			Font.outInt(40, 40, tickCount);

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
	case WM_RBUTTONDOWN:
	{
		POINT pt;
		TCHAR textBuffer[32];
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		xPos = pt.x*1.02f;
		yPos = pt.y*1.05f;
		lMouseBotton = true;
	}
	case WM_RBUTTONUP:
		lMouseBotton = false;
	case WM_LBUTTONDOWN:
	{
		POINT pt;
		TCHAR textBuffer[32];
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		xPos = pt.x*1.02f;
		yPos = pt.y*1.05f;
		lMouseBotton = true;
	}
	case WM_LBUTTONUP:
		lMouseBotton = false;
	case WM_MOUSEMOVE:
	{
		POINT pt;
		TCHAR textBuffer[32];
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		mouseX = pt.x*1.02f;
		mouseY = pt.y*1.05f;
	}
	break;

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
