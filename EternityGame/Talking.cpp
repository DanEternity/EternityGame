#include "Talking.h"


void Talking::fileRead(char s[])
{
	std::ifstream ins(s);
	if (!ins.is_open()) // если файл не открыт
		Font->outText(70, 70, "Файл не может быть открыт!");
	else
	{
		std::string qq;
		while (!ins.eof())
		{
			std::getline(ins,qq);
			//ins.getline(qq, 255);
			if (conclusion(qq.c_str())==1)
			{ }
		}
		ins.close();
	}
}

int Talking::conclusion(const char s[])
{
	float px, py;
	GetScale(103, 45, 128, 128, px, py);
	DrawSprite3v(texturegray,size.x,size.y,pos.x,pos.y);
	if (strlen(s)>100)
	{ }
	Font->outText(70,70,s);

	DrawSprite3v(texbt_001, 103*px, 43*py, size.x + pos.x+25 - 103 * px, pos.y + size.y);
	Font->outText(size.x + pos.x + 25 - 103 * px + 50, pos.y + size.y + 25, "next");
	DrawSprite3v(texbt_001, 103*px, 43*py, size.x + pos.x+25 - 3*103 * px, pos.y+size.y);
	Font->outText(size.x + pos.x + 25 - 3 * 103 * px + 50, pos.y + size.y + 25, "skip");
	return  0; //isInsideCell2(xPos - 5, yPos + 3);
}
void Talking::setFont(tFont * pick)
{
	Font = pick;
}

Talking::Talking()
{
	pos.x = 50;
	pos.y = 50;
	size.x = 1000;
	size.y = 100;

	float px, py;
	GetScale(103, 45, 128, 128, px, py);
	int id = 0;
	cell buff;
	buff.pos = { size.x + pos.x + 25 - 103 * px, pos.y + size.y };
	buff.id = id;
	buff.size = { 103 * px, 43 * py };
	//add(buff);
	id++;
	buff.pos = { size.x + pos.x + 25 - 3*103 * px , pos.y + size.y };
	buff.id = id;
	buff.size = { 103 * px, 43 * py };
	//add(buff);
	id++;
}


Talking::~Talking()
{
}
