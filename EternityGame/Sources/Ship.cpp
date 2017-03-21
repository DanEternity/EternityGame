#include "Ship.h"
#include <Graphics.h>

tShip::tShip()
{
	strcpy_s(name, "ShipName");
	movement = { 0, 0 };
	pos = { 0, 0 };
	direction = { 0, -1 };
	PhysicalSize = 1;

	baseHull = 1;
	baseHullReg = 0;
	baseShield = 0;
	baseShieldReg = 0;
	baseSpeed = 0;
	baseEvade = 0;
	baseBattery = 0;

	hull = 1;
	hullReg = 0;
	hullMax = 1;
	shield = 0;
	shieldReg = 0;
	shieldMax = 0;
	speed = 0;
	evade = 0;

	powerCapacity = 0;
	powerUsage = 0;
	powerBattery = 0;
}

tShip::~tShip()
{
}

void tShip::setStats(float bHull, float bHullReg, float bShield, float bShieldReg, float bSpeed, float bEvade, float bPhysicalSize)
{
	baseHull = bHull;
	baseHullReg = bHullReg;
	hull = bHull;
	baseShield = bShield;
	baseShieldReg = bShieldReg;
	baseSpeed = bSpeed;
	baseEvade = bEvade;
	PhysicalSize = bPhysicalSize;
}

void tShip::setName(const char * newName)
{
	strcpy_s(name, newName);
}

void tShip::setTexture(unsigned int tex)
{
	shipTexture = tex;
}

void tShip::setSize(int sizeShipX, int sizeShipY)
{
	sizeX = sizeShipX;
	sizeY = sizeShipY;
}

void tShip::setPowerBattery(float count)
{
	powerBattery = count;
}

void tShip::setPosition(vec2 newPosition)
{
	pos = newPosition;
}

void tShip::setMovement(vec2 newMove)
{
	float mod = sqrt(newMove.x * newMove.x + newMove.y * newMove.y);
	if (mod == 0)
	{
		movement = { 0, 0 };
		return;
	}
	movement.x = newMove.x / mod;
	movement.y = newMove.y / mod;
}

int tShip::addModule(ModuleType type)
{
	int id = 0;
	switch (type)
	{
	case none:
		break;
	case core:
		break;
	case sys:
		tModule.push_back(new SysModule());
		id = tModule.size()-1;
		break;
	case wep:
		tModule.push_back(new WepModule());
		id = tModule.size() - 1;
		tWep.push_back(id);
		break;
	default:
		break;
	}
	return id;
}

int tShip::addAttrToModule(int id, Attribute Attr)
{
	SysModule * pick = (SysModule*)tModule[id];
	pick->addAtribute(Attr.type, Attr.count);
	return pick->attrN;
}

int tShip::tekeDamage(DamageInfo info)
{
	hull -= info.Count;
	return 0;
}

WeaponModuleInfo tShip::getWeaponInfo(int id)
{
	WepModule * pick = (WepModule*)tModule[tWep[id]];
	return pick->Info;
}

int tShip::setWeaponCooldown(int id, float newCd)
{
	WepModule * pick = (WepModule *)tModule[tWep[id]];
	if (newCd == -1)
		pick->currentCooldown = pick->baseCooldown;
	else
		pick->currentCooldown = newCd;
	return 0;
}

int tShip::useWeapon(WeaponModuleInfo * info, int id)
{
	WepModule * pick = (WepModule*)tModule[tWep[id]];
	if (!pick->bCooldown)
	{
		WeaponModuleInfo * buff = &pick->Info;
		memcpy(info, buff, sizeof(WeaponModuleInfo));
		pick->bCooldown = true;
		pick->currentCooldown = pick->baseCooldown;
		return 0;
	}
	else return -1; // FAILED!
}

int tShip::setWeaponStats(WeaponModuleInfo info, float cooldown, int id)
{
	WepModule * pick = (WepModule *)tModule[id];
	pick->Info = info;
	pick->currentCooldown = 0;
	pick->baseCooldown = cooldown;
	pick->bCooldown = false;
	return 0;
}

void tShip::updStats(double deltatime)
{
	hullReg = baseHullReg;
	shieldReg = baseShieldReg;
	hullMax = baseHull;
	shieldMax = baseShield;
	speed = baseSpeed;
	evade = baseEvade;
	powerBatteryMax = baseBattery;
	for (int i = 0; i < tModule.size(); i++)
	{
		if (tModule[i]->type == wep)
		{
			WepModule*pick = (WepModule*)tModule[i];
			if (pick->bCooldown)
			{
				pick->currentCooldown -= deltatime;
				if (pick->currentCooldown < 0)
					pick->bCooldown = false;
			}
		}
		if (tModule[i]->type == sys)
		{
			SysModule*pick = (SysModule*)tModule[i];
			for (int k = 0; k < pick->attrN; k++)
			{
				switch (pick->mAttr[k].type)
				{
				case tHull:
				{
					hullMax = +pick->mAttr[k].count;
					break;
				}
				case tShield:
				{
					shieldMax = +pick->mAttr[k].count;
					break;
				}
				case tReghp:
				{
					hullReg = +pick->mAttr[k].count;
					break;
				}
				case tRegshield:
				{
					shieldReg = +pick->mAttr[k].count;;
					break;
				}
				case tSpeed:
				{
					speed = +pick->mAttr[k].count;;
					break;
				}
				case tPowerBattery:
				{
					powerBatteryMax = +pick->mAttr[k].count;;
					break;
				}
				case tEvade:
				{
					evade = +pick->mAttr[k].count;;
					break;
				}

				default:
					break;
				}
			}
		}

	}
}


void tShip::Draw()
{
	DrawSprite2v(shipTexture, sizeX, sizeY, pos.x, pos.y);
}
