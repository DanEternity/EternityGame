#include "editor.h"
#include <iostream>
/*
void SaveModuleToFile(const char * filename, Module * target, int format)
{
	FILE * f;
	freopen_s(&f, filename, "w", stderr);

	//fprintf(f, )

	switch (target->type)
	{
	case sys:
		break;
	default:
		break;
	}

}

Module * LoadModuleFromFile(const char * filename)
{
	FILE * f;
	if (freopen_s(&f, filename, "r", stderr))
	{
		ModuleType tp;
		SysModule * tr;
		Module * target = nullptr;
		fscanf_s(f, "%i \n", &tp);
		switch (tp)
		{
		case none:
			break;
		case main:
			break;
		case sys:
			target = new SysModule();
			tr = (SysModule *)target;
			fscanf_s(f, "%s \n", &tr->name);
			fscanf_s(f, "%f \n", &tr->healthMax);
			fscanf_s(f, "%f \n", &tr->energyConsumption);
			fscanf_s(f, "%i \n", &tr->size);
			fscanf_s(f, "%i \n", &tr->attrCount);
			for (int i(0); i < tr->attrCount; i++)
			{
				fscanf_s(f, "%i \n", &tr->nAttr[i].attr);
				fscanf_s(f, "%f \n", &tr->nAttr[i].valueFloat1);
				fscanf_s(f, "%f \n", &tr->nAttr[i].valueFloat2);
				fscanf_s(f, "%i \n", &tr->nAttr[i].valueInt1);
				fscanf_s(f, "%i \n", &tr->nAttr[i].valueInt2);
			}
			break;
		case weapon:

			break;
		case extra:
			break;
		default:
			break;
		}
	}
	else 
		return nullptr;
}
*/