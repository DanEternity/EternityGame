#include "BattleScripts.h"

ScriptResult CreateTestField(tBaseAdventure * pAdventure, tBattle * pBattle, int attribute1, int attribute2, int * attributeArray)
{
	/* TEST SCRIPT */
	/* ONLY FOR TESTING */

	/* Trying to add test objects */

	int id;

	unsigned int tex = UINT32(attribute1);

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

ScriptResult CreateTestField2(tBaseAdventure * pAdventure, tBattle * pBattle, int attribute1, int attribute2, int * attributeArray)
{
	/* TEST SCRIPT */
	/* ONLY FOR TESTING */

	/* Trying to add test objects */

	int id;
	int n = attribute2;
	unsigned int tex = UINT32(attribute1);
	for (int i(0); i < n; i++)
	{
		int power = rand()%100 + 50;
		float qq = float(power / 2);
		id = pBattle->addShip();
		pBattle->setShipStats({ "Meteorite", qq*3, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, tex, power, power, qq*1.1f }, id);
		pBattle->setShipPosition({ float(rand()%500 + 40) , float(rand()%400 + 40) }, id);
	}

	return{ TRUE, rcBattle, 0 }; // ScriptResult { bool = true, ScriptResultCode, int };
}