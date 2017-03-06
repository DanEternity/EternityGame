#pragma once

struct vec2
{
	float x, y;
};

/**************************
* Events
*
**************************/
/*
#define CollisionEvent 1;
#define ProjectileOption 2;
#define ShipOption 3;
#define ControlEvent 4;
*/
enum eventType
{
	CollisionEvent,
	ProjectileOption,
	ShipOption,
	ControlEvent
};

enum ProjectileCommand
{
	destroy,
	hide,
	disable, // side -> 0 No collision
	clearTarget
};

struct tEvent
{
	int eventType;
	__int8 data[60];
};

struct tCollisionCheck
{
	vec2 pos;
	int projectileID;
	int side;
	float dmg;
	int entityID;
	void * pointer;
};

struct tProjectileOption
{
	int projectileID;
	int command;
	int wParam;
	vec2 vecParam;
	int entityID;
	void * pointer;
};

enum tAttribute
{
	tHull,
	tShield,
	tReghp,
	tRegshield,
	tSpeed,
	tPowerBattery,
	tEvade
};
struct Attribute
{
	tAttribute type;
	float count;
};

enum ModuleType
{
	none,
	core,
	sys,
	wep
};

struct ShipBaseStats
{
	char name[32];
	float baseHull;
	float baseHullReg;
	float baseShield;
	float baseShieldReg;
	float baseSpeed;
	float baseEvade;
	float baseBattery;
	unsigned int texture;
	int sizeX, sizeY;
};

struct ShootBaseStats
{
	vec2 pos;
	vec2 movement;
	int ownerId;
	float speed;
	float damage;
	unsigned int texture;
};