#include "module.h"
#include"Types.h"
#include <iostream>
Module::Module()
{
	hp = 0;
	hpmax = 0;
	active = false;
	id = 0;
	energyUsage = 0;
	strcpy_s(name,"");
	type = none;

}

Module::~Module()
{
}

void SysModule::addAtribute(tAttribute type, float count)
{
	if (attrN == 8)
	{
		return;
	}
	mAttr[attrN].type = type;
	mAttr[attrN++].count = count;
	

}

SysModule::SysModule()
{
	attrN = 0;
	type = sys;
}

SysModule::~SysModule()
{
}

WepModule::WepModule()
{
	range = 0;
	damage = 0;
	cooldown = 0;
	type = wep;
}

WepModule::~WepModule()
{
}
