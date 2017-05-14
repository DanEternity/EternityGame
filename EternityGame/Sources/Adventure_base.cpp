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

	bool ZoneActive = false;

	for (int i(0); i < ObjectMap.size(); i++)
	{
		ObjectMap[i]->rotate += ObjectMap[i]->rotateSpeed * deltatime;
		if (ObjectMap[i]->type == objectTypepZone)
		{
			//	if (DistSqr({ shipX, shipY }, { ObjectMap[i]->pos.x, ObjectMap[i]->pos.y}) < ObjectMap[i]->size*ObjectMap[i]->size)
			if (DistSqr({ shipX, shipY }, { ObjectMap[i]->pos.x + ObjectMap[i]->size/2, ObjectMap[i]->pos.y + ObjectMap[i]->size/2}) < (ObjectMap[i]->size)*(ObjectMap[i]->size))
			{
				activeZoneId = ObjectMap[i]->id;
				ZoneActive = true;
			}
		}
	}

	if (!ZoneActive)
		activeZoneId = -1;
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

bool tBaseAdventure::EnterZone(tBaseAdventure * pAdventure, tBattle * pBattle, PlayerEnviroment * pEnviroment)
{
	if (activeZoneId != -1 && Zones[activeZoneId]->EnterFunction != NULL)
	{
		Zones[activeZoneId]->context.pAdv = pAdventure;
		Zones[activeZoneId]->context.pBattle = pBattle;
		Zones[activeZoneId]->context.pEnv = pEnviroment;

		ScriptResult sResult = Zones[activeZoneId]->EnterFunction(&Zones[activeZoneId]->context);
		lastScriptResult = sResult;

		if (sResult.success)
			return TRUE;
	}
	return FALSE;
}

bool tBaseAdventure::ProcessZone(tfEvent eventType)
{
	if (activeZoneId != -1 && Zones[activeZoneId]->ProcessFunction != NULL)
	{
		ScriptResult sResult = Zones[activeZoneId]->ProcessFunction(&Zones[activeZoneId]->context, eventType);
		lastScriptResult = sResult;

		if (sResult.success)
			return TRUE;
	}
	return FALSE;
}

int tBaseAdventure::AddBaseObject()
{
	ObjectMap.push_back(new tBaseObject());
	return ObjectMap.size() - 1;
}

int tBaseAdventure::AddZone(int objectId)
{
	Zones.push_back(new tZone());
	ObjectMap[objectId]->id = Zones.size() - 1;

	return Zones.size() - 1;
}

tBaseAdventure::tBaseAdventure()
{
	activeZoneId = -1;
}

tBaseObject::tBaseObject()
{
	type = objectTypeNone;
}

tZone::tZone()
{
	EnterFunction = NULL;
	ProcessFunction = NULL;
	EndFunction = NULL;
}
