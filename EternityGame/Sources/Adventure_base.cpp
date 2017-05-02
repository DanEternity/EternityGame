#include "Adventure_base.h"
#include "Globals.h"
#include "Graphics.h"

void tBaseAdventure::SetCamera(float angle)
{
	glTranslatef(gameFrameW / 2, gameFrameH / 2, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-gameFrameW / 2, -gameFrameH / 2, 0);

	fAngle = angle;

}

void tBaseAdventure::ResetCamera()
{
	glTranslatef(gameFrameW / 2, gameFrameH / 2, 0);
	glRotatef(-fAngle, 0, 0, 1);
	glTranslatef(-gameFrameW / 2, -gameFrameH / 2, 0);
}

void tBaseAdventure::Update(double deltatime)
{
	camera = 
	{ 
		float(camera.x + cameraMoveVector.x * deltatime * cameraSpeed),
		float(camera.y + cameraMoveVector.y * deltatime * cameraSpeed)
	};

	for (int i(0); i < ObjectMap.size(); i++)
	{
		ObjectMap[i]->rotate += ObjectMap[i]->rotateSpeed * deltatime;
	}
}

void tBaseAdventure::SetCameraMove(vec2 movement)
{
	cameraMoveVector = movement;
}

void tBaseAdventure::Draw()
{
	vec2 pDiff = { camera.x, camera.y};
	//vec2 pDiff = { camera.x, camera.y};

	DrawTile1v(tile, tileSize, 0, 4, {camera.x / ScrollingSpeed, -camera.y / ScrollingSpeed }, 400, 200);



	for (int i(0); i < ObjectMap.size(); i++)
	{
	//	DrawSprite3v(ObjectMap[i]->tex, ObjectMap[i]->texSize.x, ObjectMap[i]->texSize.y, ObjectMap[i]->pos.x - pDiff.x, ObjectMap[i]->pos.y - pDiff.y);
		DrawSprite5v(ObjectMap[i]->sprite, ObjectMap[i]->texSize, ObjectMap[i]->rotate, ObjectMap[i]->pos.x - pDiff.x, ObjectMap[i]->pos.y - pDiff.y);
	}
}

int tBaseAdventure::AddBaseObject()
{
	ObjectMap.push_back(new tBaseObject());
	return ObjectMap.size() - 1;
}

tBaseObject::tBaseObject()
{
}
