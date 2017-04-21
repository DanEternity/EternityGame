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
#include<Tview.h>

std::vector<std::string>strings;

class Talking 
{
public:
	UISmartGrid * UISG;
	vec2 pos,size;
	unsigned int texturegray;
	unsigned int texbt_001;
	void fileRead(char s[]);
	int init(int id);
	void check(UISmartGrid*UISG);
	
	int conclusion(std::string s[]);
	void setFont(tFont * pick);
	tFont * Font;
	UISmartGrid * tUISmartGrid;


	Talking();
	~Talking();
};

