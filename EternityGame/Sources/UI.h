#pragma once

#include<Graphics.h>
#include<Battle.h>
#include<Globals.h>
#include <Types.h>
#include <Vector>
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
class UIGrid: public UIElement
{
public:
	vec2 sizeCell, diff;
	int countX, countY;
	int isInsideCell(int mouseX, int mouseY)
	{
		for (int i = 0; i < countX; i++)
		{
			for (int j = 0; j < countY; j++)
			{
				if ((mouseX >= x + (j + 1)*diff.x + j*size.x) || (mouseX <= x + (j + 1)*diff.x + (j + 1)*size.x) && (mouseY >= y + (j + 1)*diff.y + j*size.y) || (mouseY >= y + (j + 1)*diff.y + (j + 1)*size.y))
				{
					return i * 5 + j;
				}
			}
		}
		return -1;
	}
};

class UISmartGrid : public UIElement
{
	std::vector<cell> cells;
	void remove(int id);
	void add(cell newcell);
	int isInsideCell2(int mouseX, int mouseY);
	UISmartGrid();
	~UISmartGrid();
};