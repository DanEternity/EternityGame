#pragma once

#include<Types.h>
#include<module.h>

struct Item
{
public:
	char name[30];
	ItemType type;

	int count;
	int texId;

	void* entity;
};