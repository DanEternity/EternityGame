#include "Menu.h"
#include <Graphics.h>

int Botton::init(int id)
{
	for (int i(0); i < 5; i++)
	{
		cell buff;
		buff.pos = { pos.x, pos.y + 45*i };
		buff.id = i;
		buff.size = { 103,43 };
		add(buff);
	}


	return 0;
}

int Botton::drawBotton()
{
	float px, py;
	GetScale(103, 45, 128, 128, px, py);
	for (int i(0); i < cells.size(); i++)	
		DrawSprite3v(texbt_001, cells[i].size.x*px, cells[i].size.y*py, cells[i].pos.x, cells[i].pos.y);	

	Font->outText(cells[0].pos.x + 30, cells[0].pos.y + 20, "Eternity");
	Font->outText(cells[1].pos.x + 35, cells[1].pos.y + 20, "start");
	Font->outText(cells[2].pos.x + 30, cells[2].pos.y + 20, "setting");
	Font->outText(cells[3].pos.x + 35, cells[3].pos.y + 20, "others");
	Font->outText(cells[4].pos.x + 30, cells[4].pos.y + 20, "exit");

	Font->outInt(1050, 30, mouseX);
	Font->outInt(1050, 50, mouseY);
	Font->outInt(1050, 100, xPos);
	Font->outInt(1050, 130, yPos);
	Font->outInt(200, 100, isInsideCell2(xPos-2, yPos+3));
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
	float px, py;
	GetScale(103, 45, 128, 128, px, py);
	size.x = 103*px;
	size.y = 45*py;
	id = 0;
}

Botton::~Botton()
{
}
