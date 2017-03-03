#include "module.h"

Module::Module()
{
}

Module::~Module()
{
}

void SysModule::addAtribute(tAttribute type, float count)
{
	if (attrN == 8)
	{
		return;
	}
	mAttr[attrN].type = type;
	mAttr[attrN++].count = count;

}

SysModule::SysModule()
{
	attrN = 0;
}

SysModule::~SysModule()
{
}

WepModule::WepModule()
{
}

WepModule::~WepModule()
{
}
