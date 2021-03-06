#include "Battle.h"
#include "globals.h"

tBattle::tBattle()
{
	unitsMax = 0;
	shootsMax = 0;
}

tBattle::~tBattle()
{
}

void tBattle::DrawAll()
{
	for (auto it(units.begin()); it != units.end(); it++)
	{
		tShip* pick = (tShip*)it->second;
		pick->Draw();
	}
	for (auto it(shoots.begin()); it != shoots.end(); it++)
	{
		tProjectile* pick = (tProjectile*)it->second;
		pick->draw();
	}
}

int tBattle::addShip()
{
	int pick;
	if (unitsQ.empty())
	{
		unitsMax++;
		units[unitsMax] = new tShip();
		pick = unitsMax;
	}
	else
	{
		pick = unitsQ.front();
		unitsQ.pop();
		units[pick] = new tShip();
	}
	return pick;
}

int tBattle::eraseShip(int id)
{
	units.erase(id);
	unitsQ.push(id);
	return 0;
}

int tBattle::addShoot()
{
	int pick;
	if (shootsQ.empty())
	{
		shootsMax++;
		shoots[shootsMax] = new tProjectile();
		pick = shootsMax;
	}
	else
	{
		pick = shootsQ.front();
		shootsQ.pop();
		shoots[pick] = new tProjectile();
	}
	return pick;
}

int tBattle::eraseShoot(int id)
{
	shoots.erase(id);
	shootsQ.push(id);
	return 0;
}

void tBattle::update(double deltatime)
{
	for (auto it(units.begin()); it != units.end(); it++) // Ship Events
	{
		tShip* pick = (tShip*)(it->second);
		vec2 dSpeed;
		pick->updStats(deltatime);
		dSpeed.x = pick->speed * pick->movement.x * deltatime + pick->pos.x;
		dSpeed.y = pick->speed * pick->movement.y * deltatime + pick->pos.y;
		pick->setPosition(dSpeed);
		if (pick->hull < 0)
		{
 			eraseShip(it->first);
			if (it._Myproxy == NULL)
				break;
		}
	}

	for (auto it(shoots.begin()); it != shoots.end(); it++) // Projectile Events
	{
		tProjectile* pick = (tProjectile*)(it->second);
		vec2 dSpeed;
		dSpeed.x = pick->speed * pick->movement.x * deltatime + pick->pos.x;
		dSpeed.y = pick->speed * pick->movement.y * deltatime + pick->pos.y;
		pick->setPosition(dSpeed);
		bool delShoot = false;
		if (DistSqr(pick->pos, { (float)gameFrameW / 2, (float)gameFrameW / 2 }) < 8000000)
		{
			for (auto trg(units.begin()); trg != units.end(); trg++) // Collision
			{
				tShip * target = (tShip*)(trg->second);
				if ((DistSqr(target->pos, pick->pos) < (target->PhysicalSize)*(target->PhysicalSize)) && (target->id != pick->ownerId))
				{
					// Make damage
					target->tekeDamage({ pick->damage, kinetic, pick->ownerId });
					delShoot = true;
					break;
				}
			}
		}
		else
			delShoot = true;
		if (delShoot)
		{
			eraseShoot(it->first);
			if (it._Myproxy == NULL)
				break;
		}
	}


}

int tBattle::setShipStats(ShipBaseStats buff, int id)
{
	tShip* pick = (tShip*)units[id];
	pick->setName(buff.name);
	pick->setStats(buff.baseHull, buff.baseHullReg, buff.baseShield, buff.baseShieldReg, buff.baseSpeed, buff.baseEvade, buff.phisicalSize);
	pick->setSize(buff.sizeX, buff.sizeY);
	pick->setTexture(buff.texture);
	return 0;
}

int tBattle::setShipPosition(vec2 pos, int id)
{
	tShip * pick = (tShip*)units[id];
	pick->setPosition(pos);
	return 0;
}

int tBattle::setShipMovement(vec2 pos, int id)
{
	tShip * pick = (tShip*)units[id];
	pick->setMovement(pos);
	return 0;
}

int tBattle::setShootStats(ShootBaseStats buff, int id)
{
	tProjectile * pick = (tProjectile*)shoots[id];
	pick->setStats(buff);
	return 0;
}

int tBattle::setShootPosition(vec2 pos, int id)
{
	tProjectile * pick = (tProjectile*)shoots[id];
	pick->setPosition(pos);
	return 0;
}

int tBattle::setShootMovement(vec2 pos, int id)
{
	tProjectile * pick = (tProjectile*)shoots[id];
	pick->setMove(pos);
	return 0;
}

int tBattle::addShipModule(ModuleType type, int id)
{
	tShip * pick = (tShip*)units[id];
	return pick->addModule(type); 
}

int tBattle::addAttrToModule(Attribute attr, int shipId, int moduleId)
{
	tShip * pick = (tShip*)units[shipId];
	pick->addAttrToModule(moduleId, attr);
	return 0;
}

WeaponModuleInfo tBattle::getWeaponInfo(int shipId, int weaponId)
{
	tShip * pick = (tShip *)units[shipId];
	return pick->getWeaponInfo(weaponId);
}

int tBattle::setWeaponCooldown(float newCooldown, int shipId, int weaponId)
{
	tShip * pick = (tShip*)units[shipId];
	pick->setWeaponCooldown(weaponId, newCooldown);
	return 0;
}

int tBattle::useWeapon(int shipId, int weaponId)
{
	tShip * pick = (tShip*)units[shipId];
	WeaponModuleInfo info;
	if (pick->useWeapon(&info, weaponId) == 0)
	{
		int id;
		switch (info.style)
		{
		case bullet:
			id = addShoot();
			setShootStats({
				pick->pos,
				pick->direction,
				shipId,
				info.speed,
				info.damage,
				info.texture },
				id);

			return 0;
		default:
			break;
		}


	}
	else return -1; // FAILED!
}

int tBattle::setWeaponStats(WeaponModuleInfo info, float cooldown, int shipId, int moduleId)
{
	tShip * pick = (tShip *)units[shipId];
	pick->setWeaponStats(info, cooldown, moduleId);
	return 0;
}

inline float DistSqr(vec2 p1, vec2 p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}
