#include "Battle.h"
#include <Graphics.h>
#include <globals.h>

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

Projectile::~Projectile()
{
}

void Battle::update(double deltatime)
{
	/* Projectiles events */
	for (int i(0); i < projectiles.size(); i++)
	{
		projectiles[i]->move(deltatime);
		tCollisionCheck colEvent;
		colEvent.pos = projectiles[i]->pos;
		colEvent.projectileID = projectiles[i]->entityID;
		colEvent.side = projectiles[i]->side;
		colEvent.entityID = projectiles[i]->entityID;
		tEvent ev;
		ev.eventType = CollisionEvent;
		memcpy(&ev.data, &colEvent, sizeof(tCollisionCheck));
		list.push(ev);
	}

	listSize = list.size();

	/*
	int i = 0;
	while(i < projectiles.size())
	{
		projectiles[i].move(deltatime);

		bool hit = false;
		int j = 0;
		while(j < units.size())
		{
			if (projectiles[i].ownerID != units[j].Entityid && sqtDist(projectiles[i].pos, units[j].pos) < (units[j].size/2)*(units[j].size/2))
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
	*/

	while(list.size() > 0)
	{
		tEvent cur = list.front();
		handleEvent(cur);
		list.pop();
	}

	for (int i(0); i < units.size(); i++)
		units[i]->draw();
	for (int i(0); i < projectiles.size(); i++)
		projectiles[i]->draw();
}

void Battle::addShip(Ship target)
{
	Ship * tmp = new Ship;
	memcpy(tmp, &target, sizeof(Ship));
	units.push_back(tmp);
}

void Battle::addProjectile(Projectile target)
{
	Projectile * tmp = new Projectile;
	target.entityID = projectilesTop++;
	memcpy(tmp, &target, sizeof(Projectile));
	projectiles.push_back(tmp);
}

Ship * Battle::getControl(int ID)
{
	for (int i(0); i < units.size(); i++)
		if (units[i]->Entityid == ID)
			return units[i];
	return nullptr;
}

Battle::Battle()
{
	projectilesTop = 1;
	shipsTop = 3;
}

Battle::~Battle()
{
}

void Battle::handleEvent(tEvent ev)
{
	switch (ev.eventType)
	{
	case CollisionEvent:
	{
		tCollisionCheck hEvent;
		memcpy(&hEvent, &ev.data, sizeof(tCollisionCheck));
		bool hit = false;
		for (int i(0); i < units.size(); i++)
			if (units[i]->side != hEvent.side && sqtDist(hEvent.pos, units[i]->pos) < (units[i]->size / 2)*(units[i]->size / 2))
			{
				units[i]->takeDmg(hEvent.dmg, hEvent.projectileID);
				tProjectileOption nEv;
				nEv.command = destroy;
				nEv.projectileID = hEvent.projectileID;
				nEv.wParam = units[i]->Entityid;
				nEv.vecParam = { 0, 0 };
				nEv.entityID = hEvent.entityID;
				tEvent buf;
				buf.eventType = ProjectileOption;
				memcpy(&buf.data, &nEv, sizeof(nEv));
				list.push(buf);
				hit = true;
				break;
			}
		if (!hit && (hEvent.pos.x > wndWidth + 200 || hEvent.pos.y > wndHeight + 200 || hEvent.pos.x < -200 || hEvent.pos.y < -200))
		{
			tProjectileOption nEv;
			nEv.command = destroy;
			nEv.projectileID = hEvent.projectileID;
			nEv.wParam = -1;
			nEv.vecParam = { 0, 0 };
			nEv.entityID = hEvent.entityID;
			tEvent buf;
			buf.eventType = ProjectileOption;
			memcpy(&buf.data, &nEv, sizeof(nEv));
			list.push(buf);
		}
		break;
	}
	case ProjectileOption:
		tProjectileOption poEvent;
		memcpy(&poEvent, &ev.data, sizeof(tProjectileOption));
		switch (poEvent.command)
		{
		case destroy:
			for (int i(0); i < projectiles.size(); i++)
				if (projectiles[i]->entityID == poEvent.entityID)
				{
					delete projectiles[i];
					projectiles.erase(projectiles.begin() + i);
					break;
				}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

float sqtDist(vec2 a, vec2 b)
{
	return (a.x - b.x)*(a.x - b.x)+(a.y - b.y)*(a.y - b.y);
}
