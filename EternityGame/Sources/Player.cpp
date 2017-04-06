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
			DrawSprite3v(_Store->texCell_004, 200, 710, 1090, 0);
			Font->outText(1120, 57, "name:");
			Font->outText(1125, 57, ((SysModule*)(items[id].entity))->name);
			Font->outText(1120, 67, "Hp/MaxHp:");
			Font->outInt(1130, 67, ((SysModule*)(items[id].entity))->hp);
			Font->outText(1135, 67, "/");
			Font->outInt(1140, 67, ((SysModule*)(items[id].entity))->hpmax);
			Font->outText(1120, 77, "energyUsage:");
			Font->outInt(1125, 77, ((SysModule*)(items[id].entity))->energyUsage);
			for (int i(0); i < ((SysModule*)(items[id].entity))->attrN; i++)
			{
				switch (((SysModule*)(items[id].entity))->mAttr[i].type)
				{
				case tHull:
					//Font->outInt(1120, 67,((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tShield:
					//Font->outInt(1120, 67, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tReghp:
					//Font->outInt(1120, 67, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tRegshield:
					//Font->outInt(1120, 67, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tSpeed:
					//Font->outInt(1120, 67, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tPowerBattery:
					//Font->outInt(1120, 67, ((SysModule*)(items[id].entity))->mAttr[i].count);
					break;
				case tEvade:
					//Font->outInt(1120, 67, ((SysModule*)(items[id].entity))->mAttr[i].count);
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
