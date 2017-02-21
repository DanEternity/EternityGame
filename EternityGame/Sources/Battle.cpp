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

void Ship::weaponUse(int WeaponID, vec2 pos)
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

void Ship::clearStats()
{
//	energy
	ShipSystem.freeEnergy = 0;
	ShipSystem.totalCapacity = 0;
	ShipSystem.totalConsumption = 0;
//	hull
	hullMax = baseHull;
	hullRegen = 0;
//	shield
	shieldMax = 0;
	shieldRegen = 0;
//	movement
	evasion = 0;
	speedMax = 0;
	acceleration = 0;
}

void Ship::updStats(double deltatime)
{
	for (int i(0); i < ShipSystem.mArray.size(); i++)
		if (ShipSystem.mArray[i]->bActive && ShipSystem.mArray[i]->type == sys)
		{
			SysModule * p = (SysModule * )ShipSystem.mArray[i];
			for (int j(0); j < p->attrCount; j++)
				switch (p->nAttr[j].attr)
				{
				case shieldmod:
					shieldMax += p->nAttr[j].valueFloat1; // valueFloat1 = Max shield
					shieldRegen += p->nAttr[j].valueFloat2; // valueFloat2 = Shield regeneration
					break;
				case hullmod:
					hullMax += p->nAttr[j].valueFloat1; // valueFloat1 = Max hull
					hullRegen += p->nAttr[j].valueFloat2; // valueFloat2 = Shield regeneration
					break;
				case engmod:
					speedMax += p->nAttr[j].valueFloat1; // valueFloat1 = Max speed
					acceleration += p->nAttr[j].valueFloat2 * 0.01f; // valueFloat2 = Engine power -> affect multiple stats
					evasion += p->nAttr[j].valueFloat2 * 0.05f;
					break;
				case energymod:
					ShipSystem.totalCapacity += p->nAttr[j].valueFloat1; // valueFloat1 = Output energy
					break;
				}
		}
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
	/* Module events */
	for (int i(0); i < units.size(); i++)
	{
		units[i]->ShipSystem.update(deltatime);
	}


	/* Projectiles events */
	for (int i(0); i < projectiles.size(); i++)
	{
		projectiles[i]->move(deltatime);
		tCollisionCheck colEvent;
		colEvent.pos = projectiles[i]->pos;
		colEvent.projectileID = projectiles[i]->entityID;
		colEvent.side = projectiles[i]->side;
		colEvent.entityID = projectiles[i]->entityID;
		colEvent.pointer = projectiles[i];
		tEvent ev;
		ev.eventType = CollisionEvent;
		memcpy(&ev.data, &colEvent, sizeof(tCollisionCheck));
		list.push(ev);
	}

	listSize = list.size();

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

void Battle::command(Ship * target)
{
	Projectile nProjectile;
	if (target->ShipSystem.activateWeapon(0, { 0, -1 }, &nProjectile))
	{
		nProjectile.pos = target->pos;
		addProjectile(nProjectile);
	}
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
				nEv.pointer = hEvent.pointer;
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
			nEv.pointer = hEvent.pointer;
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


void Module::update(double deltatime)
{
}

Module::Module()
{
}

Module::~Module()
{
}

void SysModule::update(double deltatime)
{
}

bool SysModule::addAttribute(tAttribute attribute)
{
	if (attrCount == 8)
		return false;
	else
		nAttr[attrCount++] = attribute;
	return true;
}

bool SysModule::cutAttribute(int ID)
{
	if (attrCount == 0 || ID >= attrCount)
		return false;
	else
	{
		for (int i(ID); i < attrCount-1; i++)
			nAttr[ID] = nAttr[ID + 1];
		attrCount--;
	}
	return true;
}

SysModule::SysModule()
{
	attrCount = 0;
}

void WepModule::init(float Cooldown, LockoutType type, Projectile exProjectile)
{
	wepCooldown = Cooldown;
	lType = type;
	mProjectile = exProjectile;
	wepCurrentCd = 0;
}

void WepModule::update(double deltatime)
{
	if (bCooldown)
	{
		wepCurrentCd -= deltatime;
		if (wepCurrentCd < 0)
		{
			wepCurrentCd = 0;
			bCooldown = false;
		}
	}
}

bool WepModule::shoot(Projectile * newProjectile, vec2 rotation)
{
	if (!bCooldown)
	{
		wepCurrentCd = wepCooldown;
		bCooldown = true;
		mProjectile.vec = rotation;
		memcpy(newProjectile, &mProjectile, sizeof(mProjectile));
		return true;
	}
	else
		return false;
}

WepModule::WepModule()
{
}

WepModule::~WepModule()
{
}

void cShipSystem::addModule(Module * newModule)
{
	//Module * tmp = new Module();
//	memcpy(tmp, newModule, sizeof(Module));
	//mArray.push_back(tmp);
	
	
	if (newModule->type == weapon)
	{
		WepModule * tmp = new WepModule();
		memcpy(tmp, newModule, sizeof(WepModule));
		mArray.push_back(tmp);
		wepArray.push_back(mArray.size() - 1);
	}
	if (newModule->type == sys)
	{
		SysModule * tmp = new SysModule();
		memcpy(tmp, newModule, sizeof(SysModule));
		mArray.push_back(tmp);
	}
}

void cShipSystem::update(double deltatime)
{
	for (int i(0); i < mArray.size(); i++)
	{
		mArray[i]->update(deltatime);
	}
}

bool cShipSystem::activateWeapon(int wepID, vec2 rotate, Projectile * newProjectile)
{
	if (wepID < wepArray.size() && wepArray[wepID] < mArray.size())
	{
		int moduleID = wepArray[wepID];
		if (mArray[moduleID]->type == weapon)
		{
			WepModule * wep = (WepModule *)mArray[moduleID];
			if (wep->shoot(newProjectile, rotate))
			{
				//newProjectile->pos = { 100, 100 };
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}


float sqtDist(vec2 a, vec2 b)
{
	return (a.x - b.x)*(a.x - b.x)+(a.y - b.y)*(a.y - b.y);
}
