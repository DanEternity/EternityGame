#include "Adventure_base.h"
#include "Globals.h"
#include "Graphics.h"

void tBaseAdventure::Draw()
{
	vec2 pDiff = { camera.x - wndWidth / 2, camera.y - wndHeight / 2};
	for (int i(0); i < ObjectMap.size(); i++)
	{
		DrawSprite3v(ObjectMap[i]->tex, ObjectMap[i]->texSize.x, ObjectMap[i]->texSize.y, ObjectMap[i]->pos.x - pDiff.x, ObjectMap[i]->pos.y - pDiff.y);
	}
}
