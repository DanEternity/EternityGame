#pragma once;

#include<Types.h>
#include<map>
#include<Ship.h>
#include<Projectile.h>
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
	int setShipPosition(vec2 pos, int id);
	int setShipMovement(vec2 pos, int id);
	int setShootStats(ShootBaseStats buff, int id);
	int setShootPosition(vec2 pos, int id);
	int setShootMovement(vec2 pos, int id);
	int addShipModule(ModuleType type, int id);
	int addAttrToModule(Attribute attr, int shipId, int moduleId);
	WeaponModuleInfo getWeaponInfo(int shipId, int weaponId);
	int setWeaponCooldown(float newCooldown, int shipId, int weaponId); // newCooldown = -1 to use standart weapon cd;
	int useWeapon(int shipId, int weaponId);
};

inline float DistSqr(vec2 p1, vec2 p2);