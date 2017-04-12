#include "Player.h"

int PlayerHandle::setShipMovement(vec2 NewMove)
{
	battle->setShipMovement(NewMove, shipIndex);
	return 0;
}

int PlayerHandle::addModule(ModuleType type)
{
	return battle->addShipModule(type, shipIndex);
}

int PlayerHandle::addAttrToModule(int moduleId, Attribute attr)
{
	battle->addAttrToModule(attr, shipIndex, moduleId);
	return 0;
}

int PlayerHandle::useWeapon(int weaponId)
{
	if (battle->useWeapon(shipIndex, weaponId) == 0)
	{
		return 0;
	}
	return -1;
}

int PlayerHandle::setBattle(tBattle * newBattle)
{
	battle = newBattle;
	return 0;
}

int PlayerHandle::setWeaponStats(int moduleId, WeaponInfo info)
{
	WeaponModuleInfo buff;
	buff.damage = info.damage;
	buff.range = info.range;
	buff.speed = info.speed;
	buff.style = info.style;
	buff.texture = info.texture;
	battle->setWeaponStats(buff, info.cooldown, shipIndex, moduleId);
	return 0;
}

PlayerHandle::PlayerHandle()
{
	shipIndex = -1;
	battle = nullptr;
}

PlayerHandle::~PlayerHandle()
{
}

int PrimaryStore::addItem(int id, ItemType type)
{
	switch (type)
	{
	case nullItem:
		if (items[id].type == module)
			((Module*)items[id].entity)->~Module();
		items[id].count = 0;
		items[id].type = nullItem;
		break;
	case resource:
		if (items[id].type == module)
			((Module*)items[id].entity)->~Module();
		items[id].count = 0;
		items[id].type = resource;
		break;
	case module:
		if (items[id].type == module)
			((Module*)items[id].entity)->~Module();
		items[id].count = 1;
		items[id].type = module;
		break;
	case blank:
		if (items[id].type == module)
			((Module*)items[id].entity)->~Module();
		items[id].count = 1;
		items[id].type = blank;
		break;
	default:
		break;
	}
	return 0;
}

void PrimaryStore::deleteItem(int id)
{
	if (items[id].type == module)
		((Module*)items[id].entity)->~Module();
	items[id].count = 0;
	items[id].type = nullItem;
}

void PrimaryStore::swapItem(int id1, int id2)
{
	Item temp = items[id1];
	items[id1] = items[id2];
	items[id2] = temp;

	int pt = _Store->cells[id1].additional;
	_Store->cells[id1].additional = _Store->cells[id2].additional;
	_Store->cells[id2].additional = pt;

}

int PrimaryStore::selectItem(int mouseX, int mouseY)
{
	int id = _Store->GetCellOnMouse(mouseX, mouseY);
	selected = id;
	_Store->selectedId = id;
	return id;
}

int PrimaryStore::configItem(int id, int count, int texId, const char * name)
{
	items[id].texId = texId;
	items[id].count = count;


	strcpy_s(items[id].name, name);

	_Store->cells[id].additional = texId;

	return 0;
}

int PrimaryStore::createItemModule(int id, int texId, ModuleType type, const char * name)
{
	if (items[id].type == nullItem)
	{
		items[id].type = module;
		items[id].texId = texId;
		items[id].count = 1;
		_Store->cells[id].additional = texId;

		switch (type)
		{
		case none:
			items[id].entity = new Module();
			strcpy_s(items[id].name, "Null module type");
			strcpy_s(((Module*)(items[id].entity))->name, name);
			((Module*)(items[id].entity))->active = false;
			((Module*)(items[id].entity))->id = -1;
			break;
		case core:
			break;
		case sys:
			items[id].entity = new SysModule();
			strcpy_s(items[id].name, name);
			strcpy_s(((SysModule*)(items[id].entity))->name, name);
			((SysModule*)(items[id].entity))->active = false;
			((SysModule*)(items[id].entity))->id = -1;
			break;
		case wep:
			items[id].entity = new WepModule();
			strcpy_s(items[id].name, name);
			strcpy_s(((WepModule*)(items[id].entity))->name, name);
			((WepModule*)(items[id].entity))->active = false;
			((WepModule*)(items[id].entity))->id = -1;
			break;
		default:
			break;
		}
		return id;
	}
	else return -1;
}

void PrimaryStore::setUIStore(UIStore * pick)
{
	_Store = pick;
}

int PrimaryStore::update(double deltatime)
{
	if (mouseClickL)
	{
		if (selected != -1)
		{
			int Scr = selected;
			selectItem(xPos, yPos);
			if (selected != -1)
			{
				swapItem(selected, Scr);
			}
			selected = -1;
			_Store->selectedId = -1;
		}
		else
		{
			selected = selectItem(xPos, yPos);
			SelectedItemId = selected;
		}
	}

	_Store->DrawStore();

	for (int i(0); i < capacity; i++)
		if (items[i].type != nullItem)
			drawStats(i);

	if (selected != -1)
		description(selected, _Store->cells[selected].pos);

	return 0;
}

int PrimaryStore::drawStats(int id)
{
	vec2 pos = _Store->cells[id].pos;
	if (items[id].count > 1)
		Font->outInt(pos.x + 19, pos.y + 16, items[id].count);
	return 0;
}

void PrimaryStore::description(int id, vec2 pos)
{
	
	switch (items[id].type)
	{
	case nullItem:
		break;
	case module: 
		switch (((Module*)(items[id].entity))->type)
		{
		case core:
			break;
		case sys:
			//((SysModule*)(items[id].entity))->hp;
			//DrawSprite3v(_Store->texturegray, 200, 300, pos.x, pos.y);
			Font->outText(1120, 57, "name:");
			Font->outText(1185, 57, ((SysModule*)(items[id].entity))->name);
			Font->outText(1120, 77, "Hp/MaxHp:");
			Font->outInt(1215, 77, ((SysModule*)(items[id].entity))->hp);
			Font->outText(1225, 77, "/");
			Font->outInt(1235, 77, ((SysModule*)(items[id].entity))->hpmax);
			Font->outText(1120, 97, "energyUsage:");
			Font->outInt(1225, 97, ((SysModule*)(items[id].entity))->energyUsage);
			for (int i(0); i < ((SysModule*)(items[id].entity))->attrN; i++)
			{
				switch (((SysModule*)(items[id].entity))->mAttr[i].type)
				{
				case tHull:
					Font->outText(1120, 117, "+energyUsage:");
					Font->outInt(1235, 117,((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tShield:
					Font->outText(1120, 137, "+Hull:");
					Font->outInt(1235, 137, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tReghp:
					Font->outText(1120, 157, "+Reghp:");
					Font->outInt(1235, 157, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tRegshield:
					Font->outText(1120, 177, "+Regshield:");
					Font->outInt(1235, 177, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tSpeed:
					Font->outText(1120, 197, "+Speed:");
					Font->outInt(1235, 197, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tPowerBattery:
					Font->outText(1120, 217, "+PowerBattery:");
					Font->outInt(1235, 217, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tEvade:
					Font->outText(1120, 237, "+Evade:");
					Font->outInt(1235, 237, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				default:
					break;
				}
			}
			break;
		case wep:
			//((WepModule*)(items[id].entity))->bCooldown;
			DrawSprite3v(_Store->texCell_004, 200, 710, 1090, 0);
			Font->outText(1120, 57, "name:");
			Font->outText(1120, 57, ((WepModule*)(items[id].entity))->name);
			Font->outText(1120, 62, "cooldown:");
			Font->outInt(1120, 57, ((WepModule*)(items[id].entity))->currentCooldown);
			Font->outText(1120, 57, "energyUsage:");
			Font->outInt(1120, 57, ((WepModule*)(items[id].entity))->energyUsage);
			Font->outText(1120, 57, "Damage:");
			Font->outInt(1120, 57, ((WepModule*)(items[id].entity))->Info.damage);
			Font->outText(1120, 57, "Range:");
			Font->outInt(1120, 57, ((WepModule*)(items[id].entity))->Info.range);
			Font->outText(1120, 57, "Speed:");
			Font->outInt(1120, 57, ((WepModule*)(items[id].entity))->Info.speed);

			break;
		case none:
			break;
		default:
			break;
		};
		break;
	case resource: 		
		DrawSprite3v(_Store->texCell_004,200,710,1090,0);
		Font->outText(1120,57, items[id].name);
		break;
	default:
		break;
	}
}

void PrimaryStore::clearSelection()
{
	selected = -1;
	_Store->selectedId = -1;
}

PrimaryStore::PrimaryStore(int size)
{
	capacity = size;
	for (int i(0); i < size; i++) 
	{ 
		items.push_back(Item()); 
		items[i].type = nullItem; 
	}
	used = 0;
	empty = size;
	selected = -1;
}

PrimaryStore::PrimaryStore()
{
	capacity = 0;
	used = 0;
	empty = 0;
	selected = -1;
}

PrimaryStore::~PrimaryStore()
{
	for (int i(0); i < items.size(); i++)
	{
		if (items[i].type == module)
		{
			((Module*)items[i].entity)->~Module();
		}
	}
}

int ShipMap::update(double deltatime)
{
	if (mouseClickL)
	{
		if (selected != -1)
		{
			int Scr = selected;
			selectItem(xPos, yPos);
			if (selected != -1)
			{
				swapItem(selected, Scr);
			}
			selected = -1;
			_Store->selectedId = -1;
		}
		else
		{
			selected = selectItem(xPos, yPos);
			SelectedItemId = selected;
		}
	}

	_Store->DrawStore();

	for (int i(0); i < capacity; i++)
		if (items[i].type != nullItem)
			drawStats(i);

	if (selected != -1)
		description(selected, _Store->cells[selected].pos);

	return 0;
}

int ShipMap::swapItem(int id1, int id2)
{
	Item temp = items[id1];
	items[id1] = items[id2];
	items[id2] = temp;

	int pt = _Store->cells[id1].additional;
	_Store->cells[id1].additional = _Store->cells[id2].additional;
	_Store->cells[id2].additional = pt;
	return 0;
}

int ShipMap::createShipMap(const char * filename)
{
	// for test
	cell temp;
	temp.pos = { 100, 100 };
	temp.additional = 32;
	temp.size = { 64, 64 };
	temp.id = 0;
	_Store->add(temp);
	temp.pos = { 100, 200 };
	temp.additional = 32;
	temp.size = { 64, 64 };
	temp.id = 1;
	_Store->add(temp);
	temp.pos = { 200, 100 };
	temp.additional = 32;
	temp.size = { 64, 64 };
	temp.id = 2;
	_Store->add(temp);
	items.push_back(Item());
	items.push_back(Item());
	items.push_back(Item());
	//

	return 0;
}

ShipMap::ShipMap()
{
}

ShipMap::~ShipMap()
{
}

int PlayerEnviroment::update(double deltatime)
{
	int tmpItemShipMap = selectedShipMapId;
	int	tmpItemStore = selectedStoreId;

	if (bShipMapActive)
	{
		_shipM->update(deltatime);
		selectedShipMapId = _shipM->selected;
		if (tmpItemStore != -1 && selectedShipMapId != -1 && mouseClickL)
		{
			Item temp = _shipM->items[selectedShipMapId];
			_shipM->items[selectedShipMapId] = _store->items[tmpItemStore];
			_store->items[tmpItemStore] = temp;

			int pt = _shipM->_Store->cells[selectedShipMapId].additional;
			_shipM->_Store->cells[selectedShipMapId].additional = _store->_Store->cells[tmpItemStore].additional;
			_store->_Store->cells[tmpItemStore].additional = pt;

			selectedShipMapId = -1;
			_shipM->clearSelection();
			_store->clearSelection();

			mouseClickL = false;
		}
	}
	if (bStoreActive)
	{
		_store->update(deltatime);
		selectedStoreId = _store->selected;
		if (selectedStoreId != -1 && tmpItemShipMap != -1 && mouseClickL)
		{
			Item temp = _shipM->items[tmpItemShipMap];
			_shipM->items[tmpItemShipMap] = _store->items[selectedStoreId];
			_store->items[selectedStoreId] = temp;

			int pt = _shipM->_Store->cells[tmpItemShipMap].additional;
			_shipM->_Store->cells[tmpItemShipMap].additional = _store->_Store->cells[selectedStoreId].additional;
			_store->_Store->cells[selectedStoreId].additional = pt;

			selectedStoreId = -1;
			_shipM->clearSelection();
			_store->clearSelection();

			mouseClickL = false;
		}
	}
/*
	if (mouseClickL)
	{
		if (selected != -1)
		{
			int Scr = selected;
			selectItem(xPos, yPos);
			if (selected != -1)
			{
				swapItem(selected, Scr);
			}
			selected = -1;
			_Store->selectedId = -1;
		}
		else
		{
			selected = selectItem(xPos, yPos);
			SelectedItemId = selected;
		}
	}
*/
/*
	_Store->DrawStore();

	for (int i(0); i < capacity; i++)
		if (items[i].type != nullItem)
			drawStats(i);

	if (selected != -1)
		description(selected, _Store->cells[selected].pos);

	return 0;
*/
	return 0;
}

PlayerEnviroment::PlayerEnviroment()
{
	selectedShipMapId = -1;
	selectedStoreId = -1;
	bShipMapActive = false;
	bStoreActive = false;
	bStoreExpanded = false;
}

PlayerEnviroment::~PlayerEnviroment()
{
}
