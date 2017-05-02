#pragma once
#include<Types.h>
#include<Battle.h>
#include<Ship.h>
#include<vector>
#include <gl/gl.h>


class tBaseObject
{
public:
	vec2 pos;

	float rotate;
	float rotateSpeed;


	float size;
	int id;
	float texSize;
	ModelInfo sprite;

	tBaseObject();
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

	ModelInfo tile;
	float tileSize;

	void SetCamera(float angle);
	void ResetCamera();
	void Update(double deltatime);
	void SetCameraMove(vec2 movement);
	void Draw();
	int AddBaseObject();
};
