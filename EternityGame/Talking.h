#pragma once

#include<Graphics.h>
#include<Battle.h>
#include<Globals.h>
#include <Types.h>
#include <Vector>
#include <windows.h>
#include<module.h>
#include<ship.h>
#include <fstream>
#include <string>
#include<UI.h>


class Talking
{
public:
	vec2 pos,size;
	unsigned int texturegray;
	unsigned int texbt_001;
	void fileRead(char s[]);
	int conclusion(const char s[]);
	void setFont(tFont * pick);
	tFont * Font;



	Talking();
	~Talking();
};

