#pragma once
#include <Types.h>
#include <Battle.h>
#include <Ship.h>
#include <vector>
#include <gl/gl.h>
#include <Player.h>

class tBaseAdventure;
	

class tBaseObject
{
public:
	vec2 pos;
	ObjectType type;

	float rotate;
	float rotateSpeed;


	float size;
	int id;
	float texSize;
	ModelInfo sprite;

	tBaseObject();
};

struct tZoneContext
{
	tBaseAdventure * pAdv;
	tBattle * pBattle;
	PlayerEnviroment * pEnv;
	int attribute1;
	int attribute2;
	int * attributeArray;
	void * pCustomStruct;
};

class tZone
{
public:
	/* Base info */
	int level;
	int difficult;

	/* Script info */

	ScriptResult(*EnterFunction)(tZoneContext * Context);		
	ScriptResult(*ProcessFunction)(tZoneContext * Context, tfEvent fEvent);
	ScriptResult(*EndFunction)(tZoneContext * Context);

	tZoneContext context;
	tZone();
};

class tBaseAdventure
{
public:

	vec2 camera;
	vec2 cameraMoveVector;
	float cameraSpeed;

	float fAngle;
	vec2 fCenter;
	float ScrollingSpeed;

	std::vector<tBaseObject*> ObjectMap;
	std::vector<tZone*> Zones;

	ModelInfo tile;
	float tileSize;

	/* additional */
	int activeZoneId;
	ScriptResult lastScriptResult;

	/* end */
	void SetCamera(float angle);
	void ResetCamera();
	void Update(double deltatime);
	void SetCameraMove(vec2 movement);
	void Draw();
	bool EnterZone(tBaseAdventure * pAdventure, tBattle * pBattle, PlayerEnviroment * pEnviroment);
	bool ProcessZone(tfEvent eventType);

	int AddBaseObject();
	int AddZone(int objectId);
	tBaseAdventure();
};

