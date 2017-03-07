#pragma once

#include<Types.h>
#include<Globals.h>
#include<Ship.h>
#include<Battle.h>

class PlayerHandle
{
public:
	tBattle * battle;
	int shipIndex;
	int setShipMovement(vec2 NewMove);
	int addModule(ModuleType type);
	int addAttrToModule(int moduleId, Attribute attr);

	int setBattle(tBattle * newBattle);

	PlayerHandle();
	~PlayerHandle();
};