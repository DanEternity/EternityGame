#pragma once
#include<Types.h>

class tProjectile
{
public:
	vec2 pos;
	vec2 movement;
	
	int ownerId;
	float speed;
	float damage;
	
	int texture;


};