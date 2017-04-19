#include "Talking.h"


void Talking::fileRead(char s[])
{
	int k=-1;

	std::ifstream ins(s);
	init(0);
	if (!ins.is_open()) // если файл не открыт
		Font->outText(70, 70, "Файл не может быть открыт!");
	else
	{
		std::string qq;
		while (!ins.eof())
		{

		}


			/*strings.push_back(qq);
			//if (conclusion(qq.c_str()) == 1)
			{
				std::getline(ins, qq);
				k = 1;
			}
			if (conclusion(qq.c_str()) == 0)
				k = 0;

			//std::getline(ins, qq);
			//ins.getline(qq, 255);

		}*/
		ins.close();
	}
}

void Talking::check(UISmartGrid * UISG)
{
	tUISmartGrid = UISG;

}

int Talking::init(int id)
{
	float px, py;
	GetScale(103, 45, 128, 128, px, py);
	cell buff;
	buff.pos = { size.x + pos.x + 25 - 103 * px, pos.y + size.y };
	buff.id = id;
	buff.size = { 103 * px, 43 * py };
	tUISmartGrid->add(buff);
	id++;
	buff.pos = { size.x + pos.x + 25 - 3 * 103 * px , pos.y + size.y };
	buff.id = id;
	buff.size = { 103 * px, 43 * py };
	tUISmartGrid->add(buff);
	id++;

	return 0;
}

int Talking::conclusion(std::string s[])
{
	float px, py;
	GetScale(103, 45, 128, 128, px, py);
	DrawSprite3v(texturegray,size.x,size.y,pos.x,pos.y);

	//Font->outText(70,70,s);

	DrawSprite3v(texbt_001, 103*px, 43*py, size.x + pos.x+25 - 103 * px, pos.y + size.y);
	Font->outText(size.x + pos.x + 25 - 103 * px + 50, pos.y + size.y + 25, "next");
	DrawSprite3v(texbt_001, 103*px, 43*py, size.x + pos.x+25 - 3*103 * px, pos.y+size.y);
	Font->outText(size.x + pos.x + 25 - 3 * 103 * px + 50, pos.y + size.y + 25, "skip");
	/*switch (tUISmartGrid->isInsideCell2(xPos - 5, yPos + 3))
	{
	case 0:
		Font->outInt(1000, 200, tUISmartGrid->isInsideCell2(xPos - 5, yPos + 3));
		break;
	case 1:
		Font->outInt(1000, 300, tUISmartGrid->isInsideCell2(xPos - 5, yPos + 3));
		break;
	default:
		break;
	}

	//Font->outInt(1000, 200, tUISmartGrid->isInsideCell2(xPos - 5, yPos + 3));
	//return isInsideCell2(xPos - 5, yPos + 3);*/
	//Font->outInt(1000, 200, tUISmartGrid->isInsideCell2(xPos - 5, yPos + 3));
	return tUISmartGrid->isInsideCell2(xPos - 5, yPos + 3);
}
void Talking::setFont(tFont * pick)
{
	Font = pick;
}

Talking::Talking()
{
	int id = 0;
	pos.x = 50;
	pos.y = 50;
	size.x = 1000;
	size.y = 100;

	
}


Talking::~Talking()
{
}
