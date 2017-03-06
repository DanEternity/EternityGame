#pragma once

#include<Types.h>
#include<Vector>
#include<gl/gl.h>
#include<module.h>

class tShip
{
public:
	// ShipName and Id
	char name[32];
	int id; // ship index; need in battle to identify ship by index;
	// Position
	vec2 pos;
	vec2 movement;

	// Base stats
	float baseHull;
	float baseHullReg;
	float baseShield;
	float baseShieldReg;
	float baseSpeed;
	float baseEvade;
	float baseBattery;
	// Complete statss
	float hull;
	float hullReg;
	float hullMax;
	float shield;
	float shieldReg;
	float shieldMax;
	float speed;
	float evade;

	// Modules
	std::vector <Module *> tModule;
	std::vector<int> tWep; // weapon indexes
	float powerCapacity;
	float powerUsage;
	float powerBattery;
	float powerBatteryMax;

	// Graphics
	unsigned int shipTexture;
	int sizeX, sizeY; // horizontal; vectical

	tShip();
	~tShip();
	void setStats(float bHull, float bHullReg, float bShield, float bShieldReg, float bSpeed, float bEvade);
	void setName(const char * newName);
	void setTexture(unsigned int tex);
	void setSize(int sizeShipX, int sizeShipY);
	void setPowerBattery(float count);
	void setPosition(vec2 newPosition);
	void setMovement(vec2 newMove);
	int addModule(ModuleType type);
	int addAttrToModule(int id, Attribute Attr);
	void updStats();
	void Draw();
};