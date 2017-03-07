#include "UI.h"
#include<Graphics.h>
#include<Battle.h>
#include<Globals.h>
/*
void DrawShipUI(Ship * target, unsigned int tex)
{
	int offset = 0;
	DrawSprite2v(tex, wndWidth - gameFrameW, wndWidth, (wndWidth - gameFrameW) / 2 + gameFrameW, wndHeight / 2);
	for (int i(0); i < target->ShipSystem.mArray.size(); i++)
		switch (target->ShipSystem.mArray[i]->type)
		{
		case main:
			break;
		case sys:
			DrawSysModuleUI((SysModule *)target->ShipSystem.mArray[i], &offset);
			break;
		case weapon:
			DrawWepModuleUI((WepModule *)target->ShipSystem.mArray[i], &offset);
			break;
		case extra:
			break;
		default:
			offset += 40;
			break; 
		}
}

void DrawSysModuleUI(SysModule * target, int * offs)
{
	tFont * Font = (tFont *)pFont;
	DrawSprite2v(texModHover, wndWidth - gameFrameW, 60, (wndWidth - gameFrameW) / 2 + gameFrameW, 40 + *offs);
	Font->outText((wndWidth - gameFrameW) / 2 + gameFrameW - 80, *offs + 30, target->name);
	*offs += 40;
}

void DrawWepModuleUI(WepModule * target, int * offs)
{
	tFont * Font = (tFont *)pFont;
	DrawSprite2v(texModHover, wndWidth - gameFrameW, 60, (wndWidth - gameFrameW) / 2 + gameFrameW, 40 + *offs);
	Font->outText((wndWidth - gameFrameW) / 2 + gameFrameW - 80, *offs + 30, target->name);
	char c[20];
	_itoa_s(target->wepCurrentCd * 1000, c , 10);
	Font->outText((wndWidth - gameFrameW) / 2 + gameFrameW - 80, *offs + 50, "Cooldown:");
	Font->outText((wndWidth - gameFrameW) / 2 + gameFrameW + 10, *offs + 50, c);
	*offs += 80;
}
*/

bool UIElement::isInside(int mouseX, int mouseY)
{
	if ((mouseX >= pos.x) || (mouseX <= pos.x + size.x) && (mouseY >= pos.y) || (mouseY <= pos.y + size.y))
		return true;
	else 
	{
		return false;
	}
}

UIElement::UIElement()
{
	pos.x = 0;
	pos.y = 0;
	size.x = 0;
	size.y = 0;
}

UIElement::~UIElement()
{
}

int UIGrid::isInsideCell(int mouseX, int mouseY)
{
	for (int i = 0; i < countX ; i++)
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

void UISmartGrid::remove(int id)
{
	for (int i(0); i < cells.size(); i++)
	{
		if (cells[i].id == id)
		{
			cells.erase(cells.begin() + i);
		}
	}
}

void UISmartGrid::add(cell newCell)
{
	cells.push_back(newCell);
}

int UISmartGrid::isInsideCell2(int mouseX, int mouseY)
{
	for (int i(0); i < cells.size(); i++)
	{
		cells[i].pos.x;
		cells[i].pos.y;
		cells[i].size.x;
		cells[i].size.y;
		if ((mouseX >= x + cells[i].pos.x) || (mouseX <= x + cells[i].pos.x + +cells[i].size.x) && (mouseY >= y + cells[i].pos.y) || (mouseY >= y + cells[i].pos.y + cells[i].size.y))
		{
			return cells[i].id;
		}		
	}
	return -1;
}

UISmartGrid::UISmartGrid()
{
}

UISmartGrid::~UISmartGrid()
{
}
