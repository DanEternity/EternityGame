#include "Battle.h"
#include <Graphics.h>

void Ship::draw()
{
	DrawSprite(texture, size, pos.x, pos.y);
}

void Ship::setTexture(unsigned int tex)
{
	texture = tex;
}

void Ship::weaponUse(int WeaponID)
{
}

void Ship::setStats(const char * shipName, float nhull, float nshield, float nspeed, float nsize, unsigned int ntex)
{
	for (int i(0); i < strlen(shipName); i++)
		name[i] = shipName[i];
	hull = nhull;
	shield = nshield;
	speed = nspeed;
	size = nsize;
	setTexture(ntex);
}

void Ship::takeDmg(float dmg, int owner)
{
	/* damage should be logged */
	if (bshield)
	{
		shield -= dmg;
		if (shield <= 0)
		{
			dmg = -shield;
			bshield = false;
			hull -= dmg;
		}
	}
	else
		hull -= dmg;
	/*
	if (hull <= 0)
		~ship;
	*/
}

Ship::Ship()
{
}

Ship::~Ship()
{
}

void Projectile::draw()
{
	DrawSprite(texture, 8, pos.x, pos.y);
}

void Projectile::setTexture(unsigned int tex)
{
	texture = tex;
}

void Projectile::move(double deltatime)
{
	pos.x += vec.x * deltatime * speed;
	pos.y += vec.y * deltatime * speed;
}

void Battle::update(double deltatime)
{
	int i = 0;
	while(i < projectiles.size())
	{
		/*
		tCollisionCheck vTask;
		vTask.owner = projectiles[i].owner;
		vTask.projectileID = i;
		vTask.type = CollisionEvent;
		vTask.pos = projectiles[i].pos;
		list.push((tEvent)vTask);
		*/

		projectiles[i].move(deltatime);

		bool hit = false;
		int j = 0;
		while(j < units.size())
		{
			if (projectiles[i].ownerID != units[j].Entityid && sqtDist(projectiles[i].pos, units[j].pos) < units[j].size*units[j].size)
			{
				hit = true;
				units[j].takeDmg(projectiles[i].dmg, projectiles[i].ownerID);
				break;
			}
			j++;
		}
		if (hit || projectiles[i].vec.x > 2000 || projectiles[i].vec.y > 2000 || projectiles[i].vec.x < -200 || projectiles[i].vec.y < -200)
		{
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
		i++;
	}
	for (int i(0); i < units.size(); i++)
		units[i].draw();
	for (int i(0); i < projectiles.size(); i++)
		projectiles[i].draw();
}

void Battle::addShip(Ship target)
{
	units.push_back(target);
}

void Battle::addProjectile(Projectile target)
{
	projectiles.push_back(target);
}

Ship * Battle::getControl(int ID)
{
	return &units[ID];
}

Battle::Battle()
{
}

Battle::~Battle()
{
}

float sqtDist(vec2 a, vec2 b)
{
	return (a.x - b.x)*(a.x - b.x)+(a.y - b.y)*(a.y - b.y);
}
