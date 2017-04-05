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

void WepModule::setWeaponModuleInfo(WeaponModuleInfo newInfo)
{
	Info = newInfo;
}

WepModule::WepModule()
{
	baseCooldown = 0;
	currentCooldown = 0;
	bCooldown = false;
	memset(&Info, 0, sizeof(Info));
	type = wep;
}

WepModule::~WepModule()
{
}
