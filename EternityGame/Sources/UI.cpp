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
	if ((mouseX >= pos.x) && (mouseX <= pos.x + size.x) && (mouseY >= pos.y) && (mouseY <= pos.y + size.y))
		return true;
	else 
		return false;
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
		if ( ((mouseX >=cells[i].pos.x) && (mouseX <=cells[i].pos.x + cells[i].size.x)) && ((mouseY >=cells[i].pos.y) && (mouseY <=cells[i].pos.y + cells[i].size.y)) )
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

int UIGrid::isInsideCell(int mouseX, int mouseY)
{
	
		for (int i = 0; i < countX; i++)
		{
			for (int j = 0; j < countY; j++)
			{
				if ((mouseX >= x + (j + 1)*diff.x + j*size.x) && (mouseX <= x + (j + 1)*diff.x + (j + 1)*size.x) && (mouseY >= y + (j + 1)*diff.y + j*size.y) && (mouseY <= y + (j + 1)*diff.y + (j + 1)*size.y))
				{
					return i * 5 + j;
				}
			}
		}
		return -1;
	
}

int DrawModule::init(int id)
{
	vec2 size, pos;
	float deltaY = 15, deltaX = 5, delX = 4, delY = 4;
	size.x = 64;
	size.y = 64;
	cell buff;
	buff.pos = { 180, 320 - deltaY };
	buff.id = id;
	buff.size = { size.x, size.y };
	add(buff);
	id++;
	buff.pos = { 360 - deltaX, 190 - deltaY };
	buff.id = id;
	buff.size = { size.x, size.y };
	add(buff);
	id++;
	buff.pos = { 360 - deltaX, 480 - deltaY - 5 };
	buff.id = id;
	buff.size = { size.x, size.y - delY };
	add(buff);
	id++;
	buff.pos = { 560 - deltaX, 215 - deltaY };
	buff.id = id;
	buff.size = { size.x, size.y };
	add(buff);
	id++;
	buff.pos = { 560 - deltaX, 460 - deltaY - 5 };
	buff.id = id;
	buff.size = { size.x, size.y - delY };
	add(buff);
	id++;
	buff.pos = { 740 - deltaX, 245 - deltaY };
	buff.id = id;
	buff.size = { size.x, size.y };
	add(buff);
	id++;
	buff.pos = { 740 - deltaX, 425 - deltaY - 5 };
	buff.id = id;
	buff.size = { size.x, size.y - delY };
	add(buff);
	id++;
	buff.pos = { 770, 615 };//7
	buff.id = id;
	buff.size = { 103,43 };
	add(buff);
	id++;
	buff.pos = {950, 615 };
	buff.id = id;
	buff.size = { 103,43 };
	add(buff);
	id++;

	return 0;
}

void DrawModule::setFont(tFont * pick)
{
	Font = pick;
}

void DrawModule::drawModule()
{
	float px, py;

	GetScale(103, 45, 128, 128, px, py);
	for (int i(0); i < cells.size(); i++)	
		DrawSprite3v(texbt_004, cells[i].size.x, cells[i].size.y, cells[i].pos.x, cells[i].pos.y);
	
	if (isInsideCell2(xPos, yPos) != -1)	
		DrawSprite3v(texbt_005, cells[isInsideCell2(xPos, yPos)].size.x, cells[isInsideCell2(xPos, yPos)].size.y, cells[isInsideCell2(xPos, yPos)].pos.x, cells[isInsideCell2(xPos, yPos)].pos.y);

	Font->outInt(1050, 30, mouseX);
	Font->outInt(1050, 50, mouseY);
	Font->outInt(1050, 100, xPos);
	Font->outInt(1050, 130, yPos);
	Font->outInt(200, 100, isInsideCell2(xPos - 5, yPos + 3));
}

void DrawModule::drawShip()
{	
	DrawSprite3v(shipui, 1024, 1024, 0, 100);	
}

void DrawModule::drawGui()
{
	//0,580 1064,730
}

void DrawModule::drawHp(tShip* pick)
{
	
	const int x = 150;
	const int y = 100;
	DrawSprite3v(texturegray, 200, 150, x-20, y-20);
	Font->outText(x, y, "HP");
	Font->outInt(x+130, y, pick->baseHull);
	Font->outText(x+160, y, "/");
	Font->outInt(x+165, y, pick->hullMax);

	Font->outText(x, y+20, "SHIELD");
	Font->outInt(x+130, y+20, pick->baseShield);
	Font->outText(x+160, y+20, "/");
	Font->outInt(x+165, y+20, pick->shieldMax);

	Font->outText(x, y+80, "SPEED");
//	Font->outInt(x+130, y+40, pick->baseSpeed);
//	Font->outText(x+160, y+40, "/");
	Font->outInt(x+130, y+80, pick->speed);

	Font->outText(x, y+60, "EVASION");
//	Font->outInt(x+130, y+60, pick->baseEvade);
//	Font->outText(x+160, y+60, "/");
	Font->outInt(x+130, y+60, pick->evade);

	Font->outText(x, y+40, "BATTERY");
	Font->outInt(x+130, y+40, pick->powerBattery);	
	Font->outText(x+160, y+40, "/");
	Font->outInt(x+165, y+40, pick->powerBatteryMax);

}

int DrawModule::checkNumb()
{
	float px, py;
	GetScale(103, 45, 128, 128, px, py);
	int a;
	DrawSprite3v(texbt_001, cells[7].size.x*px, cells[7].size.y*py, cells[7].pos.x, cells[7].pos.y);
	Font->outText(cells[7].pos.x + 30, cells[7].pos.y + 20, "menu");

	DrawSprite3v(texbt_001, cells[8].size.x*px, cells[8].size.y*py, cells[8].pos.x, cells[8].pos.y);
	Font->outText(cells[8].pos.x + 30, cells[8].pos.y + 20, "exit");

	switch (isInsideCell2(xPos - 5, yPos + 3))
	{
	case 7:
		a = btSelect[0];
		break;
	case 8:
		a = btSelect[1];
		break;
	default:
		a = btSelect[2];
	}
	return a;
}



/*void DrawModule::setFont(tFont * pick)
{
	Font = pick;
}*/

DrawModule::DrawModule()
{
}

DrawModule::~DrawModule()
{
}

int UIStore::GetCellOnMouse(int x, int y)
{
	return isInsideCell2(x, y);
}

int UIStore::DrawStore()
{
	DrawSprite3v(texBack_001, bgSize.x, bgSize.y, pos.x-5, pos.y-5);
	AssignTextureMap(texMap, 32, 32);
	for (int i(0); i < cells.size(); i++)
	{
		DrawSprite4v(cells[i].size.x, cells[i].additional, cells[i].pos.x, cells[i].pos.y);
		if (selectedId == cells[i].id)
			DrawSprite4v(cells[i].size.x, 33, cells[i].pos.x, cells[i].pos.y);
	}	
	return 0;
}

int UIStore::DrawLine(int first, int last)
{
	DrawSprite3v(texBack_001, bgSizeSmall.x, bgSizeSmall.y, pos.x - 5, pos.y - 5);
	AssignTextureMap(texMap, 32, 32);
	for (int i(first); i < cells.size() && i <= last; i++)
	{
		DrawSprite4v(cells[i].size.x, cells[i].additional, cells[i].pos.x, cells[i].pos.y);
		if (selectedId == cells[i].id)
			DrawSprite4v(cells[i].size.x, 33, cells[i].pos.x, cells[i].pos.y);
	}
	return 0;
}

void UIStore::setPosition(vec2 newPos)
{
	for (int i(0); i < cells.size(); i++)
	{
		cells[i].pos.x = cells[i].pos.x - pos.x + newPos.x;
		cells[i].pos.y = cells[i].pos.y - pos.y + newPos.y;
	}
	pos = newPos;
}

void UIStore::createGrid(int height, int width, int diff, vec2 size)
{
	int id = 0;
	for (int i(0); i<height; i++)
		for (int j(0); j < width; j++)
		{
			cell temp;
			temp.size = size;
			temp.pos.x = (size.x + diff)*j+pos.x;
			temp.pos.y = (size.y + diff)*i+pos.y;
			temp.id = id++;
			temp.additional = 32;
			add(temp);
		}
}

UIStore::UIStore()
{
	bgSize = { 0, 0 };
	bgSizeSmall = { 0, 0 };
	selectedId = -1;
}

UIStore::~UIStore()
{
}

void SimpleButton::Draw()
{
	DrawSprite3v(texture, size.x, size.y, pos.x, pos.y);
}

void SimpleButton::SetTexture(unsigned int tex)
{
	texture = tex;
}

bool SimpleButton::onClick(int mouseX, int mouseY)
{
	if (isInside(mouseX, mouseY))
	{
		if (funcPointer == NULL)
			return TRUE;
		else
			return funcPointer(&mouseX, &mouseY);
	}
	else
		return false;
}

SimpleButton::SimpleButton()
{
	funcPointer = NULL;
}

SimpleButton::SimpleButton(bool(*functionPointer)(int *, int *))
{
	funcPointer = functionPointer;
}
