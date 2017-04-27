#pragma once
#include<Types.h>
#include<Battle.h>
#include<Ship.h>
#include<vector>


class tBaseObject
{
public:
	vec2 pos;
	float size;
	int id;
	unsigned int tex;
	vec2 texSize;
};


class tBaseAdventure
{
public:
	vec2 camera;

	std::vector<tBaseObject*> ObjectMap;


	void Draw();
};
