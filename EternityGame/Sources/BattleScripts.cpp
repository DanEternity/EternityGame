#include "BattleScripts.h"

ScriptResult CreateTestField(tZoneContext * Context)
{
	/* TEST SCRIPT */
	/* ONLY FOR TESTING */

	/* Trying to add test objects */

	int id;

	unsigned int tex = UINT32(Context->attribute1);
	tBattle * pBattle = Context->pBattle;

	id = pBattle->addShip();
	pBattle->setShipStats({ "Meteorite", 100, 0, 0, 0, 1, 0, 1, tex, 80, 80, 40 }, id);
	pBattle->setShipPosition({ 300, 100 }, id);

	id = pBattle->addShip();
	pBattle->setShipStats({ "Meteorite", 100, 0, 0, 0, 1, 0, 1, tex, 80, 80, 40 }, id);
	pBattle->setShipPosition({ 600, 100 }, id);

	id = pBattle->addShip();
	pBattle->setShipStats({ "Meteorite", 100, 0, 0, 0, 1, 0, 1, tex, 80, 80, 40 }, id);
	pBattle->setShipPosition({ 450, 240 }, id);

	return {TRUE, rcBattle, 0}; // ScriptResult { bool = true, ScriptResultCode, int };
}

ScriptResult CreateTestField2(tZoneContext * Context)
{
	/* TEST SCRIPT */
	/* ONLY FOR TESTING */

	/* Trying to add test objects */

	int id;

	int n = Context->attribute2;
	unsigned int tex = UINT32(Context->attribute1);
	tBattle * pBattle = Context->pBattle;

	for (int i(0); i < n; i++)
	{
		int power = rand()%100 + 50;
		float qq = float(power / 2);
		id = pBattle->addShip();
		pBattle->setShipStats({ "Meteorite", qq*3, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, tex, power, power, qq*0.9f }, id);
		pBattle->setShipPosition({ float(rand()%500 + 40) , float(rand()%400 + 40) }, id);
	}

	return{ TRUE, rcBattle, 0 }; // ScriptResult { bool = true, ScriptResultCode, int };
}

ScriptResult CreateBasicProcessField(tZoneContext * Context)
{
	/* TEST SCRIPT */
	/* ONLY FOR TESTING */

	/* Trying to add test objects */

	int id;

	int n = Context->attribute2;
	unsigned int tex = UINT32(Context->attribute1);
	tBattle * pBattle = Context->pBattle;
	Context->attributeArray = new int[n + 2];

	for (int i(0); i < n; i++)
	{
		int power = rand() % 120 + 50;
		float qq = float(power / 2);
		id = pBattle->addShip();
		pBattle->setShipStats({ "Meteorite", qq * 3, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, tex, power, power, qq*0.9f }, id);
		pBattle->setShipPosition({ float(rand() % 940 + 40) , float(rand() % 450 + 40) }, id);
		Context->attributeArray[i] = id;
	}

	return{ TRUE, rcBattle, 0 }; // ScriptResult { bool = true, ScriptResultCode, int };
}

ScriptResult BasicProcessField(tZoneContext * Context, tfEvent fEvent)
{
	/* TEST SCRIPT */
	/* ONLY FOR TESTING */

	/* Switch event type */

	switch (fEvent)
	{
	case tfUpdate:
	{
		/* updating */

		/* For example we will rotate all objects defined in attributeArray */

		double dt = deltaTime;
		tBattle * pBattle = Context->pBattle;

		for (int i(0); i < Context->attribute2; i++)
			if (pBattle->units.count(Context->attributeArray[i]) == 1)
			{
				((tShip *)(pBattle->units[Context->attributeArray[i]]))->rotation += ((i % 2) * (-2) + 1) * 0.4 * dt;
			}

		break;
	}
	case tfEnd:
	{
		/* cencelling */
		tBattle * pBattle = Context->pBattle;
		bool ready = true;
		for (int i(0); i < Context->attribute2; i++)
			if (pBattle->units.count(Context->attributeArray[i]) == 1)
			{
				ready = false;
				break;
			}

		if (ready)
		{
			/* FOR EXAMPLE GIVE 100 - 250 Iron */

			int id = Context->pEnv->_store->addItem(resource);
			Context->pEnv->_store->configItem(id, rand() % 151 + 100, 0, "Iron");

			return{ TRUE, rcAdventure, 1 };
		}
		break;
	}
	case tfObjectDestroed:
		/* on object destroy */
		break;
	default:
		/* incorrect call */
		return{ FALSE, rcNothing, 0 };
		break;
	}
	return{ TRUE, rcNothing, 0 }; // ScriptResult { bool = true, ScriptResultCode, int };
}
