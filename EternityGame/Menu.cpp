#include "Menu.h"
#include <Graphics.h>

int Botton::drawBotton(int id)
{
	DrawSprite2v(texbt_001, 200, 93, pos.x + 70, pos.y + 25 + size.y*id);
	Font->outText(pos.x, pos.y, "Eternity");
	cell buff;
	buff.pos = { pos.x-35, pos.y-50 };
	buff.id = 0;	
	buff.size = { size.x, size.y + size.y*id};
	add(buff);
	id++;
	DrawSprite2v(texbt_001, 200, 93, pos.x + 70, pos.y + 25 + size.y*id);
	Font->outText(pos.x, pos.y + size.y, "start");
	buff.pos = { pos.x - 35, pos.y - 50 + size.y*id };
	buff.id = 1;
	buff.size = { size.x, size.y};
	add(buff);
	id++;
	DrawSprite2v(texbt_001, 200, 93, pos.x + 70, pos.y + 25 + size.y*id);
	Font->outText(pos.x, pos.y + size.y + size.y, "setting");
	buff.pos = { pos.x - 35, pos.y - 50 + size.y*id };
	buff.id = 2;
	buff.size = { size.x, size.y };
	add(buff);
	id++; 
	DrawSprite2v(texbt_001, 200, 93, pos.x + 70, pos.y + 25 + size.y*id);
	Font->outText(pos.x,pos.y + size.y + size.y + size.y, "others");
	buff.pos = { pos.x - 35, pos.y - 50 + size.y*id };
	buff.id = 3;
	buff.size = { size.x, size.y};
	add(buff);
	id++; 
	DrawSprite2v(texbt_001, 200, 93, pos.x + 70, pos.y + 25 + size.y*id);
	Font->outText(pos.x, pos.y + size.y + size.y + size.y + size.y, "exit");
	buff.pos = { pos.x - 35, pos.y - 50 + size.y*id };
	buff.id = 4;
	buff.size = { size.x, size.y };
	add(buff);
	id++;
	//Font->outInt(200, 100, isInsideCell2(mouseX, mouseY));
	//DrawSprite2v(texbt_001, 200, 180, pos.x+70, pos.y+60);
	Font->outInt(1050, 30, mouseX);
	Font->outInt(1050, 50, mouseY);
	Font->outInt(1050, 100, xPos);
	Font->outInt(1050, 130, yPos);
	Font->outInt(200, 100, isInsideCell2(xPos, yPos));
	return isInsideCell2(xPos, yPos);
}

void Botton::setFont(tFont * pick)
{
	Font = pick; 
}

Botton::Botton()
{
	pos.x = 500;
	pos.y = 400;
	size.x = 75;
	size.y = 35;
	id = 0;
}

Botton::~Botton()
{
}
