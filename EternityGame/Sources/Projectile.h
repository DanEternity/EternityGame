#pragma once
#include<Types.h>
#include<cmath>

class tProjectile
{
public:
	vec2 pos;
	vec2 movement;
	
	int ownerId;
	float speed;
	float damage;
	
	int texture;

	void setMove(vec2 newMove);
	void setPosition(vec2 newPosition);
	void setStats(ShootBaseStats stats);
	void setTexture(unsigned int tex);

	tProjectile();
	~tProjectile();

};