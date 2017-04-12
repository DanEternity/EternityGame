#pragma once

#include<Graphics.h>
#include<Battle.h>
#include<Globals.h>
#include <Types.h>
#include <Vector>
#include <windows.h>
#include<module.h>
#include<ship.h>
/*
void DrawShipUI(Ship * target, unsigned int tex);
void DrawSysModuleUI(SysModule * target, int * offs);
void DrawWepModuleUI(WepModule * target, int * offs);*/

class UIElement
{
public:
	vec2 pos, size;
	bool isInside(int mouseX, int mouseY);
	UIElement();
	~UIElement();
};
class UIGrid : public UIElement
{
public:
	vec2 sizeCell, diff;
	int countX, countY;
	int isInsideCell(int mouseX, int mouseY);
};

class UISmartGrid : public UIElement
{
public:
	std::vector<cell> cells;

	void remove(int id);
	void add(cell newcell);
	int isInsideCell2(int mouseX, int mouseY);
	UISmartGrid();
	~UISmartGrid();
};

class DrawModule : public UISmartGrid
{
public:
	vec2 size, pos;
	int id;
	int init(int id);
	void setFont(tFont * pick);
	void drawModule();
	void drawShip();
	void drawGui();
	void drawHp(tShip* pick);
	int checkNumb();
	tFont * Font;
	unsigned int texbt_001;
	unsigned int texbt_002;
	unsigned int texbt_004;
	unsigned int texbt_005;
	unsigned int texbt_006;
	unsigned int shipui;
	DrawModule();
	~DrawModule();

};


class UIStore : public UISmartGrid
{
public:
	int selectedId; // SelectedCellId
	/*Textures*/
	GLuint texCell_004;
	GLuint texCell_004s;
	GLuint texBack_001;
	GLuint texMap;
	GLuint texturegray;
	/*textures end*/



	int GetCellOnMouse(int x, int y);
	int DrawStore();
	void setPosition(vec2 newPos);
	void createGrid(int height, int width, int diff, vec2 size);

	UIStore();
	~UIStore();
};
