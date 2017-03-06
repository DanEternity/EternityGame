#include "Projectile.h"

void tProjectile::setMove(vec2 newMove)
{
	float mod = sqrt(newMove.x * newMove.x + newMove.y * newMove.y);
	if (mod == 0)
	{
		movement = { 0, 0 };
		return;
	}
	movement.x = newMove.x / mod;
	movement.y = newMove.y / mod;
	return;
}

void tProjectile::setPosition(vec2 newPosition)
{
	pos = newPosition;
}

void tProjectile::setStats(ShootBaseStats stats)
{
	pos = stats.pos;
	movement = stats.movement;
	ownerId = stats.ownerId;
	damage = stats.damage;
	speed = stats.speed;
	texture = stats.texture;
}

void tProjectile::setTexture(unsigned int tex)
{
	texture = tex;
}

tProjectile::tProjectile()
{
	pos = { 0, 0 };
	movement = { 0, 0 };
	ownerId = 0;
	speed = 0;
	damage = 0;
	texture = 0;
}

tProjectile::~tProjectile()
{
}
