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
	tFont * Font;

	int addItem(int id, ItemType type);
	void deleteItem(int id);
	void swapItem(int id1, int id2);
	int selectItem(int mouseX, int mouseY);

	int configItem(int id, int count, int texId, const char * name);
	int createItemModule(int id, int texId, ModuleType type, const char * name);
	void setUIStore(UIStore * pick);
	int update(double deltatime);
	int drawStats(int id);
	void description(int id, vec2 pos);
	void clearSelection();

	PrimaryStore(int size);
	PrimaryStore();
	~PrimaryStore();
};

class ShipMap : public PrimaryStore
{
public:

	//std::vector<Item> shipModules;
	std::vector<SocketInfo> sockets;


	int update(double deltatime);
	int swapItem(int id1, int id2);

	int createShipMap(const char * filename);

	ShipMap();
	~ShipMap();
};

class PlayerEnviroment
{
public:
	int selectedShipMapId;
	int selectedStoreId;
	ShipMap * _shipM;
	PrimaryStore * _store;

	/* Flags */
	bool bShipMapActive;
	bool bStoreActive;
	bool bStoreExpanded;

	/* Functions */
	int update(double deltatime);

	PlayerEnviroment();
	~PlayerEnviroment();

};