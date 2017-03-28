#pragma once

#include<Graphics.h>
#include<Battle.h>
#include<Globals.h>
#include <Types.h>
#include <Vector>
#include <windows.h>
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
	void drawModule(int id);
	tFont * Font;
	unsigned int texbt_001;
	void setFont(tFont * pick);
	DrawModule();
	~DrawModule();

};
