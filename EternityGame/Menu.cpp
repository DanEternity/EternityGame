#include "Menu.h"
#include <Graphics.h>


void Botton::drawBotton(int id)
{
	Font->outText(100, 100, "Eternity");
	Font->outText(pos.x, pos.y, "start");
	id++;
	Font->outText(pos.x+size.x, pos.y + size.y, "setting");
	id++; 
	Font->outText(pos.x + size.x + size.x,pos.y + size.y + size.y, "qq");
	id++; 
	Font->outText(pos.x + size.x + size.x + size.x, pos.y + size.y + size.y + size.y, "exit");
	id++;
}

void Botton::setFont(tFont * pick)
{
	Font = pick; 
}

Botton::Botton()
{
	pos.x = 0;
	pos.y = 0;
	size.x = 0;
	size.y = 0;
	id = 0;
}

Botton::~Botton()
{
}
