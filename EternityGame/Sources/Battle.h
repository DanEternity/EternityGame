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

#define CollisionEvent 0x0001;

struct tEvent
{
	int type;
	__int16 data[16];
};

struct tCollisionCheck
{
	int type;
	vec2 pos;
	int projectileID;
};

class Ship
{
public:
	/* Phisical parameters */
	vec2 pos;
	float speed;
	float size;
	/* Game parameters */
	int Entityid;
	int side; // 0 = Player; 1 = Enemy;
	char name[32]; // Unit name;
	float hull;
	float shield;
	bool bshield;
	/* Methods */
	void draw();
	void setTexture(unsigned int tex);
	void weaponUse(int WeaponID);
	void setStats(const char* shipName, float nhull, float nshield, float nspeed, float nsize, unsigned int ntex);
	void takeDmg(float dmg, int owner);
	Ship();
	~Ship();
private:
	unsigned int texture;
};

class Projectile
{
public:
	vec2 vec;
	vec2 pos;
	float speed;
	int side;
	int ownerID;
	float dmg;
	void draw();
	void setTexture(unsigned int tex);
	void move(double deltatime);
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
	Ship* getControl(int ID);
	Battle();
	~Battle();
private:
	std::vector<Ship> units;
	std::vector<Projectile> projectiles;
	std::queue<tEvent> list;
};

float sqtDist(vec2 a, vec2 b);