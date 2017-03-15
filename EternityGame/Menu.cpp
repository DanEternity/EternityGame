#include "Menu.h"
#include <Graphics.h>



void Botton::drawBotton(int id)
{
	bool f;
	Font->outText(pos.x, pos.y, "Eternity");
	id++;
	Font->outText(pos.x, pos.y + size.y, "start");
	id++;
	Font->outText(pos.x, pos.y + size.y + size.y, "setting");
	id++; 
	Font->outText(pos.x,pos.y + size.y + size.y + size.y, "qq");
	id++; 
	Font->outText(pos.x, pos.y + size.y + size.y + size.y + size.y, "exit");
	id++;
	Font->outInt(100, 100, isInsideCell(mouseX, mouseY));
}

void Botton::setFont(tFont * pick)
{
	Font = pick; 
}

Botton::Botton()
{
	pos.x = 500;
	pos.y = 400;
	size.x = 50;
	size.y = 50;
	id = 0;
}

Botton::~Botton()
{
}
