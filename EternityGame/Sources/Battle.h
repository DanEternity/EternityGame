#pragma once;

#include<Types.h>
#include<map>
#include<Ship.h>
#include<queue>

class tBattle
{
protected:

	int unitsMax, shootsMax;
	std::queue<int> unitsQ, shootsQ;
	std::map<int, void*> units, shoots;
public:
	tBattle();
	~tBattle();
	void DrawAll();
	int addShip();
	int eraseShip(int id);
	int addShoot();
	int eraseShoot(int id);
	void update(double deltatime);
	int setShipStats(ShipBaseStats buff, int id);
};

