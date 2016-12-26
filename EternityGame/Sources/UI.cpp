#include "UI.h"
#include<Graphics.h>
#include<Battle.h>
#include<Globals.h>

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
