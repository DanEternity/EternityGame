#pragma once
#include <windows.h>
#include <Vector>
#include <Types.h>
#include <Graphics.h>
#include <UI.h>


class Botton : public UISmartGrid
{
public:
	vec2 size,pos;
	int id;
	void drawBotton(int id);
	tFont * Font;
	unsigned int texbt_001;
	void setFont(tFont * pick);	
	Botton();
	~Botton();
};
