#pragma once

#include<Types.h>
#include<Globals.h>
#include<Ship.h>
#include<Battle.h>
#include<items.h>
#include<UI.h>

class PlayerHandle
{
public:
	tBattle * battle;
	int shipIndex;
	int setShipMovement(vec2 NewMove);
	int addModule(ModuleType type);
	int addAttrToModule(int moduleId, Attribute attr);
	int useWeapon(int weaponId);
	int setBattle(tBattle * newBattle);
	int setWeaponStats(int moduleId, WeaponInfo info);




	PlayerHandle();
	~PlayerHandle();
};

class PrimaryStore
{
public:
	/* Player store */
	std::vector<Item> items;
	int capacity;
	int used, empty;

	int selected;
	UIStore * _Store;

	int addItem(int id, ItemType type);
	void deleteItem(int id);
	int selectItem(int mouseX, int mouseY);
	int configItem(int id, int count, int texId, const char * name);
	void setUIStore(UIStore * pick);


	PrimaryStore(int size);
	~PrimaryStore();
};