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
	for (auto it(units.begin()); it != units.end(); it++)
	{
		tShip* pick = (tShip*)it->second;
		vec2 dSpeed;
		dSpeed.x = pick->speed * pick->movement.x * deltatime + pick->pos.x;
		dSpeed.y = pick->speed * pick->movement.y * deltatime + pick->pos.y;
		pick->setPosition(dSpeed);
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
