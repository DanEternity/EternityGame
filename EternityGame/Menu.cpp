#include "Menu.h"
#include <Graphics.h>

void Botton::drawBotton(int id)
{

	Font->outText(pos.x, pos.y, "Eternity");
	cell buff;
	buff.pos = { pos.x-30, pos.y-35 };
	buff.id = 0;	
	buff.size = { size.x, size.y + size.y*id};
	add(buff);
	id++;
	Font->outText(pos.x, pos.y + size.y, "start");
	buff.pos = { pos.x - 30, pos.y - 35 + size.y*id };
	buff.id = 1;
	buff.size = { size.x, size.y};
	add(buff);
	id++;
	Font->outText(pos.x, pos.y + size.y + size.y, "setting");
	buff.pos = { pos.x - 30, pos.y - 35 + size.y*id };
	buff.id = 2;
	buff.size = { size.x, size.y };
	add(buff);
	id++; 
	Font->outText(pos.x,pos.y + size.y + size.y + size.y, "others");
	buff.pos = { pos.x - 30, pos.y - 35 + size.y*id };
	buff.id = 3;
	buff.size = { size.x, size.y};
	add(buff);
	id++; 
	Font->outText(pos.x, pos.y + size.y + size.y + size.y + size.y, "exit");
	buff.pos = { pos.x - 30, pos.y - 35 + size.y*id };
	buff.id = 4;
	buff.size = { size.x, size.y };
	add(buff);
	id++;
	//Font->outInt(200, 100, isInsideCell2(mouseX, mouseY));
	Font->outInt(1050, 30, mouseX);
	Font->outInt(1050, 50, mouseY);
	Font->outInt(1050, 100, xPos);
	Font->outInt(1050, 130, yPos);
	if (lMouseBotton)
		Font->outInt(200, 100, isInsideCell2(xPos, yPos));
}

void Botton::setFont(tFont * pick)
{
	Font = pick; 
}

Botton::Botton()
{
	pos.x = 500;
	pos.y = 400;
	size.x = 55;
	size.y = 45;
	id = 0;
}

Botton::~Botton()
{
}
