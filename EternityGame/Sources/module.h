#pragma once
#include<Types.h>

class Module
{
public:
	char name[20];
	float hp;
	float hpmax;
	bool active;
	int id;
	float energyUsage;

	Module();
	~Module();
};

class SysModule : public Module
{
public:
	Attribute mAttr[8];
	int attrN;
	void addAtribute(tAttribute type, float count);
	SysModule();
	~SysModule();
};

class WepModule : public Module
{
public:
	float range;
	float damage;
	float cooldown;
	WepModule();
	~WepModule();
};