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

	return {TRUE, rcBattle, 0}; // ScriptResult { bool = true, int, int };
}
