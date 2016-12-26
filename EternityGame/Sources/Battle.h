#pragma once
#include <vector>
#include <queue>

struct vec2
{
	float x, y;
};

/**************************
* Events
*
**************************/
/*
#define CollisionEvent 1;
#define ProjectileOption 2;
#define ShipOption 3;
#define ControlEvent 4;
*/
enum eventType
{
	CollisionEvent,
	ProjectileOption,
	ShipOption,
	ControlEvent
};

enum ProjectileCommand
{
	destroy,
	hide,
	disable, // side -> 0 No collision
	clearTarget
};

struct tEvent
{
	int eventType;
	__int8 data[60];
};

struct tCollisionCheck
{
	vec2 pos;
	int projectileID;
	int side;
	float dmg;
	int entityID;
	void * pointer;
};

struct tProjectileOption
{
	int projectileID;
	int command;
	int wParam;
	vec2 vecParam;
	int entityID;
	void * pointer;
};

enum eAttr
{
	shieldmod,
	hullmod,
	engmod,
	energymod
};

struct tAttribute
{
	eAttr attr;
	int valueInt1;
	int valueInt2;
	float valueFloat1;
	float valueFloat2;
};


enum ModuleType
{
	none,
	main,
	sys,
	weapon,
	extra
};

enum ModuleSize
{
	szTiny,
	szSmall,
	szMeduim,
	szLarge,
	szHuge
};

enum LockoutType
{
	front,
	wide,
};

class Projectile
{
public:
	vec2 vec;
	vec2 pos;
	float speed;
	int side;
	int ownerID;
	int entityID;
	float dmg;
	void draw();
	void setTexture(unsigned int tex);
	void move(double deltatime);
	~Projectile();
private:
	unsigned int texture;
};

class Module
{
public:
	char name[32];
	float health;
	float energyConsumption;
	bool bActive;
	int entityID;
	int size; // module size (small - medium - large - huge)
			  //virtual	int reg(Ship * target);
	virtual void update(double deltatime);
	ModuleType type;
	Module();
	~Module();
private:

};

class SysModule : public Module
{
public:
	bool bAttrActive;
	void update(double deltatime) override;
	bool addAttribute(tAttribute attribute);
	bool cutAttribute(int ID);
	SysModule();
	tAttribute nAttr[8];
	int attrCount;
};

class WepModule : public Module
{
public:
	float wepCooldown;
	float wepCurrentCd;
	float delayDuration;
	float SeekTargetAngle;
	bool bCooldown;
	void init(float Cooldown, LockoutType type, Projectile exProjectile);
	void update(double deltatime) override;
	bool shoot(Projectile * newProjectile, vec2 rotation);
	//	int reg(Ship * target);
	WepModule();
	~WepModule();
private:

	LockoutType lType;
	Projectile mProjectile;
};

class cShipSystem
{
public:

	void addModule(Module * newModule);
	void update(double deltatime);
	bool activateWeapon(int wepID, vec2 rotate, Projectile * newProjectile);
	float totalCapacity;
	float totalConsumption;
	float freeEnergy;
	std::vector<Module *> mArray;
	std::vector<ModuleSize> sArray;
	std::vector<int> wepArray;
};

class Ship
{
public:
	/* Physical parameters */
	vec2 pos;
	float speed;
	float size;
	/* Game parameters */
	cShipSystem ShipSystem;
	char name[32]; // Unit name;
	int Entityid;
	int side; // 0 = Player; 1 = Enemy;

	float hull;
	float hullMax;
	float hullRegen;
	float shield;
	float shieldMax;
	float shieldRegen;

	float evasion;
	float speedMax;
	float acceleration;

	bool bshield;

	/* Methods */
	void draw();
	void setTexture(unsigned int tex);
	void weaponUse(int WeaponID, vec2 pos);
	void setStats(const char* shipName, float nhull, float nshield, float nspeed, float nsize, unsigned int ntex);
	void takeDmg(float dmg, int owner);
	void updStats(double deltatime);
	Ship();
	~Ship();
private:
	unsigned int texture;
};

class Battle
{
public:
	bool initBattle();
	void update(double deltatime);
	void addShip(Ship target);
	void addProjectile(Projectile target);
	void command(Ship * target);
	Ship* getControl(int ID);
	Battle();
	~Battle();
private:
	int projectilesTop;
	int shipsTop;
	std::vector<Ship * > units;
	std::vector<Projectile * > projectiles;
	std::queue<tEvent> list;
	void handleEvent(tEvent ev);
};

float sqtDist(vec2 a, vec2 b);