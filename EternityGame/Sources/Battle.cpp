#include "Battle.h"

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
}

int tBattle::addShip()
{
	int pick;
	if (units.empty())
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
	if (shoots.empty())
	{
		shootsMax++;
		//shoots[shootsMax] = new tProjectile();
		pick = shootsMax;
	}
	else
	{
		pick = shootsQ.front();
		shootsQ.pop();
		shoots[pick] = new tShip();
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
		pick->updStats();
		dSpeed.x = pick->speed * pick->movement.x * deltatime + pick->pos.x;
		dSpeed.y = pick->speed * pick->movement.y * deltatime + pick->pos.y;
		pick->setPosition(dSpeed);
	}

	for (auto it(shoots.begin()); it != shoots.end(); it++) // Projectile Events
	{

	}
}

int tBattle::setShipStats(ShipBaseStats buff, int id)
{
	tShip* pick = (tShip*)units[id];
	pick->setName(buff.name);
	pick->setStats(buff.baseHull, buff.baseHullReg, buff.baseShield, buff.baseShieldReg, buff.baseSpeed, buff.baseEvade);
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
