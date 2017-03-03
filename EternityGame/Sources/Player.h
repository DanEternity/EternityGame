#pragma once

#include<Types.h>
#include<Globals.h>
#include<Ship.h>
#include<Battle.h>

class PlayerHandle
{
	tBattle * battle;
	int shipIndex;
	int setShipMovement(vec2 NewMove);
	int setBattle(tBattle * newBattle);

};